#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Triangulation_3_to_lcc.h>

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
typedef LCC_3::Dart_descriptor Dart_descriptor;
typedef LCC_3::Point           Point;

typedef CGAL::Delaunay_triangulation_3<LCC_3::Traits> Triangulation;