#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "DrawObject.h"
#include "Sphere.h"
#include "BoundingBox.h"

namespace cg {
	class KontrollPolygon : DrawObject {
	public:
		KontrollPolygon(std::string p_file, const glm::vec3& color = glm::vec3(0.9f));
		~KontrollPolygon();

		void render(const glm::mat4& view, const glm::mat4& projection);
		void translate(const glm::vec3& vec);
		void scale(const glm::vec3& vec);
		BoundingBox* getBBox();
		ObjectData getKData();
		GLfloat getScaleX();
		GLfloat getScaleY();
		GLfloat getScaleZ();
	private:
		void initObjectData(const glm::vec3& color);
		glm::vec3 getMax();
		glm::vec3 getMin();
	public:
		// Only public for easy access.
		glm::mat4 model;
	private:
		const std::string path = "";
		std::string file;
		std::vector<Sphere*> kPunkte;
		BoundingBox* bBox;
		GLfloat scaleX = 1, scaleY = 1, scaleZ = 1;
	};
}

