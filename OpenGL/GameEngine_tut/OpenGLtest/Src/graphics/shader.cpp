#include "shader.h"
#include "../logger/logger.h"

namespace engine {
	namespace graphics {

		Shader::Shader(const char * vertPath, const char * fragPath):
			m_vert_path(vertPath),
			m_frag_path(fragPath)
		{
			m_shader_id = load();
		}

		Shader::~Shader() {
			glDeleteProgram(m_shader_id);
		}

		void Shader::enable() const {
			std::cout << "[*] Shader enabled: (shader_id=" << m_shader_id << ")" << std::endl;
			glUseProgram(m_shader_id);
		}

		void Shader::disable() const {
			std::cout << "[*] Shader enabled: (shader_id=0)" << std::endl;
			glUseProgram(0);
		}

		GLuint Shader::load() {
			GLuint program  = glCreateProgram();
			GLuint vertex   = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
			
			std::string vertex_source_str = utils::read_file(m_vert_path);
			std::string fragment_source_str = utils::read_file(m_frag_path);

			const char *vertex_source   = vertex_source_str.c_str();
			const char *fragment_source = fragment_source_str.c_str();


			// Compile Vertex Shader
			glShaderSource(vertex, 1, &vertex_source, NULL);
			glCompileShader(vertex);
			GLint vertex_result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &vertex_result);
			if (vertex_result == GL_FALSE) {
				GLint log_lenght;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &log_lenght);
				std::vector<char> error(log_lenght);
				glGetShaderInfoLog(vertex, log_lenght, &log_lenght, &error[0]);
				std::cout << "[-] Failed to compile vertex shader:" << std::endl;
				std::cout << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 1;
			}
			if (vertex_result == GL_TRUE)
				std::cout << "[+] Vertex Shader loaded successfully" << std::endl;

			// Compile Fragment Shader
			glShaderSource(fragment, 1, &fragment_source, NULL);
			glCompileShader(fragment);
			GLint fragment_result;
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &fragment_result);
			if (fragment_result == GL_FALSE) {
				GLint log_lenght;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &log_lenght);
				std::vector<char> error(log_lenght);
				glGetShaderInfoLog(fragment, log_lenght, &log_lenght, &error[0]);
				std::cout << "[-] Failed to compile fragment shader:" << std::endl;
				std::cout << &error[0] << std::endl;
				glDeleteShader(fragment);
				return 1;
			}
			if (fragment_result == GL_TRUE)
				std::cout << "[+] Fragment Shader loaded successfully" << std::endl;

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

	} // namespace graphics
} // namespace engine