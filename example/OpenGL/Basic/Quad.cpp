#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int width = 720;
int height = 720;
char title[256];

float redColor = 0.0f;

void updateInputs(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { redColor += 0.01; }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { redColor -= 0.01; }

  if (redColor < 0) redColor = 0;
  if (redColor > 1) redColor = 1;
}

int main()
{
	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices coordinates
	GLfloat vertices[] = {
    -1.0f,  1.0f, 0.0f, // Upper left corner
		-1.0f, -1.0f, 0.0f, // Lower left corner
		 1.0f, -1.0f, 0.0f, // Lower right corner
     1.0f,  1.0f, 0.0f, // Upper right corner
		-1.0f,  1.0f, 0.0f, // Upper left corner
     1.0f, -1.0f, 0.0f  // Lower right corner
	};

  sprintf(title, "OpenGL Quad");
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

  // Shaders
  std::string vertexShaderCode = R"(
  #version 330 core
  
  in vec3 position;

  void main() {
    gl_Position = vec4(position, 1.0f);
  }
  )";
  
  std::string fragmentShaderCode = R"(
  #version 330 core

  uniform float redColor;

  out vec4 outColor;

  void main() {
    outColor = vec4(redColor, 0.0f, 0.0f, 1.0f);
  }
  )";

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
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader Objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(shaderProgram, "position"), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(glGetAttribLocation(shaderProgram, "position"));

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Specify the color of the background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

  // Bind the VAO so OpenGL knows to use it
	glBindVertexArray(VAO);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

    updateInputs(window);

		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);

    // Set uniforms
    glUniform1f(glGetUniformLocation(shaderProgram, "redColor"), redColor);

		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
    glfwSwapBuffers(window);
	}

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}