#include "Line.h"

using namespace cg;

Line::Line(const glm::vec3& color) {
	Line::initShader(programSimple, "shader/simple.vert", "shader/simple.frag");
	initObject(color);
}

void Line::render(const glm::mat4& view, const glm::mat4& projection) {
	// Create mvp.
	glm::mat4 mvp = projection * view * model;

	// Bind the shader program and set uniform(s).
	programSimple.use();
	programSimple.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the triangle.
	glBindVertexArray(objLine.vao);
	glDrawElements(GL_LINES, objLine.indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glPopMatrix();
}

void Line::initObject(const glm::vec3& color) {
	// Build the sphere
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> positions = { { 0, -500, 0 }, { 0, 500, 0 } };
	std::vector<GLuint> indices = { 0, 1 };
	colors.push_back(color);

	GLuint programId = programSimple.getHandle();
	GLuint pos;

	// Vertex array object.
	glGenVertexArrays(1, &objLine.vao);
	glBindVertexArray(objLine.vao);

	// Position buffer.
	glGenBuffers(1, &objLine.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objLine.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Color buffer.
	glGenBuffers(1, &objLine.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objLine.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Index buffer.
	objLine.indexCount = (GLuint)indices.size();

	glGenBuffers(1, &objLine.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objLine.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, objLine.indexCount * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void Line::initShader(GLSLProgram& program, const std::string& vert, const std::string& frag) {
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