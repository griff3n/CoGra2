#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLSLProgram.h"
#include "Object.h"

namespace cg {
	class Sphere {
	public:
		// Create a wired sphere with the given color.
		Sphere(const glm::vec3& color = glm::vec3(0.9f));
		void render(const glm::mat4& view, const glm::mat4& projection);
	private:
		void initObject(const glm::vec3& color);
		static void initShader(GLSLProgram& program, const std::string& vert, const std::string& frag);
	public:
		// Only public for easy access.
		glm::mat4 model;
	private:
		GLSLProgram programSimple;
		Object objSphere;
	};
} // namespace cg

#endif // SPHERE_H