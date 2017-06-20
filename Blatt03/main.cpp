#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Sphere.h"
#include "Line.h"

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
cg::Sphere* sun = nullptr;
float sunSize = 0.8f;
float sunRotationAxisX = 0;
float sunRotationAxisY = 0;
float sunRotationAxisZ = 0;
float sunRotationAxisXFactor = 0;
float sunRotationAxisYFactor = 1.0f;
float sunRotationAxisZFactor = 0;
glm::vec3 sunColor = GELB;

//change
cg::Sphere* earth = nullptr;
float earthSize = 0.4f;
float earthAngle = 0;
float earthAngleFactor = 0.01f;
float earthRotationAxisX = 0;
float earthRotationAxisY = 0;
float earthRotationAxisZ = 0;
float earthRotationAxisXFactor = 0;
float earthRotationAxisYFactor = 1.0f;
float earthRotationAxisZFactor = 0;
float earthPosX = 3;
glm::vec3 earthPos = glm::vec3(earthPosX, 0, 0);
glm::vec3 earthColor = BLAU;

//change
cg::Sphere* mars = nullptr;
float marsSize = 0.3f;
float marsAngle = 0;
float marsAngleFactor = 0.01f;
float marsRotationAxisX = 0;
float marsRotationAxisY = 0;
float marsRotationAxisZ = 45.0f;
float marsRotationAxisXFactor = 0;
float marsRotationAxisYFactor = 1.0f;
float marsRotationAxisZFactor = 0;
float marsPosX = -5;
glm::vec3 marsPos = glm::vec3(marsPosX, 0, 0);
glm::vec3 marsColor = ROT;

//change
cg::Sphere* moon1 = nullptr;
float moon1Size = 0.1f;
float moon1Angle = 0;
float moon1AngleFactor = 0.05f;
float moon1RotationAxisX = 0;
float moon1RotationAxisY = 0;
float moon1RotationAxisZ = 0;
float moon1RotationAxisXFactor = 0;
float moon1RotationAxisYFactor = 1.0f;
float moon1RotationAxisZFactor = 0;
glm::vec3 moon1Pos = glm::vec3(1, 0, 0);
glm::vec3 moon1Color = WEISS;

//change
cg::Sphere* moon2 = nullptr;
float moon2Size = 0.1f;
float moon2Angle = 0;
float moon2AngleFactor = 0.05f;
float moon2RotationAxisX = 0;
float moon2RotationAxisY = 0;
float moon2RotationAxisZ = 0;
float moon2RotationAxisXFactor = 0;
float moon2RotationAxisYFactor = 1.0f;
float moon2RotationAxisZFactor = 0;
glm::vec3 moon2Pos = glm::vec3(-1, 0, 0);
glm::vec3 moon2Color = HELLGRUEN;

//change
cg::Sphere* moon3 = nullptr;
float moon3Size = 0.1f;
float moon3Angle = 0;
float moon3AngleFactor = 0.05f;
float moon3RotationAxisX = 0;
float moon3RotationAxisY = 0;
float moon3RotationAxisZ = 0;
float moon3RotationAxisXFactor = 0;
float moon3RotationAxisYFactor = 1.0f;
float moon3RotationAxisZFactor = 0;
glm::vec3 moon3Pos = glm::vec3(0, 0, 1);
glm::vec3 moon3Color = CYAN;

//change
cg::Sphere* moon4 = nullptr;
float moon4Size = 0.1f;
float moon4Angle = 0;
float moon4AngleFactor = 0.05f;
float moon4RotationAxisX = 0;
float moon4RotationAxisY = 0;
float moon4RotationAxisZ = 25.19f;
float moon4RotationAxisXFactor = 0;
float moon4RotationAxisYFactor = 1.0f;
float moon4RotationAxisZFactor = 0;
glm::vec3 moon4Pos = glm::vec3(1, 0, 0);
glm::vec3 moon4Color = MAGENTA;

//change
cg::Sphere* moon5 = nullptr;
float moon5Size = 0.1f;
float moon5Angle = 0;
float moon5AngleFactor = 0.05f;
float moon5RotationAxisX = 0;
float moon5RotationAxisY = 0;
float moon5RotationAxisZ = 25.19f;
float moon5RotationAxisXFactor = 0;
float moon5RotationAxisYFactor = 1.0f;
float moon5RotationAxisZFactor = 0;
glm::vec3 moon5Pos = glm::vec3(-1, 0, 0);
glm::vec3 moon5Color = SILBER;

//change
cg::Sphere* moon6 = nullptr;
float moon6Size = 0.1f;
float moon6Angle = 0;
float moon6AngleFactor = 0.05f;
float moon6RotationAxisX = 0;
float moon6RotationAxisY = 0;
float moon6RotationAxisZ = 25.19f;
float moon6RotationAxisXFactor = 0;
float moon6RotationAxisYFactor = 1.0f;
float moon6RotationAxisZFactor = 0;
glm::vec3 moon6Pos = glm::vec3(0, 0, 1);
glm::vec3 moon6Color = BRAUN;

//change
cg::Sphere* moon7 = nullptr;
float moon7Size = 0.1f;
float moon7Angle = 0;
float moon7AngleFactor = 0.05f;
float moon7RotationAxisX = 0;
float moon7RotationAxisY = 0;
float moon7RotationAxisZ = 25.19f;
float moon7RotationAxisXFactor = 0;
float moon7RotationAxisYFactor = 1.0f;
float moon7RotationAxisZFactor = 0;
glm::vec3 moon7Pos = glm::vec3(0, 0, -1);
glm::vec3 moon7Color = SCHWARZ;

//change
cg::Line* sunLine = nullptr;
cg::Line* earthLine = nullptr;
cg::Line* marsLine = nullptr;

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
	delete sun;
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
		sun = new Sphere(GELB);
		earth = new Sphere(BLAU);
		mars = new Sphere(ROT);
		moon1 = new Sphere(WEISS);
		moon2 = new Sphere(HELLGRUEN);
		moon3 = new Sphere(CYAN);
		moon4 = new Sphere(MAGENTA);
		moon5 = new Sphere(SILBER);
		moon6 = new Sphere(BRAUN);
		moon7 = new Sphere(SCHWARZ);
		
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
	
	sun->render(view, projection);
	sunLine->render(view, projection);
	
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
	
	/*
	float earthFactor = earthPosX;
	earthPos = glm::vec3(-cos(earthAngle) * earthFactor, 0, -sin(earthAngle) * earthFactor);

	earth->model = glm::scale(earth->model, glm::vec3(1 / earthSize));
	earth->model = glm::rotate(earth->model, glm::radians(-earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	earth->model = glm::translate(earth->model, earthPos);

	earthLine->model = glm::scale(earthLine->model, glm::vec3(1 / earthSize));
	earthLine->model = glm::rotate(earthLine->model, glm::radians(-earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	earthLine->model = glm::translate(earthLine->model, earthPos);

	moon1->model = glm::scale(moon1->model, glm::vec3(1 / moon1Size));
	moon1->model = glm::rotate(moon1->model, glm::radians(-earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon1->model = glm::translate(moon1->model, earthPos);
	moon1->model = glm::translate(moon1->model, -moon1Pos);

	moon2->model = glm::scale(moon2->model, glm::vec3(1 / moon2Size));
	moon2->model = glm::rotate(moon2->model, glm::radians(-earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon2->model = glm::translate(moon2->model, earthPos);
	moon2->model = glm::translate(moon2->model, -moon2Pos);

	moon3->model = glm::scale(moon3->model, glm::vec3(1 / moon3Size));
	moon3->model = glm::rotate(moon3->model, glm::radians(-earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon3->model = glm::translate(moon3->model, earthPos);
	moon3->model = glm::translate(moon3->model, -moon3Pos);

	earthAngle += earthAngleFactor;
	earthRotationAxisY += earthRotationAxisYFactor;
	earthPos = glm::vec3(cos(earthAngle) * earthFactor, 0, sin(earthAngle) * earthFactor);

	moon1Angle += moon1AngleFactor;
	moon1RotationAxisY += moon1RotationAxisYFactor;

	moon1Pos = glm::vec3(moon1Pos[0] * cos(moon1AngleFactor) - moon1Pos[2] * sin(moon1AngleFactor), moon1Pos[1], moon1Pos[2] * cos(moon1AngleFactor) + moon1Pos[0] * sin(moon1AngleFactor));
	moon2Pos = glm::vec3(moon2Pos[0] * cos(moon2AngleFactor) - moon2Pos[2] * sin(moon2AngleFactor), moon2Pos[1], moon2Pos[2] * cos(moon2AngleFactor) + moon2Pos[0] * sin(moon2AngleFactor));
	moon3Pos = glm::vec3(moon3Pos[0] * cos(moon3AngleFactor) - moon3Pos[2] * sin(moon3AngleFactor), moon3Pos[1], moon3Pos[2] * cos(moon3AngleFactor) + moon3Pos[0] * sin(moon3AngleFactor));

	moon1->model = glm::translate(moon1->model, moon1Pos);
	moon2->model = glm::translate(moon2->model, moon2Pos);
	moon3->model = glm::translate(moon3->model, moon3Pos);

	earth->model = glm::translate(earth->model, earthPos);
	earth->model = glm::rotate(earth->model, glm::radians(earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	earth->model = glm::scale(earth->model, glm::vec3(earthSize));

	earthLine->model = glm::translate(earthLine->model, earthPos);
	earthLine->model = glm::rotate(earthLine->model, glm::radians(earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	earthLine->model = glm::scale(earthLine->model, glm::vec3(earthSize));

	moon1->model = glm::translate(moon1->model, earthPos);
	moon1->model = glm::rotate(moon1->model, glm::radians(earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon1->model = glm::scale(moon1->model, glm::vec3(moon1Size));

	moon2->model = glm::translate(moon2->model, earthPos);
	moon2->model = glm::rotate(moon2->model, glm::radians(earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon2->model = glm::scale(moon2->model, glm::vec3(moon2Size));

	moon3->model = glm::translate(moon3->model, earthPos);
	moon3->model = glm::rotate(moon3->model, glm::radians(earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon3->model = glm::scale(moon3->model, glm::vec3(moon3Size));

	float marsFactor = marsPosX;
	marsPos = glm::vec3(-cos(marsAngle) * marsFactor, 0, -sin(marsAngle) * marsFactor);

	mars->model = glm::scale(mars->model, glm::vec3(1 / marsSize));
	mars->model = glm::rotate(mars->model, glm::radians(-marsRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	mars->model = glm::rotate(mars->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	mars->model = glm::translate(mars->model, marsPos);

	marsLine->model = glm::scale(marsLine->model, glm::vec3(1 / marsSize));
	marsLine->model = glm::rotate(marsLine->model, glm::radians(-marsRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	marsLine->model = glm::rotate(marsLine->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	marsLine->model = glm::translate(marsLine->model, marsPos);

	moon4->model = glm::scale(moon4->model, glm::vec3(1 / moon1Size));
	moon4->model = glm::rotate(moon4->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon4->model = glm::translate(moon4->model, marsPos);
	moon4->model = glm::translate(moon4->model, -moon4Pos);

	moon5->model = glm::scale(moon5->model, glm::vec3(1 / moon2Size));
	moon5->model = glm::rotate(moon5->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon5->model = glm::translate(moon5->model, marsPos);
	moon5->model = glm::translate(moon5->model, -moon5Pos);

	moon6->model = glm::scale(moon6->model, glm::vec3(1 / moon3Size));
	moon6->model = glm::rotate(moon6->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon6->model = glm::translate(moon6->model, marsPos);
	moon6->model = glm::translate(moon6->model, -moon6Pos);

	moon7->model = glm::scale(moon7->model, glm::vec3(1 / moon3Size));
	moon7->model = glm::rotate(moon7->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon7->model = glm::translate(moon7->model, marsPos);
	moon7->model = glm::translate(moon7->model, -moon7Pos);


	marsAngle += marsAngleFactor;
	marsRotationAxisY += marsRotationAxisYFactor;
	marsPos = glm::vec3(cos(marsAngle) * marsFactor, 0, sin(marsAngle) * marsFactor);

	moon4Pos = glm::vec3(moon4Pos[0] * cos(moon4AngleFactor) - moon4Pos[2] * sin(moon4AngleFactor), moon4Pos[1], moon4Pos[2] * cos(moon4AngleFactor) + moon4Pos[0] * sin(moon4AngleFactor));
	moon5Pos = glm::vec3(moon5Pos[0] * cos(moon5AngleFactor) - moon5Pos[2] * sin(moon5AngleFactor), moon5Pos[1], moon5Pos[2] * cos(moon5AngleFactor) + moon5Pos[0] * sin(moon5AngleFactor));
	moon6Pos = glm::vec3(moon6Pos[0] * cos(moon6AngleFactor) - moon6Pos[2] * sin(moon6AngleFactor), moon6Pos[1], moon6Pos[2] * cos(moon6AngleFactor) + moon6Pos[0] * sin(moon6AngleFactor));
	moon7Pos = glm::vec3(moon7Pos[0] * cos(moon7AngleFactor) - moon7Pos[2] * sin(moon7AngleFactor), moon7Pos[1], moon7Pos[2] * cos(moon7AngleFactor) + moon7Pos[0] * sin(moon7AngleFactor));


	moon4->model = glm::translate(moon4->model, moon4Pos);
	moon5->model = glm::translate(moon5->model, moon5Pos);
	moon6->model = glm::translate(moon6->model, moon6Pos);
	moon7->model = glm::translate(moon7->model, moon7Pos);


	mars->model = glm::translate(mars->model, marsPos);
	mars->model = glm::rotate(mars->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	mars->model = glm::rotate(mars->model, glm::radians(marsRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	mars->model = glm::scale(mars->model, glm::vec3(marsSize));

	marsLine->model = glm::translate(marsLine->model, marsPos);
	marsLine->model = glm::rotate(marsLine->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	marsLine->model = glm::rotate(marsLine->model, glm::radians(marsRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	marsLine->model = glm::scale(marsLine->model, glm::vec3(marsSize));

	moon4->model = glm::translate(moon4->model, marsPos);
	moon4->model = glm::rotate(moon4->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));

	moon4->model = glm::scale(moon4->model, glm::vec3(moon4Size));

	moon5->model = glm::translate(moon5->model, marsPos);
	moon5->model = glm::rotate(moon5->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon5->model = glm::scale(moon5->model, glm::vec3(moon5Size));

	moon6->model = glm::translate(moon6->model, marsPos);
	moon6->model = glm::rotate(moon6->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon6->model = glm::scale(moon6->model, glm::vec3(moon6Size));

	moon7->model = glm::translate(moon7->model, marsPos);
	moon7->model = glm::rotate(moon7->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon7->model = glm::scale(moon7->model, glm::vec3(moon7Size));


	

	sun->model = glm::rotate(sun->model, glm::radians(-sunRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	sun->model = glm::rotate(sun->model, glm::radians(-sunRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));

	sunLine->model = glm::rotate(sunLine->model, glm::radians(-sunRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	sunLine->model = glm::rotate(sunLine->model, glm::radians(-sunRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));

	sunRotationAxisY += sunRotationAxisYFactor;
	sunRotationAxisZ += sunRotationAxisZFactor;

	sun->model = glm::rotate(sun->model, glm::radians(sunRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	sun->model = glm::rotate(sun->model, glm::radians(sunRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));

	sunLine->model = glm::rotate(sunLine->model, glm::radians(sunRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	sunLine->model = glm::rotate(sunLine->model, glm::radians(sunRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	*/
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
//change
void keyboard(GLFWwindow* window, unsigned int codepoint) {
	switch (codepoint) {
	case '+':
		sun->model = glm::scale(sun->model, glm::vec3(1.2f));
		sunLine->model = glm::scale(sunLine->model, glm::vec3(1.2f));
		break;
	case '-':
		sun->model = glm::scale(sun->model, glm::vec3(0.8f));
		sunLine->model = glm::scale(sunLine->model, glm::vec3(0.8f));
		break;
	case 'x':
		sun->model = glm::rotate(sun->model, 0.1f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		break;
	case 'X':
		sun->model = glm::rotate(sun->model, -0.1f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		break;
	case 'y':
		sun->model = glm::rotate(sun->model, 0.1f, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		break;
	case 'Y':
		sun->model = glm::rotate(sun->model, -0.1f, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		break;
	case 'z':
		sun->model = glm::rotate(sun->model, 0.1f, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)));
		break;
	case 'Z':
		sun->model = glm::rotate(sun->model, -0.1f, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)));
		break;
	}
}

void transformObjs() {
	sun->model = rotate(sun->model, radians(sunRotationSpeed), vec3(0.0f, 1.0f, 0.0f));
	sunLine->model = rotate(sunLine->model, radians(0.1f), vec3(0.0f, 1.0f, 0.0f));

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