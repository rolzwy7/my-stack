#include "logger.h"

namespace engine {
	namespace logger {

		void Logger::logger_simpleMsg(std::string msg) {
			std::cout << msg << std::endl;
		}

		void Logger::logger_moduleDebugNotice(const char* module_name) {
			std::cout << "[DEBUG] Debug enabled for '" << module_name << "' module" << std::endl;
		}

		void Logger::logger_debugPrintKeyPress(int key, int action) {
			std::string d_pressed = (action == GLFW_PRESS)       ? "yes" : "no";
			std::string d_repeat  = (action == GLFW_REPEAT)      ? "yes" : "no";
			std::string d_release = (action == GLFW_RELEASE)     ? "yes" : "no";
			std::string d_unknown = (action == GLFW_KEY_UNKNOWN) ? "yes" : "no";
			std::cout << "---------------------------------\n";
			std::cout << "- Pressed : " << d_pressed << std::endl;
			std::cout << "- Repeat  : " << d_repeat << std::endl;
			std::cout << "- Release : " << d_release << std::endl;
			std::cout << "- Unknown : " << d_unknown << std::endl;
			// Unknown key pressed
			if (action == GLFW_KEY_UNKNOWN) {
				std::cout << "Unknown key: " << key << std::endl;
			}
			// Normal key press
			if ((action != GLFW_RELEASE) && (action != GLFW_KEY_UNKNOWN)) {
				std::cout << "Pressed: " << key << std::endl;
			}
			// Normal key release
			if ((action == GLFW_RELEASE) && (action != GLFW_KEY_UNKNOWN)) {
				std::cout << "Released: " << key << std::endl;
			}
		}

		void Logger::logger_debugPrintButtonPress(int button, int action) {
			std::string d_pressed = (action == GLFW_PRESS) ? "yes" : "no";
			std::string d_release = (action == GLFW_RELEASE) ? "yes" : "no";
			std::string d_unknown = (action == GLFW_KEY_UNKNOWN) ? "yes" : "no";

			std::cout << "---------------------------------\n";
			std::cout << "- mouse pressed : " << d_pressed << std::endl;
			std::cout << "- mouse release : " << d_release << std::endl;
			std::cout << "- mouse unknown : " << d_unknown << std::endl;

			// Unknown key pressed
			if (action == GLFW_KEY_UNKNOWN) {
				std::cout << "mouse Unknown button: " << button << std::endl;
			}
			// Normal key press
			if ((action != GLFW_RELEASE) && (action != GLFW_KEY_UNKNOWN)) {
				std::cout << "mouse Pressed: " << button << std::endl;
			}
			// Normal key release
			if ((action == GLFW_RELEASE) && (action != GLFW_KEY_UNKNOWN)) {
				std::cout << "mouse Released: " << button << std::endl;
			}
		}

		void Logger::logger_debugPrintCursorPosition(const double& x, const double& y) {
			std::cout << "Mouse (x=" << x << ", y=" << y << ")" << std::endl;
		}


	} // namespace logger
} // namespace engine