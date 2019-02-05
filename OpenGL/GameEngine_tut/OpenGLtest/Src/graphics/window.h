#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "..\logger\logger.h"

#define module_name "window"
#define window_debug false

#define KEYS_ARRAY_MAX_SIZE		1024
#define BUTTONS_ARRAY_MAX_SIZE  64

namespace engine {
	namespace graphics {
		class Window: public logger::Logger {
		private:
			GLFWwindow *m_window;
			const char *m_name;
			int m_height;
			int m_width;
			bool m_closed;
			bool m_keys[KEYS_ARRAY_MAX_SIZE];
			bool m_buttons[BUTTONS_ARRAY_MAX_SIZE];
			double m_mouseX, m_mouseY;
		public:
			Window(const char* name, int width, int height);

			~Window();

			void update();

			void clear() const;

			bool isClosed();

			int getWidth() const;

			int getHeight() const;

			const char* getName() const;

			bool setKey(int key, int action);

			bool isKeyPressed(int key);

			void setCursorPos(const double& x, const double& y);

			bool setButton(int button, int action);

			bool isMouseButtonPressed(int button);

			void getMousePosition(double& x, double& y);
		private:
			bool init();
		};
	} // namespace graphics
} // namespace engine
