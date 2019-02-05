#include <string>
#include <sstream>
#include <iostream>

// https://sourceforge.net/p/predef/wiki/OperatingSystems/
// http://gcc.gnu.org/onlinedocs/cpp/Predefined-Macros.html

#if _WIN32
// Windows stuff here
#include <windows.h>
#elif (__unix || __unix__ || unix)
// Linux stuff here
#include <unistd.h>
#else
// ??
#endif

int testFun() {
	std::cout << "__func__ in testFun : " << __func__ << std::endl;
	return 45;
}

int main(int argc, char* argv[]) {
	// https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html#Standard-Predefined-Macros
	std::cout << "__FILE__ : " << __FILE__ << std::endl;
	std::cout << "__LINE__ : " << __LINE__ << std::endl;
	std::cout << "__DATE__ : " << __DATE__ << std::endl;
	std::cout << "__TIME__ : " << __TIME__ << std::endl;
	std::cout << "__func__ : " << __func__ << std::endl;
	testFun();



	int x;
	std::cin >> x;
	return 0;
}
