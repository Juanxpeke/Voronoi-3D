#include "Definitions.h"

namespace V3D
{

  class Volume
  {
  public:
    void initFace()
    {
      currentFace.clear();
    }

    void addVertex(double x, double y, double z)
    {
      vertices.push_back({x, y, z});
      currentFace.push_back(vertices.size() - 1);
    }

    void endFace() {
      if (!currentFace.empty())
      {
        faces.push_back(currentFace);
      }
    }

  private:
    std::vector<std::vector<double>> vertices;
    std::vector<std::vector<int>> faces;
    std::vector<int> currentFace;
  };

}