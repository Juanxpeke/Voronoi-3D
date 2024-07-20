#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace V3D
{

  class OFFConstructor
  {
  public:

    OFFConstructor() = default;

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

    void write(const std::string& path)
    {
      std::ofstream out(path);
      
      if (!out.is_open())
      {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
      }

      out << "OFF\n";
      out << vertices.size() << " " << faces.size() << " 0\n";

      for (const auto& vertex : vertices)
      {
        out << vertex[0] << " " << vertex[1] << " " << vertex[2] << "\n";
      }

      for (const auto& face : faces)
      {
        out << face.size();
        for (const auto& index : face)
        {
          out << " " << index;
        }
        out << "\n";
      }

      out.close();
    }

  private:
    std::vector<std::vector<double>> vertices;
    std::vector<std::vector<int>> faces;
    std::vector<int> currentFace;
  };

}


