#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "AbstractCube.h"
#include "CubeSharp.h"
#include "CubeSmooth.h"


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

cg::AbstractCube* cubeLeft = nullptr;
cg::AbstractCube* cubeRight = nullptr;

cg::AbstractCube* manipulate = nullptr;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

/*
Release resources on termination.
*/
void release() {
	delete cubeRight;
	delete cubeLeft;
}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init() {
	// OpenGL stuff. Set "background" color and enable depth testing.
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Construct view matrix.
	glm::vec3 eye(0.0f, 0.0f, 8.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(eye, center, up);

	// Create cube objects.
	try {
		cubeLeft = new cg::CubeSharp(glm::vec3(1.0f, 0.1f, 0.1f));
		cubeRight = new cg::CubeSmooth(glm::vec3(0.1f, 0.1f, 1.0f));

		manipulate = cubeLeft;
	} catch (const std::exception& e) {
		release();
		std::cerr << e.what() << std::endl;
		return false;
	}

	// Manipulate models.
	auto& modelLeft = cubeLeft->getModel();
	modelLeft = glm::translate(modelLeft, glm::vec3(-2.5, 0.0f, 0.0f));

	auto& modelRight = cubeRight->getModel();
	modelRight = glm::translate(modelRight, glm::vec3(2.5, 0.0f, 0.0f));

	// Set light direction (only an example).
	auto lightDirection = glm::normalize(glm::vec3(-1.0f, 1.0f, 4.0f));
	cubeLeft->setLightDirection(lightDirection);
	cubeRight->setLightDirection(lightDirection);

	std::cout << "Use space to switch between cubes" << std::endl;
	std::cout << "Use x, y, z to rotate the currently selected cube" << std::endl;
	std::cout << "Use + and - to scale the currently selected cube" << std::endl;
	std::cout << "Use n to enable / disable normals for the currently selected cube" << std::endl;

	return true;
}

/*
 Rendering.
 */
void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cubeLeft->render(view, projection);
	cubeRight->render(view, projection);
}

/*
 Resize callback.
 */
void resize(GLFWwindow* window, int width, int height) {
	height = height < 1 ? 1 : height;
	glViewport(0, 0, width, height);

	// Construct projection matrix.
	projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
}

/*
 Callback for char input.
 */
void keyboard(GLFWwindow* window, unsigned int codepoint) {
	auto& model = manipulate->getModel();

	switch (codepoint) 	{
	case '+':
		model = glm::scale(model, glm::vec3(1.2f));
		break;
	case '-':
		model = glm::scale(model, glm::vec3(0.8f));
		break;
	case 'x':
		model = glm::rotate(model, 0.1f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		break;
	case 'X':
		model = glm::rotate(model, -0.1f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		break;
	case 'y':
		model = glm::rotate(model, 0.1f, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		break;
	case 'Y':
		model = glm::rotate(model, -0.1f, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		break;
	case 'z':
		model = glm::rotate(model, 0.1f, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)));
		break;
	case 'Z':
		model = glm::rotate(model, -0.1f, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)));
		break;
	case ' ':
		// #quickanddirty
		manipulate = manipulate == cubeLeft ? cubeRight : cubeLeft;
		break;
	case 'n':
		manipulate->toggleRenderNormals();
		break;
	}
}

int main(int argc, char** argv) {
	GLFWwindow* window;

	// Initialize glfw library (window toolkit).
	if (!glfwInit())
		return -1;

	// Create a window and opengl context (version 3.3 core profile).
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cube example", nullptr, nullptr);
	
	if (!window) {
		glfwTerminate();
		return -2;
	}

	// Make the window's opengl context current.
	glfwMakeContextCurrent(window);

	// Load opengl extensions
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		glfwTerminate();
		return -3;
	}

	// Set callbacks for resize and keyboard events.
	glfwSetWindowSizeCallback(window, resize);
	glfwSetCharCallback(window, keyboard);

	if (!init()) {
		release();
		glfwTerminate();
		return -4;
	}

	// We have to call resize once for a proper setup.
	resize(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Loop until the user closes the window.
	while (!glfwWindowShouldClose(window)) {
		render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up everything on termination.
	release();
	glfwTerminate();
	return 0;
}