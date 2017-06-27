#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace cg {
	struct ObjectData {
		std::vector<glm::vec3> colors;
		std::vector<glm::vec3> positions;
		std::vector<GLuint> indices;
	};
}