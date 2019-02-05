#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace engine {
	namespace utils {
		// GL
		void printGLVersion();
		// GLW
		bool initGLFW();
		void terminateGLFW();
		// GLEW
		void checkGLEW();
	} // namespace utils
} // namespace engine