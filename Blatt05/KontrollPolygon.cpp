#include "KontrollPolygon.h"

using namespace cg;
using namespace glm;

cg::KontrollPolygon::KontrollPolygon(std::string p_file, const glm::vec3 & color) {
	file = p_file;
	DrawObject::initShader(programSimple, "shader/simple.vert", "shader/simple.frag");
	initObjectData(color);
	initObject();
}

KontrollPolygon::~KontrollPolygon() {
	delete bBox;
}

void cg::KontrollPolygon::render(const glm::mat4 & view, const glm::mat4 & projection) {
	DrawObject::render(model, view, projection);
	for (int i = 0; i < kPunkte.size(); i++) {
		kPunkte[i]->render(view, projection);
	}
	bBox->render(view, projection);
}

void cg::KontrollPolygon::translate(const glm::vec3 & vec) {
	bBox->model = glm::translate(bBox->model, vec);
	model = glm::translate(model,vec);
	for (int i = 0; i < kPunkte.size(); i++) {
		kPunkte[i]->model = model;
		kPunkte[i]->model = glm::translate(kPunkte[i]->model, drawObjData.positions[i]);
		kPunkte[i]->model = glm::scale(kPunkte[i]->model, vec3(0.1));
	}
}

void cg::KontrollPolygon::scale(const glm::vec3 & vec) {
	bBox->model = glm::scale(bBox->model, vec);
	model = glm::scale(model, vec);
	for (int i = 0; i < kPunkte.size(); i++) {
		kPunkte[i]->model = model;
		kPunkte[i]->model = glm::translate(kPunkte[i]->model, drawObjData.positions[i]);
		kPunkte[i]->model = glm::scale(kPunkte[i]->model, vec3(0.1));
	}
	scaleX *= vec.x;
	scaleY *= vec.y;
	scaleZ *= vec.z;
}

BoundingBox* cg::KontrollPolygon::getBBox() {
	return bBox;
}

ObjectData cg::KontrollPolygon::getKData() {
	return drawObjData;
}

GLfloat cg::KontrollPolygon::getScaleX() {
	return scaleX;
}

GLfloat cg::KontrollPolygon::getScaleY() {
	return scaleY;
}

GLfloat cg::KontrollPolygon::getScaleZ() {
	return scaleZ;
}

void cg::KontrollPolygon::initObjectData(const glm::vec3 & color) {
	GLint lines = 0;
	bool end = false;
	std::ifstream input(path + file);

	if (!input) {
		std::cerr << "Fehler beim Öffnen der Datei " << path + file << std::endl;
		exit(1);
	}
	std::string word;
	while (input >> word && !end) {
		if (word[0] == '#' || word == "#") {
			std::getline(input, word);
		} else if (word == "v") {
			GLfloat x = 0, y = 0, z = 0;
			input >> word;
			x = std::stof(word, nullptr);
			input >> word;
			y = std::stof(word, nullptr);
			input >> word;
			z = std::stof(word, nullptr);
			drawObjData.positions.push_back(vec3(x,y,z));
			Sphere* sp = new Sphere(vec3(1, 1, 0));
			kPunkte.push_back(sp);
			kPunkte.back()->model = glm::translate(kPunkte.back()->model, vec3(x,y,z));
			kPunkte.back()->model = glm::scale(kPunkte.back()->model, vec3(0.1));
		} else if (word == "deg") {
			input >> word;
			lines = std::stoi(word);
		} else if (word == "curv") {
			int index = 0;
			for (int i = 0; i < lines + 1; i++) {
				input >> word;
				index = std::stoi(word) - 1;
				drawObjData.indices.push_back(index);
				if (i != 0 && i != lines + 1) {
					drawObjData.indices.push_back(index);
				}
			} 
		} else if (word == "end") {
			end = true;
		}
	}
	input.close();
	for (std::size_t i = 0; i < drawObjData.positions.size(); i++) {
		drawObjData.colors.push_back(color);
	}
	bBox = new BoundingBox(getMin(), getMax(), vec3(0, 1, 0));
}

glm::vec3 cg::KontrollPolygon::getMax() {
	GLfloat x, y, z;
	x = drawObjData.positions[0].x;
	y = drawObjData.positions[0].y;
	z = drawObjData.positions[0].z;
	for (std::size_t i = 1; i < drawObjData.positions.size(); i++) {
		if (x < drawObjData.positions[i].x) {
			x = drawObjData.positions[i].x;
		}
		if (y < drawObjData.positions[i].y) {
			y = drawObjData.positions[i].y;
		}
		if (z < drawObjData.positions[i].z) {
			z = drawObjData.positions[i].z;
		}
	}
	return vec3(x, y, z);
}

glm::vec3 cg::KontrollPolygon::getMin() {
	GLfloat x, y, z;
	x = drawObjData.positions[0].x;
	y = drawObjData.positions[0].y;
	z = drawObjData.positions[0].z;
	for (std::size_t i = 1; i < drawObjData.positions.size(); i++) {
		if (x > drawObjData.positions[i].x) {
			x = drawObjData.positions[i].x;
		}
		if (y > drawObjData.positions[i].y) {
			y = drawObjData.positions[i].y;
		}
		if (z > drawObjData.positions[i].z) {
			z = drawObjData.positions[i].z;
		}
	}
	return vec3(x, y, z);
}
