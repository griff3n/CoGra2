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
#include "ObjectData.h"

namespace cg {
	class DrawObject {
	public:
		virtual void setLightDirection(const glm::vec3& dir) = 0;
		void setRenderNormals(bool renderNormals);
		void toggleRenderNormals();
		bool isRenderNormals() const;
	protected:
		void initShader();
		static void initShader(GLSLProgram& program, const std::string& vert, const std::string& frag);
		virtual void initObjectData(const glm::vec3& color) = 0;
		void initObject();
		void render(const glm::mat4 model, const glm::mat4& view, const glm::mat4& projection);
	protected:
		bool renderNormals;
		GLSLProgram programSimple;
		GLSLProgram programShaded;
		Object drawObj;
		Object drawObjNorm;
		ObjectData drawObjData;
		ObjectData drawObjNormData;
	};
}
