#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
using namespace glm;

namespace cg {
	namespace GLSLShader {
		enum GLSLShaderType {
			VERTEX = GL_VERTEX_SHADER,
			FRAGMENT = GL_FRAGMENT_SHADER,
			GEOMETRY = GL_GEOMETRY_SHADER,
			TESS_CONTROL = GL_TESS_CONTROL_SHADER,
			TESS_EVALUATION = GL_TESS_EVALUATION_SHADER
		};
	};

	// Based on https://github.com/daw42/glslcookbook.
	class GLSLProgram {
	private:
		GLuint handle;
		bool linked;
		string logString;
		vector<GLuint> shaders;
		bool verbose;
		bool checkAndCreateProgram(void);
		bool fileExists(const string& filename);
	public:
		GLSLProgram(bool verbose = true);
		~GLSLProgram(void);
		bool compileShaderFromFile(const char* filename, GLSLShader::GLSLShaderType type);
		bool compileShaderFromString(const string& source, GLSLShader::GLSLShaderType type);
		bool link(void);
		void use(void);
		string log(void) const;
		int getHandle(void) const;
		bool isLinked(void) const;
		void bindAttribLocation(GLuint location, const char* name);
		void bindFragDataLocation(GLuint location, const char* name);
		void setUniform(const char* name, float x, float y, float z);
		void setUniform(const char* name, const vec3& v);
		void setUniform(const char* name, const vec4& v);
		void setUniform(const char* name, const mat3& m);
		void setUniform(const char* name, const mat4& m);
		void setUniform(const char* name, float value);
		void setUniform(const char* name, int value);
		void setUniform(const char* name, bool value);
		void setUniform(const char* name, int size, const mat4* value);
		void printActiveUniforms(void);
		void printActiveAttribs(void);
		int getUniformLocation(const char* name);
	};
};
