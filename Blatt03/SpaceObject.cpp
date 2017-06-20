#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "SpaceObject.h"


using namespace cg;

Sphere* SpaceObject::createObj(float angleX, float angleY, float angleZ, float size, glm::vec3 pos, glm::vec3 color) {
	Sphere* sphere = new Sphere(color);
	sphere->model = glm::translate(sphere->model, pos);
	sphere->model = glm::rotate(sphere->model, angleX, glm::vec3(1.0f, 0.0f, 0.0f));
	sphere->model = glm::rotate(sphere->model, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
	sphere->model = glm::rotate(sphere->model, angleZ, glm::vec3(0.0f, 0.0f, 1.0f));
	sphere->model = glm::scale(sphere->model, glm::vec3(size));
	return sphere;
}
Line* SpaceObject::createAxis(float angleX, float angleY, float angleZ, float size, glm::vec3 pos, glm::vec3 color) {
	Line* line = new Line(color);
	line->model = glm::translate(line->model, pos);
	line->model = glm::rotate(line->model, angleX, glm::vec3(1.0f, 0.0f, 0.0f));
	line->model = glm::rotate(line->model, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
	line->model = glm::rotate(line->model, angleZ, glm::vec3(0.0f, 0.0f, 1.0f));
	line->model = glm::scale(line->model, glm::vec3(size));
	return line;
}

