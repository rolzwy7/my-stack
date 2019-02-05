#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

namespace engine {
	namespace logger {
		class Logger {
		public:
			void logger_simpleMsg(std::string msg);
			void logger_moduleDebugNotice(const char* module_name);
			void logger_debugPrintKeyPress(int key, int action); // keyboard key press
			void logger_debugPrintButtonPress(int button, int action); // mouse button press
			void logger_debugPrintCursorPosition(const double& x, const double& y);
		};
	} // namespace logger
} // namespace engine