#include "stdafx.h"
#include <exception>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class ParserException : public std::exception {
	private:
		const char* _msg;
		const char* _file;
		unsigned int _line;

	public:
		ParserException(const char *msg, const char* file, unsigned int line): std::exception(msg),
			_file(file),
			_line(line)
		{}

		const char* getFile() const {
			return this->_file;
		}

		unsigned int getLine() const {
			return this->_line;
		}

		const char* getMsg() const {
			return this->_msg;
		}

		void printDetails() const {
			cout << "[ParserException]\n";
			cout << "\tMsg  : "	<< this->what()		<< endl;
			cout << "\tFile : "	<< this->getFile()	<< endl;
			cout << "\tLine : "	<< this->getLine()	<< endl;
		}
};


void checkContainsDot(string to_parse) {
	if (to_parse.find('.') == std::string::npos)
		throw ParserException("String must contain dot", "somefile.txt", 65);
}


int main() {
	string to_check_dot = "This is a string with . dot";
	string to_check_no_dot = "This is a string without dot";

	try {
		checkContainsDot(to_check_dot);
	} catch(ParserException &e) {
		e.what();
	}

	try {
		checkContainsDot(to_check_no_dot);
	}
	catch (ParserException &except) {
		except.printDetails();
	}

    return 0;
}

