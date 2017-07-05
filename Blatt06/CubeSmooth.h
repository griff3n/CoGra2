#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"
#include "Object.h"
#include "AbstractCube.h"

namespace cg {
	class CubeSmooth : public AbstractCube {
	public:
		CubeSmooth(const glm::vec3& color = glm::vec3(0.8f));
		~CubeSmooth();
		
		void calcNormal(ObjectData& objData, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
	};
}