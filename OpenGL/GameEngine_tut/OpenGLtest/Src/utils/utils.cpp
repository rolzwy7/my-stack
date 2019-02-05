#include "utils.h"

namespace engine {
	namespace utils {
		// GL
		void printGLVersion() {
			std::cout << "[*] OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		}
		// GLFW
		bool initGLFW() {
			if (!glfwInit())
				return false;
			return true;
		}
		void terminateGLFW() {
			glfwTerminate();
		}
		// GLEW
		void checkGLEW() {
			if (GLEW_VERSION_1_3)
				std::cout << "[+/Glew] OpenGL 1.3 is supported!" << std::endl;
			else
				std::cout << "[-/Glew] OpenGL 1.3 is not supported!" << std::endl;
		}

	} // namespace utils
} // namespace engine