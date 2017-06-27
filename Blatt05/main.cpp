#include <iostream>
#include <vector>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Sphere.h"
#include "Line.h"
#include "BoundingBox.h"
#include "KontrollPolygon.h"
#include "BezierKurve.h"

using namespace cg;
using namespace glm;

#define SCHWARZ		glm::vec3(0.0f, 0.0f, 0.0f)

#define	DUNKELBLAU	glm::vec3(0.0f, 0.0f, 0.5f)
#define	GRUEN		glm::vec3(0.0f, 0.5f, 0.0f)
#define	TEAL		glm::vec3(0.0f, 0.5f, 0.5f)
#define	BRAUN		glm::vec3(0.5f, 0.0f, 0.0f)
#define	PURPUR		glm::vec3(0.5f, 0.0f, 0.5f)
#define	OLIVE		glm::vec3(0.5f, 0.5f, 0.0f)
#define	GRAU		glm::vec3(0.5f, 0.5f, 0.5f)

#define SILBER		glm::vec3(0.75f, 0.75f, 0.75f)

#define BLAU		glm::vec3(0.0f, 0.0f, 1.0f)
#define HELLGRUEN	glm::vec3(0.0f, 1.0f, 0.0f)
#define CYAN		glm::vec3(0.0f, 1.0f, 1.0f)
#define ROT			glm::vec3(1.0f, 0.0f, 0.0f)
#define MAGENTA		glm::vec3(1.0f, 0.0f, 1.0f)
#define GELB		glm::vec3(1.0f, 1.0f, 0.0f)
#define WEISS		glm::vec3(1.0f, 1.0f, 1.0f)

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900

void transformObjs();

const GLfloat sunRotationSpeed = 0.1f;
const GLfloat earthRadius = 4.0f;
const GLfloat moonRadius = 2.0f;
const GLfloat marsRadius = -5.0f;

//change
cg::Sphere* earth = nullptr;
cg::Sphere* mars = nullptr;
cg::Sphere* moon1 = nullptr;
cg::Sphere* moon2 = nullptr;
cg::Sphere* moon3 = nullptr;
cg::Sphere* moon4 = nullptr;
cg::Sphere* moon5 = nullptr;
cg::Sphere* moon6 = nullptr;
cg::Sphere* moon7 = nullptr;

//change
cg::Line* sunLine = nullptr;
cg::Line* earthLine = nullptr;
cg::Line* marsLine = nullptr;

BoundingBox* boundingBox = nullptr;
KontrollPolygon* kPolygon = nullptr;
BezierKurve* bezierKurve = nullptr;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

//change
cg::Sphere* createPlanet(float angleX, float angleY, float angleZ, float size, glm::vec3 pos, glm::vec3 color) {
	cg::Sphere* sphere = new cg::Sphere(color);
	sphere->model = glm::translate(sphere->model, pos);
	sphere->model = glm::rotate(sphere->model, angleX, glm::vec3(1.0f, 0.0f, 0.0f));
	sphere->model = glm::rotate(sphere->model, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
	sphere->model = glm::rotate(sphere->model, angleZ, glm::vec3(0.0f, 0.0f, 1.0f));
	sphere->model = glm::scale(sphere->model, glm::vec3(size));
	return sphere;
}

//change
cg::Line* createPlanetLine(float angleX, float angleY, float angleZ, float size, glm::vec3 pos, glm::vec3 color) {
	cg::Line* line = new cg::Line(color);
	line->model = glm::translate(line->model, pos);
	line->model = glm::rotate(line->model, angleX, glm::vec3(1.0f, 0.0f, 0.0f));
	line->model = glm::rotate(line->model, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
	line->model = glm::rotate(line->model, angleZ, glm::vec3(0.0f, 0.0f, 1.0f));
	line->model = glm::scale(line->model, glm::vec3(size));
	return line;
}

/*
Release resources on termination.
*/
//change
void release() {
	delete earth;
	delete mars;
	delete sunLine;
	delete earthLine;
	delete marsLine;
	delete moon1;
	delete moon2;
	delete moon3;
	delete moon4;
	delete moon5;
	delete moon6;
	delete moon7;

	delete bezierKurve;
}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init() {
	// OpenGL stuff. Set "background" color and enable depth testing.
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Width of the lines.
	glLineWidth(1.0f);

	// Construct view matrix.
	//change
	//eye 0,0,10 up 0,1,0
	glm::vec3 eye(0.0f, 0.0f, 15.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	view = glm::lookAt(eye, center, up);

	// Create pyramid object.
	//change
	try {
		sunLine = new Line(GELB, 2.0f);
		earthLine = new Line(BLAU, 2.0f);
		marsLine = new Line(ROT, 2.0f);
		earth = new Sphere(BLAU);
		mars = new Sphere(ROT);
		moon1 = new Sphere(WEISS);
		moon2 = new Sphere(HELLGRUEN);
		moon3 = new Sphere(CYAN);
		moon4 = new Sphere(MAGENTA);
		moon5 = new Sphere(SILBER);
		moon6 = new Sphere(BRAUN);
		moon7 = new Sphere(SCHWARZ);

		boundingBox = new BoundingBox(GELB);
		kPolygon = new KontrollPolygon("UB_Bezier_1.obj", GELB);
		GLfloat scaleX = 0, scaleY = 0, scaleZ = 0;
		GLfloat lengthX = 0, lengthY = 0, lengthZ = 0;
		GLfloat lengthkX = 0, lengthkY = 0, lengthkZ = 0;
		BoundingBox* kBBox = kPolygon->getBBox();
		lengthkX = fabs(kBBox->getXMin()) + fabs(kBBox->getXMax());
		lengthkY = fabs(kBBox->getYMin()) + fabs(kBBox->getYMax());
		lengthkZ = fabs(kBBox->getZMin()) + fabs(kBBox->getZMax());
		lengthX = fabs(boundingBox->getXMin()) + fabs(boundingBox->getXMax());
		lengthY = fabs(boundingBox->getYMin()) + fabs(boundingBox->getYMax());
		lengthZ = fabs(boundingBox->getZMin()) + fabs(boundingBox->getZMax());
		if (lengthkX == 0) {
			scaleX = 1;
		} else {
			scaleX = lengthX / lengthkX;
		}

		if (lengthkY == 0) {
			scaleY = 1;
		}
		else {
			scaleY = lengthY / lengthkY;
		}

		if (lengthkZ == 0) {
			scaleZ = 1;
		}
		else {
			scaleZ = lengthZ / lengthkZ;
		}
		kPolygon->scale(vec3(scaleX, scaleY, scaleZ));
		bezierKurve = new BezierKurve(kPolygon, 0.5, GELB);

		earthLine->model = translate(earthLine->model, vec3(earthRadius, 0.0f, 0.0f));
		earthLine->model = scale(earthLine->model, vec3(0.5f));
		earth->model = translate(earth->model, vec3(earthRadius, 0.0f, 0.0f));
		earth->model = scale(earth->model, vec3(0.5f));
		
		moon1->model = translate(moon1->model, vec3(earthRadius, 0.0f, 0.0f));
		moon1->model = rotate(moon1->model, radians(30.0f), vec3(0.0f, 1.0f, 0.0f));
		moon1->model = translate(moon1->model, vec3(moonRadius, 0.0f, 0.0f));
		moon1->model = scale(moon1->model, vec3(0.25f));

		moon2->model = translate(moon2->model, vec3(earthRadius, 0.0f, 0.0f));
		moon2->model = rotate(moon2->model, radians(150.0f), vec3(0.0f, 1.0f, 0.0f));
		moon2->model = translate(moon2->model, vec3(moonRadius, 0.0f, 0.0f));
		moon2->model = scale(moon2->model, vec3(0.25f));
		
		moon3->model = translate(moon3->model, vec3(earthRadius, 0.0f, 0.0f));
		moon3->model = rotate(moon3->model, radians(270.0f), vec3(0.0f, 1.0f, 0.0f));
		moon3->model = translate(moon3->model, vec3(moonRadius, 0.0f, 0.0f));
		moon3->model = scale(moon3->model, vec3(0.25f));
				
		marsLine->model = translate(marsLine->model, vec3(marsRadius, 0.0f, 0.0f));
		marsLine->model = rotate(marsLine->model, radians(45.0f), vec3(0, 0, 1.0f));
		marsLine->model = scale(marsLine->model, vec3(0.5f));
		mars->model = translate(mars->model, vec3(marsRadius, 0.0f, 0.0f));
		mars->model = rotate(mars->model, radians(45.0f), vec3(0, 0, 1.0f));
		mars->model = scale(mars->model, vec3(0.5f));
		
		
		moon4->model = translate(moon4->model, vec3(marsRadius, 0.0f, 0.0f));
		moon4->model = rotate(moon4->model, radians(45.0f), vec3(0, 0, 1.0f));
		moon4->model = rotate(moon4->model, radians(0.0f), vec3(0.0f, 1.0f, 0.0f));
		moon4->model = translate(moon4->model, vec3(moonRadius, 0, 0));
		moon4->model = scale(moon4->model, vec3(0.1f));
		
		moon5->model = translate(moon5->model, vec3(marsRadius, 0.0f, 0.0f));
		moon5->model = rotate(moon5->model, radians(45.0f), vec3(0, 0, 1.0f));
		moon5->model = rotate(moon5->model, radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
		moon5->model = translate(moon5->model, vec3(moonRadius, 0, 0));
		moon5->model = scale(moon5->model, vec3(0.1f));
		
		moon6->model = translate(moon6->model, vec3(marsRadius, 0.0f, 0.0f));
		moon6->model = rotate(moon6->model, radians(45.0f), vec3(0, 0, 1.0f));
		moon6->model = rotate(moon6->model, radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
		moon6->model = translate(moon6->model, vec3(moonRadius, 0, 0));
		moon6->model = scale(moon6->model, vec3(0.1f));

		moon7->model = translate(moon7->model, vec3(marsRadius, 0.0f, 0.0f));
		moon7->model = rotate(moon7->model, radians(45.0f), vec3(0, 0, 1.0f));
		moon7->model = rotate(moon7->model, radians(270.0f), vec3(0.0f, 1.0f, 0.0f));
		moon7->model = translate(moon7->model, vec3(moonRadius, 0, 0));
		moon7->model = scale(moon7->model, vec3(0.1f));
		
	} catch (const std::exception& e) {
		release();
		std::cerr << e.what() << std::endl;
		return false;
	}

	//change
	std::cout << "Use x, y, z to rotate the sphere" << std::endl;
	std::cout << "Use + and - to scale the sphere" << std::endl;
	return true;
}

/*
 Rendering.
 */
//change
void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	//boundingBox->render(view, projection);
	//kPolygon->render(view, projection);
	bezierKurve->render(view, projection);

	moon1->render(view, projection);
	moon2->render(view, projection);
	
	earth->render(view, projection);
	earthLine->render(view, projection);
	moon3->render(view, projection);
	
	
	mars->render(view, projection);
	marsLine->render(view, projection);
	moon4->render(view, projection);
	moon5->render(view, projection);
	moon6->render(view, projection);
	moon7->render(view, projection);
	transformObjs();
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
	switch (codepoint) {
	case '+':
		boundingBox->model = scale(boundingBox->model, glm::vec3(1.2f));
		kPolygon->scale(vec3(1.2f));
		bezierKurve->model = scale(bezierKurve->model, vec3(1.2f));
		break;
	case '-':
		boundingBox->model = scale(boundingBox->model, glm::vec3(0.8f));
		kPolygon->scale(vec3(0.8f));
		bezierKurve->model = scale(bezierKurve->model, vec3(0.8f));
		break;
	case 'b':
		bezierKurve->andereSchrittweite(true);
		bezierKurve->refresh(GELB);
		render();
		break;
	case 'B':
		bezierKurve->andereSchrittweite(false);
		bezierKurve->refresh(GELB);
		render();
		break;
	}
}

void transformObjs() {
	earth->model = translate(earth->model, vec3(-2.0f * earthRadius, 0.0f, 0.0f));
	earth->model = rotate(earth->model, radians(sunRotationSpeed), vec3(0.0f, 1.0f, 0.0f));
	earth->model = translate(earth->model, vec3(2.0f * earthRadius, 0.0f, 0.0f));
	earthLine->model = translate(earthLine->model, vec3(-2.0f * earthRadius, 0.0f, 0.0f));
	earthLine->model = rotate(earthLine->model, radians(sunRotationSpeed), vec3(0.0f, 1.0f, 0.0f));
	earthLine->model = translate(earthLine->model, vec3(2.0f * earthRadius, 0.0f, 0.0f));

	moon1->model = translate(moon1->model, vec3(-4.0f * moonRadius, 0.0f, 0.0f));
	moon1->model = rotate(moon1->model, radians(-30.0f), vec3(0.0f, 1.0f, 0.0f));
	moon1->model = translate(moon1->model, vec3(-4.0f * earthRadius, 0.0f, 0.0f));
	moon1->model = rotate(moon1->model, radians(sunRotationSpeed), vec3(0.0f, 1.0f, 0.0f));
	moon1->model = translate(moon1->model, vec3(4.0f * earthRadius, 0.0f, 0.0f));
	moon1->model = rotate(moon1->model, radians(30.0f), vec3(0.0f, 1.0f, 0.0f));
	moon1->model = translate(moon1->model, vec3(4.0f * moonRadius, 0.0f, 0.0f));

	moon2->model = translate(moon2->model, vec3(-4.0f * moonRadius, 0.0f, 0.0f));
	moon2->model = rotate(moon2->model, radians(-150.0f), vec3(0.0f, 1.0f, 0.0f));
	moon2->model = translate(moon2->model, vec3(-4.0f * earthRadius, 0.0f, 0.0f));
	moon2->model = rotate(moon2->model, radians(sunRotationSpeed), vec3(0.0f, 1.0f, 0.0f));
	moon2->model = translate(moon2->model, vec3(4.0f * earthRadius, 0.0f, 0.0f));
	moon2->model = rotate(moon2->model, radians(150.0f), vec3(0.0f, 1.0f, 0.0f));
	moon2->model = translate(moon2->model, vec3(4.0f * moonRadius, 0.0f, 0.0f));

	moon3->model = translate(moon3->model, vec3(-4.0f * moonRadius, 0.0f, 0.0f));
	moon3->model = rotate(moon3->model, radians(-270.0f), vec3(0.0f, 1.0f, 0.0f));
	moon3->model = translate(moon3->model, vec3(-4.0f * earthRadius, 0.0f, 0.0f));
	moon3->model = rotate(moon3->model, radians(sunRotationSpeed), vec3(0.0f, 1.0f, 0.0f));
	moon3->model = translate(moon3->model, vec3(4.0f * earthRadius, 0.0f, 0.0f));
	moon3->model = rotate(moon3->model, radians(270.0f), vec3(0.0f, 1.0f, 0.0f));
	moon3->model = translate(moon3->model, vec3(4.0f * moonRadius, 0.0f, 0.0f));

	mars->model = rotate(mars->model, radians(-45.0f), vec3(0.0f, 0.0f, 1.0f));
	mars->model = translate(mars->model, vec3(-2 * marsRadius, 0.0f, 0.0f));
	mars->model = rotate(mars->model, radians(sunRotationSpeed), vec3(0.0f, 1.0f, 0.0f));
	mars->model = translate(mars->model, vec3(2 * marsRadius, 0.0f, 0.0f));
	mars->model = rotate(mars->model, radians(45.0f), vec3(0.0f, 0.0f, 1.0f));

	marsLine->model = rotate(marsLine->model, radians(-45.0f), vec3(0.0f, 0.0f, 1.0f));
	marsLine->model = translate(marsLine->model, vec3(-2 * marsRadius, 0.0f, 0.0f));
	marsLine->model = rotate(marsLine->model, radians(sunRotationSpeed), vec3(0.0f, 1.0f, 0.0f));
	marsLine->model = translate(marsLine->model, vec3(2 * marsRadius, 0.0f, 0.0f));
	marsLine->model = rotate(marsLine->model, radians(45.0f), vec3(0.0f, 0.0f, 1.0f));

	moon4->model = rotate(moon4->model, radians(-0.0f), vec3(0.0f, 1.0f, 0.0f));
	moon4->model = translate(moon4->model, vec3(-10 * moonRadius, 0, 0));
	moon4->model = rotate(moon4->model, radians(-45.0f), vec3(0, 0, 1.0f));
	moon4->model = translate(moon4->model, vec3(-10 * marsRadius, 0.0f, 0.0f));
	moon4->model = rotate(moon4->model, radians(sunRotationSpeed), vec3(0.0f, 1.0f, 0.0f));
	moon4->model = translate(moon4->model, vec3(10 * marsRadius, 0.0f, 0.0f));
	moon4->model = rotate(moon4->model, radians(45.0f), vec3(0, 0, 1.0f));
	moon4->model = translate(moon4->model, vec3(10 * moonRadius, 0, 0));
	moon4->model = rotate(moon4->model, radians(0.0f), vec3(0.0f, 1.0f, 0.0f));

	moon5->model = rotate(moon5->model, radians(-90.0f), vec3(0.0f, 1.0f, 0.0f));
	moon5->model = translate(moon5->model, vec3(-12 * moonRadius, 0, 0));
	moon5->model = rotate(moon5->model, radians(-45.0f), vec3(0, 0, 1.0f));
	moon5->model = translate(moon5->model, vec3(-12 * marsRadius, 0.0f, 0.0f));
	moon5->model = rotate(moon5->model, radians(sunRotationSpeed), vec3(0.0f, 1.0f, 0.0f));
	moon5->model = translate(moon5->model, vec3(12 * marsRadius, 0.0f, 0.0f));
	moon5->model = rotate(moon5->model, radians(45.0f), vec3(0, 0, 1.0f));
	moon5->model = translate(moon5->model, vec3(12 * moonRadius, 0, 0));
	moon5->model = rotate(moon5->model, radians(90.0f), vec3(0.0f, 1.0f, 0.0f));

	moon6->model = rotate(moon6->model, radians(-180.0f), vec3(0.0f, 1.0f, 0.0f));
	moon6->model = translate(moon6->model, vec3(-18 * moonRadius, 0, 0));
	moon6->model = rotate(moon6->model, radians(-45.0f), vec3(0, 0, 1.0f));
	moon6->model = translate(moon6->model, vec3(-18 * marsRadius, 0.0f, 0.0f));
	moon6->model = rotate(moon6->model, radians(sunRotationSpeed), vec3(0.0f, 1.0f, 0.0f));
	moon6->model = translate(moon6->model, vec3(18 * marsRadius, 0.0f, 0.0f));
	moon6->model = rotate(moon6->model, radians(45.0f), vec3(0, 0, 1.0f));
	moon6->model = translate(moon6->model, vec3(18 * moonRadius, 0, 0));
	moon6->model = rotate(moon6->model, radians(180.0f), vec3(0.0f, 1.0f, 0.0f));

	moon7->model = rotate(moon7->model, radians(-270.0f), vec3(0.0f, 1.0f, 0.0f));
	moon7->model = translate(moon7->model, vec3(-16 * moonRadius, 0, 0));
	moon7->model = rotate(moon7->model, radians(-45.0f), vec3(0, 0, 1.0f));
	moon7->model = translate(moon7->model, vec3(-16 * marsRadius, 0.0f, 0.0f));
	moon7->model = rotate(moon7->model, radians(sunRotationSpeed), vec3(0.0f, 1.0f, 0.0f));
	moon7->model = translate(moon7->model, vec3(16 * marsRadius, 0.0f, 0.0f));
	moon7->model = rotate(moon7->model, radians(45.0f), vec3(0, 0, 1.0f));
	moon7->model = translate(moon7->model, vec3(16 * moonRadius, 0, 0));
	moon7->model = rotate(moon7->model, radians(270.0f), vec3(0.0f, 1.0f, 0.0f));
}

int main(int argc, char** argv) {
	GLFWwindow* window;

	// Initialize glfw library (window toolkit).
	if (!glfwInit()) {
		return -1;
	}

	// Create a window and opengl context (version 3.3 core profile).
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Turn this on for smoother lines.
	// glfwWindowHint(GLFW_SAMPLES, 8);
	
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sphere example", nullptr, nullptr);
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