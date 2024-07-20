#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "PathManager.h"
#include "DelaunayVoronoiManager.h"
#include "PointsGenerator.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Camera.h"

int width = 720;
int height = 720;
char title[256];

void updateInputs(GLFWwindow* window, V3D::Camera& camera)
{
  float dt = 0.016;
  const float cameraSpeed = 14.4f;
  const float cameraAngularSpeed = 2.0f;

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera.translate(camera.getFrontVector() * dt * cameraSpeed);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera.translate(camera.getRightVector() * dt * -cameraSpeed);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.translate(camera.getFrontVector() * dt * -cameraSpeed);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera.translate(camera.getRightVector() * dt * cameraSpeed);
	}
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    camera.translate(glm::vec3(0.0f, 1.0f, 0.0f) * dt * cameraSpeed);
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    camera.translate(glm::vec3(0.0f, 1.0f, 0.0f) * dt * -cameraSpeed);
  }
  // Rotation
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    camera.rotate(camera.getRightVector(), dt * cameraAngularSpeed);
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    camera.rotate(glm::vec3(0.0f, 1.0f, 0.0f), dt * cameraAngularSpeed);
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    camera.rotate(camera.getRightVector(), dt * -cameraAngularSpeed);
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    camera.rotate(glm::vec3(0.0f, 1.0f, 0.0f), dt * -cameraAngularSpeed);
  }
}

int main()
{
  const std::string triangulationPath = V3D::filePath("assets/output/ComplexTriangulation.off");
  const std::string voronoiPath = V3D::filePath("assets/output/ComplexVoronoi.off");

  V3D::DelaunayVoronoiManager dvm;

  dvm.insertPoint(Point(0, 0, 0));
  dvm.insertPoint(Point(1, 0, 0));
  dvm.insertPoint(Point(1, 0, 1));
  dvm.insertPoint(Point(0, 0, 1));

  dvm.insertPoint(Point(0, 1, 0));
  dvm.insertPoint(Point(1, 1, 0));
  dvm.insertPoint(Point(1, 1, 1));
  dvm.insertPoint(Point(0, 1, 1));

  //dvm.insertPoint(Point(0.5, 0.5, 0.5));

  size_t innerPointsAmount = 12;

  std::vector<Point> innerPoints = V3D::generatePointsInCube(0.5, innerPointsAmount, Point(0.5, 0.5, 0.5));

  for (const Point& point : innerPoints)
  {
    //dvm.insertPoint(point);
  }

  dvm.generateTriangulationLCC();
  dvm.generateVoronoiLCC();

  std::vector<V3D::Volume> triangulationVolumes = dvm.writeTriangulationToOFF(triangulationPath);
  std::vector<V3D::Volume> voronoiVolumes = dvm.writeVoronoiToOFF(voronoiPath);

	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
  sprintf(title, "Complex");
	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

	// Error check if the window fails to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	glViewport(0, 0, width, height);

  V3D::Camera camera(width, height);
  camera.setTranslation({ 0, 0, 0 });

  V3D::ShaderProgram program;

  std::vector<V3D::Mesh*> meshes;

  for (V3D::Volume& volume : triangulationVolumes)
  {
    V3D::Mesh* mesh = new V3D::Mesh();

    volume.print();

    mesh->fillFromVolume(volume);

    meshes.push_back(mesh);
  }

  std::cout << "Meshes count: " << meshes.size() << std::endl;

  program.bind();

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

    updateInputs(window, camera);

		glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 viewProjection = camera.getViewProjection();
    glm::vec3 cameraPosition = camera.getLocalTranslation();

    glUniformMatrix4fv(glGetUniformLocation(program.getID(), "viewProjection"), 1, GL_FALSE, glm::value_ptr(viewProjection));
    glUniform3fv(glGetUniformLocation(program.getID(), "cameraPosition"), 1, glm::value_ptr(cameraPosition));

    for (const V3D::Mesh* mesh : meshes)
    {
      mesh->bind();

      // Set uniforms
      glm::vec3 color = mesh->getColor();
      glUniform3fv(glGetUniformLocation(program.getID(), "color"), 1, glm::value_ptr(color));

      // Draw the triangle using the GL_TRIANGLES primitive
      glDrawElements(GL_TRIANGLES, mesh->getIndicesCount(), GL_UNSIGNED_INT, nullptr);

      mesh->unbind();
    }
		
    glfwSwapBuffers(window);
	}

  program.unbind();

  for (V3D::Mesh* mesh : meshes)
  {
    delete mesh;
  }

  // Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

  return 0;
}