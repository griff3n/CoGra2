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
#include "DrawObject.h"

namespace cg {
	class Sphere : DrawObject {
	public:
		// Create a wired sphere with the given color.
		Sphere(const glm::vec3& color = glm::vec3(0.9f));
		void render(const glm::mat4& view, const glm::mat4& projection);
		ObjectData getObjektData();
	private:
		void initObjectData(const glm::vec3& color);
	public:
		// Only public for easy access.
		glm::mat4 model;
	};
} // namespace cg

#endif // SPHERE_H