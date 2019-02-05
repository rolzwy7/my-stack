#include "window.h"

namespace engine {
	namespace graphics {
		// callbacks
		void windowSizeCallback(GLFWwindow* window, int width, int height) {
			Window *win = (Window*) glfwGetWindowUserPointer(window);
			#if window_debug
				std::cout << "Window resized to: " << width << "x" << height << std::endl;
			#endif // window_debug
			glViewport(0, 0, width, height);
		}
		
		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->setKey(key, action);
		}
		
		void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->setCursorPos(xpos, ypos);
		}

		void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->setButton(button, action);
		}
		
		// public
		Window::Window(const char* name, int width, int height){
			#if window_debug
			this->logger_moduleDebugNotice(module_name);
			#endif
			m_name   = name;
			m_height = height;
			m_width  = width;
			for (int i = 0; i < KEYS_ARRAY_MAX_SIZE; ++i)
				m_keys[i] = false;
			for (int i = 0; i < BUTTONS_ARRAY_MAX_SIZE; ++i)
				m_buttons[i] = false;
			m_closed = !init();
		}
		
		Window::~Window() {}

		void Window::update() {
			glfwGetFramebufferSize(m_window, &m_width, &m_height);
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
		
		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT);
		}
		
		bool Window::isClosed() {
			bool ret = glfwWindowShouldClose(m_window) == 1;
			m_closed = ret;
			return ret;
		}
		
		int Window::getWidth() const {
			return m_width;
		}
		
		int Window::getHeight() const {
			return m_height;
		}
		
		const char* Window::getName() const {
			return m_name;
		}
		
		bool Window::setKey(int key, int action) {
			if (key >= 0 && key < KEYS_ARRAY_MAX_SIZE) {

				#if window_debug
				this->logger_debugPrintKeyPress(key, action);
				#endif

				// Unknown Key Pressed
				if (action == GLFW_KEY_UNKNOWN) {
					return false;
				}

				// Normal Key Press
				if( (action != GLFW_RELEASE) && (action != GLFW_KEY_UNKNOWN) ) {
					m_keys[key] = true;
				}

				// Normal Key Release
				if ( (action == GLFW_RELEASE) && (action != GLFW_KEY_UNKNOWN) ) {
					m_keys[key] = false;
				}

				return true;
			}
			return false;
		}
		
		bool Window::isKeyPressed(int key) {
			if (key >= 0 && key < KEYS_ARRAY_MAX_SIZE) {
				return m_keys[key];
			}
			return false;
		}
			
		void Window::setCursorPos(const double& x, const double& y) {
			m_mouseX = x;
			m_mouseY = y;
			#if window_debug
			this->logger_debugPrintCursorPosition(m_mouseX, m_mouseY);
			#endif // window_debug
		}

		bool Window::setButton(int button, int action) {

			if (button >= 0 && button < BUTTONS_ARRAY_MAX_SIZE) {
				#if window_debug
				this->logger_debugPrintButtonPress(button, action);
				#endif // window_debug
				// Unknown key pressed
				if (action == GLFW_KEY_UNKNOWN) {
					return false;
				}
				// Normal key press
				if ((action != GLFW_RELEASE) && (action != GLFW_KEY_UNKNOWN)) {
					m_buttons[button] = true;
				}
				// Normal key release
				if ((action == GLFW_RELEASE) && (action != GLFW_KEY_UNKNOWN)) {
					m_buttons[button] = false;
				}
				return true;
			}
			return false;
		}

		bool Window::isMouseButtonPressed(int button) {
			return m_buttons[button];
		}

		void Window::getMousePosition(double& x, double& y) {
			x = m_mouseX;
			y = m_mouseY;
		}

		// private
		bool Window::init() {
			// create window
			m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);
			if (!m_window) {
				std::cout << "[-] '" << m_name << "' window initialization failed " << std::endl;
				return false;
			} std::cout << "[+] '" << m_name << "' window initialized successfully " << std::endl;
			glfwMakeContextCurrent(m_window);
			// GLEW
			GLenum glew_err = glewInit();
			if (glew_err != GLEW_OK) {
				std::cout << "[-] Glew initialization failed: " << glewGetErrorString(glew_err) << std::endl;
				return false;
			} std::cout << "[+] Glew initialized successfully: " << glewGetString(GLEW_VERSION) << std::endl;
			std::cout << "[*] OpenGL version: " << glGetString(GL_VERSION) << std::endl;
			// set window pointer for callbacks
			glfwSetWindowUserPointer(m_window, this);
			// set callbacks
			glfwSetWindowSizeCallback(m_window, windowSizeCallback);
			glfwSetCursorPosCallback(m_window, cursorPositionCallback);
			glfwSetKeyCallback(m_window, keyCallback);
			glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
			return true;
		}

	} // namespace graphics
} // namespace engine