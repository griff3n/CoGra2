#include "BoundingBox.h"

using namespace cg;
using namespace glm;

BoundingBox::BoundingBox(const glm::vec3 & color) {
	DrawObject::initShader(programSimple, "shader/simple.vert", "shader/simple.frag");
	initObjectData(color);
	initObject();
}

cg::BoundingBox::BoundingBox(const glm::vec3 min, const glm::vec3 max, const glm::vec3 & color) {
	xMin = min.x;
	yMin = min.y;
	zMin = min.z;
	xMax = max.x;
	yMax = max.y;
	zMax = max.z;
	DrawObject::initShader(programSimple, "shader/simple.vert", "shader/simple.frag");
	initObjectData(color);
	initObject();
}

BoundingBox::~BoundingBox() {}

void BoundingBox::render(const glm::mat4 & view, const glm::mat4 & projection) {
	DrawObject::render(model, view, projection);
}

void BoundingBox::initObjectData(const glm::vec3 & color) {
	vec3 p1, p2, p3, p4, p5, p6, p7, p8;
	p1 = {xMin, yMin, zMax};
	p2 = {xMax, yMin, zMax };
	p3 = {xMin, yMax, zMax };
	p4 = {xMax, yMax, zMax };

	p5 = {xMin, yMin, zMin };
	p6 = {xMax, yMin, zMin };
	p7 = {xMin, yMax, zMin };
	p8 = {xMax, yMax, zMin };
	
	drawObjData.positions = {	p1, p2, p2, p4, p4, p3, p3, p1,
								p5, p6, p6, p8, p8, p7, p7, p5,
								p1, p5, p2, p6, p3, p7, p4, p8	};

	for (std::size_t i = 0; i < drawObjData.positions.size(); i++) {
		drawObjData.indices.push_back(i);
		drawObjData.colors.push_back(color);
	}
}

void cg::BoundingBox::refreshObjectData(const glm::vec3 & color) {
	drawObjData.positions.clear();
	drawObjData.colors.clear();
	drawObjData.indices.clear();
	initObjectData(color);
}

GLfloat cg::BoundingBox::getXMin() {
	return xMin;
}

GLfloat cg::BoundingBox::getXMax() {
	return xMax;
}

GLfloat cg::BoundingBox::getYMin() {
	return yMin;
}

GLfloat cg::BoundingBox::getYMax() {
	return yMax;
}

GLfloat cg::BoundingBox::getZMin() {
	return zMin;
}

GLfloat cg::BoundingBox::getZMax() {
	return zMax;
}

