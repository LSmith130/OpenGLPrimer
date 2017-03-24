#ifndef GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLCOREARB // Tell GLFW to use modern gl header.
#endif

#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char const *argv[]) {

	using std::cout;
	using std::endl;
	using namespace std::literals::chrono_literals;

	if (!glfwInit()) {
		cout << "GLFW could not initalize" << endl;
	    return 1;
  	}

	// Prepare an OpenGL context and window

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(700, 700, "Hello Triangle", NULL, NULL);

	if (!window) {
		glfwTerminate();
        cout << "Failed to initalize OpenGL window" << endl;
		return 1;
	}
	glfwMakeContextCurrent(window);

	// Prepare the triangle

	float points[] = {
	   0.0f,  0.5f,  0.0f,
	   0.5f, -0.5f,  0.0f,
	  -0.5f, -0.5f,  0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);

	//Create Shader Program

	const char* vertexShaderSource =
		"#version 410\n"
		"in vec3 vertexPosition;"
		"out vec4 color;"
		"void main() {"
			"color = vec4(1.0, 0.0, 1.0, 1.0);"
			"gl_Position = vec4(vertexPosition, 1.0);"
		"}";
	const char* fragmentShaderSource =
		"#version 410\n"
		"in vec4 color;"
		"out vec4 frag_color;"
		"void main() {"
			"frag_color = color;"
		"}";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glBindAttribLocation(shaderProgram, 0, "vertexPosition");
	glLinkProgram(shaderProgram);


	// Main loop

	while(!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);

		glfwPollEvents();

        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);

		}

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		std::this_thread::sleep_for(6ms);
	}

	glfwTerminate();

	return 0;
}
