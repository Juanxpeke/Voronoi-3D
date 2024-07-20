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

    void print()
    {
      std::cout << "Volume with faces:" << std::endl;

      for (int i = 0; i < faces.size(); i++)
      {
        std::cout << "Face " << i << " with " << faces[i].vertices.size() << " vertices (vertex 0 = " << faces[i].vertices[0][0] << std::endl;
      }
    }

  private:
    std::vector<Face> faces;
    bool faceEnded;
  };

}