#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

namespace V3D
{

  class Camera
  {
  public:

    // Projection variables
    int width;
    int height;
    float FOV = 60.0f;
    float near = 0.0001f;
    float far = 100.0f;

    Camera(int width, int height) : width(width), height(height)
    {
      localTranslation = glm::vec3(0.0f);
      localRotation = glm::fquat(1.0f, 0.0f, 0.0f, 0.0f);
    }

    const glm::vec3& getLocalTranslation() const
    {
      return localTranslation;
    }

    glm::mat4 getViewProjection()
    {
      glm::mat4 view = getViewMatrix();
	    glm::mat4 projection = glm::perspective(glm::radians(FOV), (float) (width) / height, near, far);

      return projection * view;
    }

    glm::mat4 getViewMatrix() const
    {
      const glm::vec3 up = getUpVector();
      const glm::vec3 front = getFrontVector();
      return glm::lookAt(localTranslation, localTranslation + front, up);
    }

    glm::vec3 getRightVector() const
    {
      return glm::rotate(localRotation, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    
    glm::vec3 getUpVector() const
    {
      return glm::rotate(localRotation, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::vec3 getFrontVector() const
    {
      return glm::rotate(localRotation, glm::vec3(0.0f, 0.0f, -1.0f));
    }

    void translate(glm::vec3 translation)
    {
      localTranslation += translation;
    }

    void setTranslation(const glm::vec3 translation)
    {
      localTranslation = translation;
    }
    
    void rotate(glm::vec3 axis, float angle)
    {
      localRotation = glm::angleAxis(angle, axis) * localRotation;
    }

    void innerRotate(glm::vec3 axis, float angle)
    {
      localRotation = glm::rotate(localRotation, angle, axis);
    }

    void setRotation(const glm::fquat& rotation)
    {
      localRotation = rotation;
    }

  private:
    glm::vec3 localTranslation;
    glm::fquat localRotation;

  };

}