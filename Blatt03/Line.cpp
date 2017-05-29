#include "Line.h"

using namespace cg;

Line::Line(const glm::vec3& color) {
	DrawObject::initShader(programSimple, "shader/simple.vert", "shader/simple.frag");
	initObjectData(color);
	initObject();
}

void Line::render(const glm::mat4& view, const glm::mat4& projection) {
	DrawObject::render(model, view, projection);
}

void Line::initObjectData(const glm::vec3& color) {
	// Build the line
	drawObjData.positions = { { 0, -500, 0 }, { 0, 500, 0 } };
	drawObjData.indices = { 0, 1 };
	drawObjData.colors.push_back(color);
}