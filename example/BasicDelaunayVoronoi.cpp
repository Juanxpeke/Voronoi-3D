#include "PathManager.h"
#include "DelaunayVoronoiManager.h"

int main()
{
  const std::string pointsPath = V3D::filePath("assets/data/points3");

  V3D::DelaunayVoronoiManager dvm(pointsPath);

  dvm.generateTriangulationLCC();
  dvm.generateVoronoiLCC();

  return 0;
}