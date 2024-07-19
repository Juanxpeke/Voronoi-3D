#include "PathManager.h"
#include "DelaunayVoronoiManager.h"
#include "PointsGenerator.h"

int main()
{
  const std::string triangulationPath = V3D::filePath("assets/output/ComplexTriangulation.off");
  const std::string voronoiPath = V3D::filePath("assets/output/ComplexVoronoi.off");

  V3D::DelaunayVoronoiManager dvm;

  dvm.insertPoint(Point(0, 0, 0));
  dvm.insertPoint(Point(1, 0, 0));
  dvm.insertPoint(Point(1, 0, 1));
  dvm.insertPoint(Point(0, 0, 1));

  dvm.insertPoint(Point(0, 1, 0));
  dvm.insertPoint(Point(1, 1, 0));
  dvm.insertPoint(Point(1, 1, 1));
  dvm.insertPoint(Point(0, 1, 1));

  size_t innerPointsAmount = 12;

  std::vector<Point> innerPoints = V3D::generatePointsInCube(0.5, innerPointsAmount, Point(0.5, 0.5, 0.5));

  for (const Point& point : innerPoints)
  {
    dvm.insertPoint(point);
  }

  dvm.generateTriangulationLCC();
  dvm.generateVoronoiLCC();

  dvm.writeTriangulationToOFF(triangulationPath);
  dvm.writeVoronoiToOFF(voronoiPath);

  return 0;
}