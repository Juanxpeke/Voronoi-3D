#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Volume.h"

#define BIG_SIZE 48000
#define POSITION_LOCATION 0

namespace V3D
{
  typedef glm::vec3 MeshVertex;

  class Mesh
  {
  public:
    Mesh()
    {
      glCreateVertexArrays(1, &VAO);
      glCreateBuffers(1, &VBO);
      glCreateBuffers(1, &EBO);

      glBindVertexArray(VAO);

      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, BIG_SIZE * sizeof(MeshVertex), nullptr, GL_STATIC_DRAW);

      glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
      glEnableVertexAttribArray(POSITION_LOCATION);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, BIG_SIZE * sizeof(unsigned int), nullptr, GL_STATIC_DRAW);

      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

      color = { 1.0, 1.0, 1.0 };
    }

    void bind() const
    {
      glBindVertexArray(VAO);
    }

    void unbind() const
    {
      glBindVertexArray(0);
    }

    unsigned int getIndicesCount() const
    {
      return indicesSize;
    }

    glm::vec3 getColor() const
    {
      return color;
    }

    void fillFromVolume(Volume volume)
    {
      const std::vector<Face> faces = volume.getFaces();

      std::vector<MeshVertex> vertices;
      std::vector<unsigned int> indices;
      
      for (int f = 0; f < faces.size(); f++)
      {

        const Face face = faces[f];
        const glm::vec3 rootVertex = face.vertices[0];

        vertices.push_back(rootVertex);
        unsigned int rootVertexIndex = vertices.size() - 1;

        for (int v = 1; v < face.vertices.size() - 1; v++)
        {
          vertices.push_back(face.vertices[v]);
          vertices.push_back(face.vertices[v + 1]);

          indices.push_back(rootVertexIndex);
          indices.push_back(rootVertexIndex + v);
          indices.push_back(rootVertexIndex + v +1);
        }
      }

      glBindVertexArray(VAO);

      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(MeshVertex), vertices.data());

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), indices.data());

      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

      indicesSize = indices.size();
    }

  private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    unsigned int indicesSize;

    glm::vec3 color;
  };

}