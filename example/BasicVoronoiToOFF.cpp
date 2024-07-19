#include "PathManager.h"
#include "DelaunayVoronoiManager.h"

int main()
{
  const std::string voronoiPath = V3D::filePath("assets/output/Voronoi.off");

  V3D::DelaunayVoronoiManager dvm;

  dvm.insertPoint(Point(0, 0, 0));
  dvm.insertPoint(Point(1, 0, 0));
  dvm.insertPoint(Point(1, 0, 1));
  dvm.insertPoint(Point(0, 0, 1));

  dvm.insertPoint(Point(0, 1, 0));
  dvm.insertPoint(Point(1, 1, 0));
  dvm.insertPoint(Point(1, 1, 1));
  dvm.insertPoint(Point(0, 1, 1));

  dvm.insertPoint(Point(0.5, 0.5, 0.5));

  dvm.generateTriangulationLCC();

  dvm.generateVoronoiLCC();

  dvm.writeVoronoiToOFF(voronoiPath);

  return 0;
}