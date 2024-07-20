#pragma once

#include "Definitions.h"
#include <glm/glm.hpp>

namespace V3D
{

  struct Face
  {
    void addVertex(double x, double y, double z)
    {
      vertices.emplace_back(x, y, z);
    }

    std::vector<glm::vec3> vertices;
  };

  class Volume
  {
  public:

    Volume() : faceEnded(true) {}

    void initFace()
    {
      Face newFace;
      faces.push_back(newFace);

      faceEnded = false;
    }

    void addVertex(double x, double y, double z)
    {
      if (faceEnded) 
      {
        std::cout << "[Volume] Tried to add vertex to non initialized face!" << std::endl;
      }

      faces.back().addVertex(x, y, z);
    }

    void endFace()
    {
      faceEnded = true;
    }

    std::vector<Face> getFaces()
    {
      return faces;
    }

  private:
    std::vector<Face> faces;
    bool faceEnded;
  };

}