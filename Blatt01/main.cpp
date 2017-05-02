#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"
#include "main.h"

using namespace std;
using namespace glm;
using namespace cg;
using namespace GLSLShader;

int main(int argc, char** argv) {
	GLFWwindow* window;

	// Initialize glfw library (window toolkit).
	if (!glfwInit()) {
		return -1;
	}
	
	// Create a window and opengl context (version 4.5 core profile).
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Aufgabenblatt 01", nullptr, nullptr);
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

// Initialization. Should return true if everything is ok and false if something went wrong.
bool init() {
	// OpenGL stuff. Set "background" color and enable depth testing.
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	// Construct view matrix.
	vec3 eye(0.0f, 0.0f, 4.0f);
	vec3 center(0.0f, 0.0f, 0.0f);
	vec3 up(0.0f, 1.0f, 0.0f);
	view = lookAt(eye, center, up);

	// Create a shader program and set light direction.
	if (!program.compileShaderFromFile("shader/simple.vert", VERTEX) 
		|| !program.compileShaderFromFile("shader/simple.frag", FRAGMENT)
		|| !program.link()) {
		cerr << program.log();
		return false;
	}
	initNEck(360);
	return true;
}

void initNEck(int n) {
	data dataNEck;
	dataNEck.vertices.push_back(vec3(0.0f, 0.0f, 0.0f));
	dataNEck.colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	for (int i = 0; i < n; i++) {
		// Umlaufenden Winkel berechnen
		double winkel = double(i) / double(n) * 2.0f * M_PI;
		// Kreisfunktionen Sinus und Cosinus verwenden
		double x = sin(winkel);
		double y = cos(winkel);
		// Punkt setzen
		dataNEck.vertices.push_back(vec3(x, y, 0.0f));
		dataNEck.colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	}
	for (int i = 1; i < n; i++) {
		dataNEck.indices.push_back(0);
		dataNEck.indices.push_back(i);
		dataNEck.indices.push_back(i +1);
	}
	dataNEck.indices.push_back(0);
	dataNEck.indices.push_back(n);
	dataNEck.indices.push_back(1);
	nEck.n = n;
	nEck = initObjekt(dataNEck, nEck);
}

void initWurfel() {
	data dataWurfel;
	dataWurfel.vertices.push_back(vec3(-0.5f, -0.5f, 0.5f));
	dataWurfel.vertices.push_back(vec3(0.5f, -0.5f, 0.5f));
	dataWurfel.vertices.push_back(vec3(0.5f, 0.5f, 0.5f));
	dataWurfel.vertices.push_back(vec3(-0.5f, 0.5f, 0.5f));
	
	dataWurfel.colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	dataWurfel.colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	dataWurfel.colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	dataWurfel.colors.push_back(vec3(1.0f, 1.0f, 1.0f));

	dataWurfel.vertices.push_back(vec3(0.5f, -0.5f, -0.5f));
	dataWurfel.vertices.push_back(vec3(-0.5f, -0.5f, -0.5f));
	dataWurfel.vertices.push_back(vec3(-0.5f, 0.5f, -0.5f));
	dataWurfel.vertices.push_back(vec3(0.5f, 0.5f, -0.5f));

	dataWurfel.colors.push_back(vec3(1.0f, 1.0f, 0.0f));
	dataWurfel.colors.push_back(vec3(1.0f, 1.0f, 0.0f));
	dataWurfel.colors.push_back(vec3(1.0f, 1.0f, 0.0f));
	dataWurfel.colors.push_back(vec3(1.0f, 1.0f, 0.0f));

	dataWurfel.vertices.push_back(vec3(-0.5f, -0.5f, -0.5f));
	dataWurfel.vertices.push_back(vec3(-0.5f, -0.5f, 0.5f));
	dataWurfel.vertices.push_back(vec3(-0.5f, 0.5f, 0.5f));
	dataWurfel.vertices.push_back(vec3(-0.5f, 0.5f, -0.5f));

	dataWurfel.colors.push_back(vec3(1.0f, 0.0f, 1.0f));
	dataWurfel.colors.push_back(vec3(1.0f, 0.0f, 1.0f));
	dataWurfel.colors.push_back(vec3(1.0f, 0.0f, 1.0f));
	dataWurfel.colors.push_back(vec3(1.0f, 0.0f, 1.0f));
	
	dataWurfel.vertices.push_back(vec3(0.5f, -0.5f, 0.5f));
	dataWurfel.vertices.push_back(vec3(0.5f, -0.5f, -0.5f));
	dataWurfel.vertices.push_back(vec3(0.5f, 0.5f, -0.5f));
	dataWurfel.vertices.push_back(vec3(0.5f, 0.5f, 0.5f));

	dataWurfel.colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	dataWurfel.colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	dataWurfel.colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	dataWurfel.colors.push_back(vec3(1.0f, 0.0f, 0.0f));

	dataWurfel.vertices.push_back(vec3(-0.5f, 0.5f, 0.5f));
	dataWurfel.vertices.push_back(vec3(0.5f, 0.5f, 0.5f));
	dataWurfel.vertices.push_back(vec3(0.5f, 0.5f, -0.5f));
	dataWurfel.vertices.push_back(vec3(-0.5f, 0.5f, -0.5f));

	dataWurfel.colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	dataWurfel.colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	dataWurfel.colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	dataWurfel.colors.push_back(vec3(0.0f, 1.0f, 0.0f));

	dataWurfel.vertices.push_back(vec3(0.5f, -0.5f, -0.5f));
	dataWurfel.vertices.push_back(vec3(0.5f, -0.5f, 0.5f));
	dataWurfel.vertices.push_back(vec3(-0.5f, -0.5f, 0.5f));
	dataWurfel.vertices.push_back(vec3(-0.5f, -0.5f, -0.5f));

	dataWurfel.colors.push_back(vec3(0.0f, 1.0f, 1.0f));
	dataWurfel.colors.push_back(vec3(0.0f, 1.0f, 1.0f));
	dataWurfel.colors.push_back(vec3(0.0f, 1.0f, 1.0f));
	dataWurfel.colors.push_back(vec3(0.0f, 1.0f, 1.0f));
	for (int i = 0; i < 6; i++) {
		dataWurfel.indices.push_back(i * 4);
		dataWurfel.indices.push_back(i * 4 + 1);
		dataWurfel.indices.push_back(i * 4 + 2);
		dataWurfel.indices.push_back(i * 4);
		dataWurfel.indices.push_back(i * 4 + 2);
		dataWurfel.indices.push_back(i * 4 + 3);
	}
	wurfel.n = 36;
	
	wurfel = initObjekt(dataWurfel, wurfel);
}

Object initObjekt(data objektdata, Object obj) {
	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &obj.vertexArrayObject);
	glBindVertexArray(obj.vertexArrayObject);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &obj.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, obj.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, objektdata.vertices.size() * sizeof(vec3), objektdata.vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &obj.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, obj.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, objektdata.colors.size() * sizeof(vec3), objektdata.colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &obj.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, objektdata.indices.size() * sizeof(GLushort), objektdata.indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	obj.model = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
	return obj;
}

// Rendering.
void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (isWurfel) {
		renderWurfel();
	}
	else {
		renderNEck();
	}
}

void renderNEck() {
	renderObject(nEck, nEck.n * 3);
}

void renderWurfel() {
	glClear(GL_COLOR_BUFFER_BIT);
	renderObject(wurfel, wurfel.n);
}

void renderObject(Object obj, GLint caunt) {
	// Erstelle model view projection matrix
	mat4x4 mvp = projection * view * obj.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 1 triangle.
	glBindVertexArray(obj.vertexArrayObject);
	glDrawElements(GL_TRIANGLES, caunt, GL_UNSIGNED_SHORT, 0);
	//glBindVertexArray(0);
}

// Resize callback.
void resize(GLFWwindow* window, int width, int height) {
	height = height < 1 ? 1 : height;
	glViewport(0, 0, width, height);

	// Construct projection matrix.
	projection = perspective(45.0f, (float)width / height, zNear, zFar);
}

// Callback for char input.
void keyboard(GLFWwindow* window, unsigned int codepoint) {
	int n = nEck.n;
	switch (codepoint) {
	case '+':
		if (n < 30) {
			initNEck(n + 1);
			render();
		}
		break;
	case '-':
		if (n > 3) {
			initNEck(n - 1);
			render();
		}
		break;
	case 'x':
		//wurfel.model = translate(wurfel.model, vec3(0.0f, 0.0f, -8.0f));
		wurfel.model = rotate(wurfel.model, 45.0f, vec3(0.0f, 1.0f, 0.0f));
		//wurfel.model = scale(wurfel.model, vec3(0.5f));
		renderWurfel();
		cout << "x";
		break;
	case 'y':
		wurfel.model = rotate(wurfel.model, 45.0f, vec3(1.0f, 0.0f, 0.0f));
		renderWurfel();
		cout << "y";
		break;
	case 'z':
		wurfel.model = rotate(wurfel.model, 45.0f, vec3(0.0f, 0.0f, 1.0f));
		renderWurfel();
		cout << "z";
		break;
	case '1':
		initNEck(360);
		render();
		break;
	case '2':
		initNEck(4);
		render();
		break;
	case '3':
		isWurfel = true;
		initWurfel();
		renderWurfel();
		break;
	}
}

// Release resources on termination.
void release() {
	// Shader program will be released upon program termination.
	releaseObject(nEck);
}

// Release object resources.
void releaseObject(Object& obj) {
	glDeleteVertexArrays(1, &obj.vertexArrayObject);
	glDeleteBuffers(1, &obj.indexBuffer);
	glDeleteBuffers(1, &obj.colorBuffer);
	glDeleteBuffers(1, &obj.positionBuffer);
}
