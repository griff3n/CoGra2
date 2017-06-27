#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "DrawObject.h"

namespace cg {
	class BoundingBox : DrawObject {
	public:
		BoundingBox(const glm::vec3& color = glm::vec3(0.9f));
		BoundingBox(const glm::vec3 min, const glm::vec3 max, const glm::vec3& color = glm::vec3(0.9f));
		~BoundingBox();

		void render(const glm::mat4& view, const glm::mat4& projection);
		void refreshObjectData(const glm::vec3& color);
		GLfloat getXMin();
		GLfloat getXMax();
		GLfloat getYMin();
		GLfloat getYMax();
		GLfloat getZMin();
		GLfloat getZMax();	
	private:
		void initObjectData(const glm::vec3& color);
	public:
		// Only public for easy access.
		glm::mat4 model;
	private:
		GLfloat xMin = -1;
		GLfloat xMax = 1;
		GLfloat yMin = -1;
		GLfloat yMax = 1;
		GLfloat zMin = -1;
		GLfloat zMax = 1;
	};
}

