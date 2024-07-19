#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Triangulation_3_to_lcc.h>

#include <iostream>
#include <fstream>
#include <cassert>

#include "OFFConstructor.h"

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
typedef LCC_3::Dart_descriptor Dart_descriptor;
typedef LCC_3::Point           Point;

typedef CGAL::Delaunay_triangulation_3<LCC_3::Traits> Triangulation;

namespace V3D
{

  class DelaunayVoronoiManager
  {
  public:
    DelaunayVoronoiManager() = default;

    DelaunayVoronoiManager(const std::string& filename)
    {
      std::ifstream iFile(filename.c_str());
      if (!iFile)
      {
        std::cout << "[DelaunayVoronoiManager] Problem reading file " << filename << std::endl;
        return;
      }

      std::istream_iterator<Point> begin(iFile), end;
      delaunayTriangulation.insert(begin, end);

      assert(delaunayTriangulation.is_valid(false));
    }

    void insertPoint(Point p)
    {
      delaunayTriangulation.insert(p);
    }

    void generateTriangulationLCC()
    {
      triangulationDart = CGAL::import_from_triangulation_3<LCC_3, Triangulation>(triangulationLCC, delaunayTriangulation, &triangulationVolToDart);
      
      std::cout << "Triangulation LCC:" << std::endl << "  ";
      triangulationLCC.display_characteristics(std::cout) << ", valid=" << triangulationLCC.is_valid() << std::endl;
    }

    void generateVoronoiLCC()
    {
      voronoiDart = triangulationLCC.dual(voronoiLCC, triangulationDart);

      // Here, voronoiLCC is the 3D Voronoi diagram
      assert(voronoiLCC.is_without_boundary());

      transformDartToDual();
      setVoronoiLCCGeometry();

      std::cout << "Unfiltered Voronoi LCC:" << std::endl << "  ";
      voronoiLCC.display_characteristics(std::cout) << ", valid=" << voronoiLCC.is_valid() << std::endl;

      filterVoronoiLCCFiniteVolumes();

      std::cout << "Voronoi LCC:" << std::endl << "  ";
      voronoiLCC.display_characteristics(std::cout) << ", valid=" << voronoiLCC.is_valid() << std::endl;
    }

    void writeTriangulationToOFF(const std::string& path)
    {
      writeLCCToOFF(path, triangulationLCC);
    }

    void writeVoronoiToOFF(const std::string& path)
    {
      writeLCCToOFF(path, voronoiLCC);
    }

  private:

    void transformDartToDual()
    {
      LCC_3::Dart_range::iterator it1 = triangulationLCC.darts().begin();
      LCC_3::Dart_range::iterator it2 = voronoiLCC.darts().begin();

      std::map<LCC_3::Dart_descriptor, LCC_3::Dart_descriptor> dual;

      for (; it1!=triangulationLCC.darts().end(); ++it1, ++it2)
      {
        dual[it1] = it2;
      }

      for (std::map<Triangulation::Cell_handle, LCC_3::Dart_descriptor>::iterator it = triangulationVolToDart.begin(), itend = triangulationVolToDart.end(); it!=itend; ++it)
      {
        triangulationVolToDart[it->first] = dual[it->second];
      }
    }

    void setVoronoiLCCGeometry()
    {
      for (std::map<Triangulation::Cell_handle, LCC_3::Dart_descriptor>::iterator it = triangulationVolToDart.begin(), itend = triangulationVolToDart.end(); it != itend; ++it)
      {
        if (!delaunayTriangulation.is_infinite(it->first))
        {
          voronoiLCC.set_vertex_attribute(it->second, voronoiLCC.create_vertex_attribute(delaunayTriangulation.dual(it->first)));
        }
        else
        {
          voronoiLCC.set_vertex_attribute(it->second, voronoiLCC.create_vertex_attribute());
        }
      }
    }

    void filterVoronoiLCCFiniteVolumes()
    {
      // We remove the infinite volume plus all the volumes adjacent to it.
      // Indeed, we cannot view these volumes since they do not have
      // a "correct geometry".
      std::stack<Dart_descriptor> toRemove;
      LCC_3::size_type markToRemove = voronoiLCC.get_new_mark();

      // Dart belongs to the infinite volume.
      toRemove.push(voronoiDart);
      CGAL::mark_cell<LCC_3, 3>(voronoiLCC, voronoiDart, markToRemove);

      // Now we get all the volumes adjacent to the infinite volume.
      for (LCC_3::Dart_of_cell_range<3>::iterator it = voronoiLCC.darts_of_cell<3>(voronoiDart).begin(), itend = voronoiLCC.darts_of_cell<3>(voronoiDart).end(); it != itend; ++it)
      {
        if (!voronoiLCC.is_marked(voronoiLCC.beta(it, 3), markToRemove))
        {
          CGAL::mark_cell<LCC_3, 3>(voronoiLCC, voronoiLCC.beta(it, 3), markToRemove);
          toRemove.push(voronoiLCC.beta(it,3));
        }
      }

      while(!toRemove.empty())
      {
        voronoiLCC.remove_cell<3>(toRemove.top());
        toRemove.pop();
      }

      assert(voronoiLCC.is_without_boundary(1) && voronoiLCC.is_without_boundary(2));
    }

    void writeLCCToOFF(const std::string& path, const LCC_3& lcc)
    {
      V3D::OFFConstructor off;
      
      LCC_3::size_type markVolumes  = lcc.get_new_mark();
      LCC_3::size_type markFaces    = lcc.get_new_mark();
      LCC_3::size_type orientedMark = lcc.get_new_mark();

      lcc.orient(orientedMark);

      for (LCC_3::Dart_range::const_iterator it = lcc.darts().begin(), itend = lcc.darts().end(); it != itend; ++it)
      {
        if (!lcc.is_marked(it, markVolumes))
        {
          for (LCC_3::template Dart_of_cell_basic_range<3>::const_iterator
               itv = lcc.template darts_of_cell_basic<3>(it, markVolumes).begin(), itvend = lcc.template darts_of_cell_basic<3>(it, markVolumes).end();
               itv != itvend;
               ++itv)
          {
            lcc.mark(itv, markVolumes); // To be sure that all darts of the basic iterator will be marked

            if (!lcc.is_marked(itv, markFaces) && lcc.is_marked(itv, orientedMark))
            {
              writeLCCFace(off, lcc, itv);
            }

            for (LCC_3::template Dart_of_cell_basic_range<2>::const_iterator
                 itf = lcc.template darts_of_cell_basic<2>(itv, markFaces).begin(), itfend = lcc.template darts_of_cell_basic<2>(itv, markFaces).end();
                 itf != itfend;
                 ++itf)
            {
              lcc.mark(itf, markFaces); // To be sure that all darts of the basic iterator will be marked
            }
          }
        }
      }
      
      for (LCC_3::Dart_range::const_iterator it = lcc.darts().begin(), itend = lcc.darts().end(); it != itend; ++it)
      {
        lcc.unmark(it, markFaces);
        lcc.unmark(it, markVolumes);
        lcc.unmark(it, orientedMark);
      }

      lcc.free_mark(markVolumes);
      lcc.free_mark(markFaces);
      lcc.free_mark(orientedMark);

      off.write(path);
    }

    void writeLCCFace(OFFConstructor& off, const LCC_3& lcc, LCC_3::Dart_const_descriptor dh)
    {
      LCC_3::Dart_const_descriptor cur = dh;
      LCC_3::Dart_const_descriptor min = dh;

      do
      {
        if (!lcc.is_next_exist(cur)) return; // Open face
        if (cur < min) min = cur;
        cur = lcc.next(cur);
      }
      while(cur != dh);

      off.initFace();

      cur = dh;
      do
      {
        Point p = lcc.point(cur);

        off.addVertex(p.x(), p.y(), p.z());

        cur = lcc.next(cur);
      }
      while(cur != dh);

      off.endFace();
    }

    // Delaunay Triangulation 3
    Triangulation delaunayTriangulation;

    // Triangulation LCC
    LCC_3 triangulationLCC;
    Dart_descriptor triangulationDart;
    std::map<Triangulation::Cell_handle, LCC_3::Dart_descriptor> triangulationVolToDart;

    // Voronoi LCC
    LCC_3 voronoiLCC;
    Dart_descriptor voronoiDart;
  };

}