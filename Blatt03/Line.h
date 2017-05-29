#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLSLProgram.h"
#include "Object.h"
#include "DrawObject.h"

namespace cg {
	class Line : DrawObject {
	public:
		// Create a line with the given color.
		Line(const glm::vec3& color = glm::vec3(0.9f));
		void render(const glm::mat4& view, const glm::mat4& projection);
	private:
		void initObjectData(const glm::vec3& color);
	public:
		glm::mat4 model;
	};
}

#endif