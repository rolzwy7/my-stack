#include "files.h"

namespace engine {
	namespace utils {

	std::string read_file(const char * filepath) {
		
		FILE* file;
		fopen_s(&file, filepath, "rt");

		fseek(file, 0, SEEK_END);

		unsigned long lenght = ftell(file);
		char *data = new char[lenght + 1];
		memset(data, 0, lenght + 1);
		data[lenght] = '\0';
		fseek(file, 0, SEEK_SET);
		//fread(data, 1, lenght, file);
		fread_s(data, lenght+1, 1, lenght, file);
		std::string result(data);
		std::cout << "[*] Read " << lenght << " characters from: " << filepath << std::endl;
		delete[] data;
		return result;


	}

	} // namespace utils
} // namespace engine