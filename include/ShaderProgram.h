#pragma once

#include <string>
#include <glad/glad.h>

namespace V3D
{

  // Shaders
  std::string vertexShaderCode = R"(
  #version 330 core
  
  uniform mat4 model;
  uniform mat4 viewProjection;
  uniform vec3 cameraPosition;

  in vec3 position;

  void main() {
    gl_Position = viewProjection * mat4(1.0) * vec4(position.x, position.y, position.z, 1.0);
  }
  )";
  
  std::string fragmentShaderCode = R"(
  #version 330 core

  uniform vec3 color;

  out vec4 outColor;

  void main() {
    outColor = vec4(color, 1.0f);
  }
  )";

  class ShaderProgram
  {
  public:

    ShaderProgram()
    {
      // Vertex shader
      const char* vertexShaderSource = vertexShaderCode.c_str();
      GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
      glCompileShader(vertexShader);

      // Fragment shader
      const char* fragmentShaderSource = fragmentShaderCode.c_str();
      GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
      glCompileShader(fragmentShader);

      // Shader program
      ID = glCreateProgram();
      glAttachShader(ID, vertexShader);
      glAttachShader(ID, fragmentShader);
      glLinkProgram(ID);

      // Delete the now useless Vertex and Fragment Shader Objects
      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);
    }

    void bind() const
    {
      glUseProgram(ID);
    }

    void unbind() const
    {
      glUseProgram(0);
    }
    
    unsigned int getID() const
    {
      return ID;
    }

  private:
    unsigned int ID;

  };

}