#pragma once

#include "Line.h"
#include "Sphere.h"

namespace cg {
	class SpaceObject {
	public:
		virtual void render(const glm::mat4& view, const glm::mat4& projection) = 0;
		Sphere* createObj(float angleX, float angleY, float angleZ, float size, glm::vec3 pos, glm::vec3 color);
		Line* createAxis(float angleX, float angleY, float angleZ, float size, glm::vec3 pos, glm::vec3 color);
		
	protected:
		
		float objSize;
		float objAngle;
		float objAngleFactor;
		float objRotationAxisX;
		float objRotationAxisY;
		float objRotationAxisZ;
		float objRotationAxisXFactor;
		float objRotationAxisYFactor;
		float objRotationAxisZFactor;
		float objPosX;
		glm::vec3 objPos;
		glm::vec3 objColor;
	};
}
