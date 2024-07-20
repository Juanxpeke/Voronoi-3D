#include "PathManager.h"
#include "DelaunayVoronoiManager.h"

int main()
{
  const std::string triangulationPath = V3D::filePath("assets/output/BasicTriangulation.off");

  V3D::DelaunayVoronoiManager dvm;

  dvm.insertPoint(Point(0, 0, 0));
  dvm.insertPoint(Point(1, 0, 0));
  dvm.insertPoint(Point(0, 1, 0));
  dvm.insertPoint(Point(0, 0, 1));

  dvm.generateTriangulationLCC();

  dvm.writeTriangulationToOFF(triangulationPath);

  return 0;
}