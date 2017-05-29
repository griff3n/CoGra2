#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLSLProgram.h"
#include "Object.h"
#include "ObjectData.h"

namespace cg {
	class DrawObject {
	public:
		void render(const glm::mat4 model, const glm::mat4& view, const glm::mat4& projection);
	protected:
		virtual void initObjectData(const glm::vec3& color) = 0;
		void initObject();
		static void initShader(GLSLProgram& program, const std::string& vert, const std::string& frag);
	protected:
		GLSLProgram programSimple;
		Object drawObj;
		ObjectData drawObjData;
	};
}
