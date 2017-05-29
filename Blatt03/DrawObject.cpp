#include "DrawObject.h"

using namespace cg;

void DrawObject::render(const glm::mat4 model, const glm::mat4& view, const glm::mat4& projection) {
	// Create mvp.
	glm::mat4 mvp = projection * view * model;

	// Bind the shader program and set uniform(s).
	programSimple.use();
	programSimple.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the triangle.
	glBindVertexArray(drawObj.vao);
	glDrawElements(GL_LINES, drawObj.indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void DrawObject::initObject() {
	GLuint programId = programSimple.getHandle();
	GLuint pos;

	// Vertex array object.
	glGenVertexArrays(1, &drawObj.vao);
	glBindVertexArray(drawObj.vao);

	// Position buffer.
	glGenBuffers(1, &drawObj.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, drawObj.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, drawObjData.positions.size() * sizeof(glm::vec3), drawObjData.positions.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Color buffer.
	glGenBuffers(1, &drawObj.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, drawObj.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, drawObjData.colors.size() * sizeof(glm::vec3), drawObjData.colors.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Index buffer.
	drawObj.indexCount = (GLuint)drawObjData.indices.size();

	glGenBuffers(1, &drawObj.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawObj.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawObj.indexCount * sizeof(GLuint), drawObjData.indices.data(), GL_STATIC_DRAW);

}

void DrawObject::initShader(GLSLProgram& program, const std::string& vert, const std::string& frag) {
	if (!program.compileShaderFromFile(vert.c_str(), cg::GLSLShader::VERTEX)) {
		throw std::runtime_error(program.log());
	}
	if (!program.compileShaderFromFile(frag.c_str(), cg::GLSLShader::FRAGMENT)) {
		throw std::runtime_error(program.log());
	}
	if (!program.link()) {
		throw std::runtime_error(program.log());
	}
}