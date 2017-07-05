#include "DrawObject.h"

using namespace cg;

void cg::DrawObject::setRenderNormals(bool renderNormals) {
	this->renderNormals = renderNormals;
}

void cg::DrawObject::toggleRenderNormals() {
	renderNormals = !renderNormals;
}

bool cg::DrawObject::isRenderNormals() const {
	return renderNormals;
}

void cg::DrawObject::initShader() {
	DrawObject::initShader(programSimple, "shader/simple.vert", "shader/simple.frag");
	DrawObject::initShader(programShaded, "shader/shaded.vert", "shader/shaded.frag");

	programShaded.use();
	programShaded.setUniform("lightDirection", glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)));

}

void cg::DrawObject::initShader(GLSLProgram & program, const std::string & vert, const std::string & frag) {
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

void cg::DrawObject::initObject() {
	GLuint programId = programShaded.getHandle();
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

	// Normal buffer.
	glGenBuffers(1, &drawObj.normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, drawObj.normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, drawObjData.normals.size() * sizeof(glm::vec3), drawObjData.normals.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "normal");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Index buffer.
	drawObj.indexCount = (GLuint)drawObjData.indices.size();

	glGenBuffers(1, &drawObj.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawObj.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawObj.indexCount * sizeof(GLuint), drawObjData.indices.data(), GL_STATIC_DRAW);

	// Build the normals.
	programId = programSimple.getHandle();

	// Vertex array object.
	glGenVertexArrays(1, &drawObjNorm.vao);
	glBindVertexArray(drawObjNorm.vao);

	// Position buffer.
	glGenBuffers(1, &drawObjNorm.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, drawObjNorm.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, drawObjNormData.positions.size() * sizeof(glm::vec3), drawObjNormData.positions.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Color buffer.
	glGenBuffers(1, &drawObjNorm.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, drawObjNorm.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, drawObjNormData.colors.size() * sizeof(glm::vec3), drawObjNormData.colors.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Index buffer.
	drawObjNorm.indexCount = (GLuint)drawObjNormData.indices.size();

	glGenBuffers(1, &drawObjNorm.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawObjNorm.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawObjNorm.indexCount * sizeof(GLuint), drawObjNormData.indices.data(), GL_STATIC_DRAW);
}

void cg::DrawObject::render(const glm::mat4 model, const glm::mat4 & view, const glm::mat4 & projection) {
	// Create mvp.
	glm::mat4 mvp = projection * view * model;

	// Create normal matrix (nm) from model matrix.
	glm::mat3 nm = glm::inverseTranspose(glm::mat3(model));

	// Bind the shader program and set uniform(s).
	programShaded.use();
	programShaded.setUniform("mvp", mvp);
	programShaded.setUniform("nm", nm);

	// Bind vertex array object so we can render the triangle.
	glBindVertexArray(drawObj.vao);
	glDrawElements(GL_TRIANGLES, drawObj.indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	if (renderNormals) {
		// Bind the shader program and set uniform(s).
		programSimple.use();
		programSimple.setUniform("mvp", mvp);
		// Bind vertex array object so we can render the triangle.
		glBindVertexArray(drawObjNorm.vao);
		glDrawElements(GL_LINES, drawObjNorm.indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
