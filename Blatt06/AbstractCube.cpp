#include "AbstractCube.h"

using namespace cg;

AbstractCube::AbstractCube() {}

AbstractCube::~AbstractCube() {}

void cg::AbstractCube::initObjectData(const glm::vec3 & color) {
	for (int i = 0; i < indicies.size(); i++) {
		glm::vec4 index = indicies[i];
		AbstractCube::addQuad(drawObjData, color, vertices[index[0]], vertices[index[1]], vertices[index[2]], vertices[index[3]]);
	}
	for (GLushort i = 0; i < drawObjData.positions.size(); i++) {
		drawObjData.indices.push_back(i);
	}
	const glm::vec3 colorNormal(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < indiecesNorm.size(); i++) {
		AbstractCube::addNormal(drawObjNormData, colorNormal, drawObjData.positions[indiecesNorm[i]], drawObjData.normals[indiecesNorm[i]]);
	}
	for (GLushort i = 0; i < drawObjNormData.positions.size(); i++) {
		drawObjNormData.indices.push_back(i);
	}
}

void cg::AbstractCube::render(const glm::mat4 & view, const glm::mat4 & projection) {
	DrawObject::render(model, view, projection);
}

void cg::AbstractCube::setLightDirection(const glm::vec3 & dir) {
	programShaded.use();
	programShaded.setUniform("lightDirection", dir);
}

glm::mat4& AbstractCube::getModel() {
	return model;
}

void AbstractCube::addNormal(ObjectData& objData, const glm::vec3& color, const glm::vec3& vertex, const glm::vec3& normal, float scale) {
	objData.positions.push_back(vertex);
	objData.positions.push_back(vertex + normal * scale);
	objData.colors.push_back(color);
	objData.colors.push_back(color);
}

void AbstractCube::addQuad(ObjectData& objData, const glm::vec3& color, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d) {
	addTriangle(objData, color, a, c, b);
	addTriangle(objData, color, a, d, c);
}

void AbstractCube::addTriangle(ObjectData& objData, const glm::vec3& color, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
	// Add vertices, normals and colors to the buffers.
	objData.positions.push_back(a);
	objData.positions.push_back(b);
	objData.positions.push_back(c);
	
	calcNormal(objData, a, b, c);
	
	objData.colors.push_back(color);
	objData.colors.push_back(color);
	objData.colors.push_back(color);
}
