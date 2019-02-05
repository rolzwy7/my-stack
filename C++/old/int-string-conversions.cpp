#include <string>
#include <sstream>
#include <iostream>

#if _DEBUG
	#include <windows.h>
#endif // _DEBUG


int main(int argc, char* argv[]) {
	int integer = 15;
	std::string _string = "85";
	std::string _string2 = "   85ccc";

	// INT TO STRING
	std::cout << std::endl << "Int to String: int="<< integer << std::endl;
	std::stringstream ss;
	ss << integer;
	std::cout << "result: " << ss.str() << std::endl;
	ss.str(""); // reset string stream

	// STRING TO INT
	std::cout << std::endl << "String to Int: string:" << _string << std::endl;
	std::cout << "result: " << std::stoi(_string) << std::endl;
	std::cout << std::endl << "String to Int: string:" << _string2 << std::endl;
	std::cout << "result: " << std::atoi(_string2.c_str()) << std::endl;
	

	#if _DEBUG
		std::cout << std::endl;
		system("pause");
	#endif // _DEBUG
	return 0;
}
