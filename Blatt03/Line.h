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

namespace cg {
	class Line {
	public:
		// Create a line with the given color.
		Line(const glm::vec3& color = glm::vec3(0.9f));
		void render(const glm::mat4& view, const glm::mat4& projection);
	private:
		void initObject(const glm::vec3& color);
		static void initShader(GLSLProgram& program, const std::string& vert, const std::string& frag);
	public:
		glm::mat4 model;
	private:
		GLSLProgram programSimple;
		Object objLine;
	};
}

#endif