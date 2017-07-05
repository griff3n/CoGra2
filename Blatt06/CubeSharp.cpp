#include "CubeSharp.h"

using namespace cg;

CubeSharp::CubeSharp(const glm::vec3& color) {
	initShader();
	initObjectData(color);
	initObject();
}

CubeSharp::~CubeSharp() {}

void cg::CubeSharp::calcNormal(ObjectData & objData, const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c) {
	// Calculate normal for the triangle.
	auto u = b - a;
	auto v = c - a;
	auto normal = glm::normalize(glm::cross(v, u));

	objData.normals.push_back(normal);
	objData.normals.push_back(normal);
	objData.normals.push_back(normal);
}
