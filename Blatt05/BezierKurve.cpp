#include "BezierKurve.h"

using namespace cg;
using namespace glm;

BezierKurve::BezierKurve(KontrollPolygon * p_kPolygon, const GLfloat p_schrittweite, const glm::vec3 & color) {
	kPolygon = p_kPolygon;
	schrittweite = p_schrittweite;
	DrawObject::initShader(programSimple, "shader/simple.vert", "shader/simple.frag");
	initObjectData(color);
	initObject();
}

BezierKurve::~BezierKurve() {
	delete kPolygon;
}

void BezierKurve::render(const glm::mat4 & view, const glm::mat4 & projection) {
	DrawObject::render(model, view, projection);
	kPolygon->render(view, projection);
}

GLfloat cg::BezierKurve::getSchrittweite() {
	return schrittweite;
}

void cg::BezierKurve::andereSchrittweite(bool kleiner) {
	if (!kleiner && schrittweite == 0.5f || kleiner && schrittweite <= 0.390625f) {
		return;
	}
	if (kleiner) {
		schrittweite *= 0.5f;
	} else {
		schrittweite *= 10;
	}
}

void BezierKurve::initObjectData(const glm::vec3 & color) {
	zeichneBezierKurve(color);
}

void BezierKurve::zeichneBezierKurve(const glm::vec3 & color) {
	drawObjData.positions.clear();
	drawObjData.colors.clear();
	drawObjData.indices.clear();
	std::vector<vec3> temp;
	std::vector<std::vector<vec3>> zwPunkte;
	vec3 lastpos;
	ObjectData kData = kPolygon->getKData();
	GLfloat x = 0, y = 0, z = 0;
	for (int i = 0; i < kData.positions.size(); i++) {
		x = kData.positions[i].x * kPolygon->getScaleX();
		y = kData.positions[i].y * kPolygon->getScaleY();
		z = kData.positions[i].z * kPolygon->getScaleZ();
		temp.push_back(vec3(x, y, z));
	}
	lastpos = temp.front();
	for (GLfloat t = schrittweite; t < 1; t += schrittweite) {
		for (int i = 0; i < temp.size(); i++) {
			std::vector<vec3> p;
			p.push_back(temp[i]);
			zwPunkte.push_back(p);
		}

		for (int k = 1; k < zwPunkte.size(); k++) {
			for (int i = k; i < zwPunkte.size(); i++) {
				vec3 val = (1 - t) * zwPunkte[i - 1][k - 1] + t * zwPunkte[i][k - 1];
				zwPunkte[i].push_back(val);
			}
		}
		drawObjData.positions.push_back(lastpos);
		lastpos = zwPunkte.back().back();
		drawObjData.positions.push_back(lastpos);
		zwPunkte.clear();
	}
	drawObjData.positions.push_back(lastpos);
	drawObjData.positions.push_back(temp.back());
	for (std::size_t i = 0; i < drawObjData.positions.size(); i++) {
		drawObjData.indices.push_back(i);
		drawObjData.colors.push_back(color);
	}
}

void cg::BezierKurve::refresh(const glm::vec3 & color) {
	//DrawObject::initShader(programSimple, "shader/simple.vert", "shader/simple.frag");
	initObjectData(color);
	initObject();
}
