using namespace glm;
using namespace cg;

// Standard Fenster Breite und Höhe
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

// Einfache "struct" die Daten fürs die Bildsyntese(rendern) speichert.
struct Object {
	// IDs für mehrere Puffer.
	GLuint vertexArrayObject;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;

	// Model matrix
	mat4x4 model;
	int n;
};

struct data
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<GLushort> indices;
};

int main(int argc, char** argv);
bool init();
void initNEck(int n);
void initWurfel();
Object initObjekt(data objektdata, Object obj);

void render();
void renderNEck();
void renderWurfel();
void renderObject(Object obj, GLint caunt);
void resize(GLFWwindow* window, int width, int height);
void keyboard(GLFWwindow* window, unsigned int codepoint);
void release();
void releaseObject(Object& obj);

GLSLProgram program;

mat4x4 view;
mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

Object nEck;
Object wurfel;

bool isWurfel = false;