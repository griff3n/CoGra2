#pragma once

#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "DrawObject.h"
#include "KontrollPolygon.h"

namespace cg {
	class BezierKurve : DrawObject {
	public:
		BezierKurve(KontrollPolygon* p_kPolygon,const GLfloat p_schrittweite = 0.5f, const glm::vec3& color = glm::vec3(0.9f));
		~BezierKurve();
		void render(const glm::mat4& view, const glm::mat4& projection);
		GLfloat getSchrittweite();
		void andereSchrittweite(bool kleiner);
		void zeichneBezierKurve(const glm::vec3 & color);
		void refresh(const glm::vec3 & color);
	private:
		void initObjectData(const glm::vec3& color);
	public:
		// Only public for easy access.
		glm::mat4 model;
	private:
		KontrollPolygon* kPolygon;
		GLfloat schrittweite;
	};
}

