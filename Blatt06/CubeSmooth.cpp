#include "CubeSmooth.h"

using namespace cg;

CubeSmooth::CubeSmooth(const glm::vec3& color) {
	initShader();
	initObjectData(color);
	initObject();
}

CubeSmooth::~CubeSmooth() {}

void CubeSmooth::calcNormal(ObjectData& objData, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
	// This is simple... this time!
	objData.normals.push_back(glm::normalize(a));
	objData.normals.push_back(glm::normalize(b));
	objData.normals.push_back(glm::normalize(c));
}
