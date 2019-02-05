// author: Bartosz Nowakowski (https://github.com/rolzwy7)
#pragma once

#include <string>
#include <iostream>
#include <map>
#include <regex>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::map;

namespace argparse {

	const char os_sep =
#ifdef _WIN32
		'\\';
#else
		'/';
#endif

	enum ArgDataType {
		tInteger = 10,
		tFloat = 20,
		tString = 30,
		tStoreTrue = 40,
		tStoreFalse = 50
	};
	enum ArgImpType {
		tOptional,
		tPositional,
		tError
	};

	struct Argument {
		Argument *next;
		string name;
		string str_value;
		string help;
		ArgDataType arg_data_type;
		ArgImpType arg_imp_type;
		int argv_index;
	};

	class ArgumentParser {
	private:
		string description;
		string executable_name;
		string *str_argv;
		string convention_check;
		int argv_index;
		int argc_added;
		bool terminate_parse;
		Argument *head;
		std::map<string, string> map_str;
		std::map<string, int> map_int;
		std::map<string, float> map_float;
		std::map<string, bool> map_bool;

		void parse_mappings();

	public:
		ArgumentParser(string description);
		ArgumentParser();
		~ArgumentParser();

		void init_defaults(string description);

		void print_usage();

		void print_help();

		void print_no_positionals();

		bool add_argument(string name, string help = "", ArgDataType arg_data_type = tString);

		bool parse_args(int argc, char* argv[]);

		bool arg_name_exists(string name);

		void debug_print_arguments();

		bool get_str(string name, string &target);

		bool get_bool(string name, bool &target);

		bool get_int(string name, int &target);

		bool get_float(string name, float &target);

	};
} // namespace argparse