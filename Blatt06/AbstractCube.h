#pragma once

#include <glm\glm.hpp>

#include "ObjectData.h"
#include "DrawObject.h"

namespace cg {
	class AbstractCube : public DrawObject {
	public:
		AbstractCube();
		virtual ~AbstractCube();

		void initObjectData(const glm::vec3& color);
		void render(const glm::mat4& view, const glm::mat4& projection);
		void setLightDirection(const glm::vec3& dir);
		glm::mat4& getModel();
	protected:
		void addNormal(ObjectData& objData, const glm::vec3& color, const glm::vec3& vertex, const glm::vec3& normal, float scale = 0.5f);
		void addQuad(ObjectData& objData, const glm::vec3& color, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d);
		void addTriangle(ObjectData& objData, const glm::vec3& color, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
		virtual void calcNormal(ObjectData& objData, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) = 0;
	protected:
		glm::mat4 model;
		const std::vector<glm::vec3> vertices = { { -1.0f, 1.0f, -1.0f, }, { 1.0f, 1.0f, -1.0f }, { 1.0f, -1.0f, -1.0f }, { -1.0f, -1.0f, -1.0f },
		{ -1.0f, 1.0f, 1.0f, }, { 1.0f, 1.0f, 1.0f }, { 1.0f, -1.0f, 1.0f }, { -1.0f, -1.0f, 1.0f } };
		const std::vector<glm::vec4> indicies = { { 0, 1, 2, 3 },{ 4, 0, 3, 7 },{ 1, 5, 6, 2 },{ 4, 5, 1, 0 },{ 3, 2, 6, 7 },{ 7, 6, 5, 4 } };
		const std::vector<GLint> indiecesNorm = { 0, 8, 22, 2, 12, 23, 1, 16, 26, 4, 7, 24, 34, 6, 18, 31, 20, 14, 32, 13, 25, 30, 10, 28 };
	};
}