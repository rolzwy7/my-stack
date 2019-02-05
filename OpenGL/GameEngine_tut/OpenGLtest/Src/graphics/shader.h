#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../utils/files.h"

#include <vector>
#include <iostream>

namespace engine {
	namespace graphics {

		class Shader {
		private:
			GLuint m_shader_id;
			const char *m_vert_path;
			const char *m_frag_path;
		public:
			Shader(const char *vertPath, const char *fragPath);
			~Shader();

			void enable() const;
			void disable() const;
		private:
			GLuint load();
		};


	} // namespace graphics
} // namespace engine