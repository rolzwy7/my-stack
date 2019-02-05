#include "Src/graphics/window.h"
#include "Src/utils/utils.h"
#include "Src/math/math.h"
#include "Src/utils/files.h"
#include "Src/graphics/shader.h"

#include <iostream>


int main(int argc, char* argv[]) {

	using namespace engine;
	using namespace math;
	using std::cout;
	using std::endl;
	using std::cin;

	utils::initGLFW();
	graphics::Window window("Test", 960, 540);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


	GLfloat verts[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};

	GLuint vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	graphics::Shader shader(
		"src/shaders/basic.vert",
		"src/shaders/basic.frag"
	);

	shader.enable();

	while (!window.isClosed()) {
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	}

	utils::terminateGLFW();
	return 0;
}