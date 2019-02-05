// author: Bartosz Nowakowski (https://github.com/rolzwy7)

#include "stdafx.h"
#include "argparse.h"

namespace argparse {

	ArgumentParser::ArgumentParser() {
		this->init_defaults("");
	}

	ArgumentParser::~ArgumentParser() {
		delete[] this->str_argv;
		Argument *ptr;
		while (this->head) {
			ptr = head;
			this->head = this->head->next;
			delete ptr;
		}
	}

	ArgumentParser::ArgumentParser(string description) {
		this->init_defaults(description);
	}

	void ArgumentParser::parse_mappings() {
		Argument *ptr = this->head;
		while (ptr) {
			if (ptr->str_value != "<str_value_not_set>") {
				// tString
				if (ptr->arg_data_type == tString)
					this->map_str[ptr->name] = ptr->str_value;
				// tInteger
				if (ptr->arg_data_type == tInteger)
					this->map_int[ptr->name] = atoi(ptr->str_value.c_str());
				// tFloat
				if (ptr->arg_data_type == tFloat)
					this->map_float[ptr->name] = (float)atof(ptr->str_value.c_str());
				// tStoreTrue, tStoreFalse
				if (ptr->arg_data_type == tStoreTrue && ptr->str_value == "<set>")
					this->map_bool[ptr->name] = true;
				if (ptr->arg_data_type == tStoreFalse && ptr->str_value == "<set>")
					this->map_bool[ptr->name] = false;
			}
			else {
				cout << "Parameter '" << ptr->name << "' not set." << endl;
			}
			ptr = ptr->next;
		}
	}

	void  ArgumentParser::init_defaults(string description) {
		this->description = description;
		this->head = nullptr;
		this->argc_added = 0;
		this->argv_index = 0;
		this->convention_check = "";
		this->terminate_parse = false;
	}

	void  ArgumentParser::print_usage() {
		auto make_opt_desc = [](string name) {
			string upper_name = name;
			for (auto it = upper_name.begin(); it != upper_name.end(); ++it) {
				*it = ::toupper(*it);
			}
			return "[" + name + " " + upper_name + "] ";

		};
		cout << "usage: " << this->executable_name << " [-h] ";
		Argument *ptr = this->head;
		while (ptr) {
			if (ptr->arg_imp_type == tOptional) {
				cout << make_opt_desc(ptr->name);
			}
			ptr = ptr->next;
		}
		string args_required = "";
		ptr = this->head;
		while (ptr) {
			if (ptr->arg_imp_type == tPositional) {
				args_required = ptr->name + " " + args_required;
			}
			ptr = ptr->next;
		}
		cout << args_required << endl;
	}

	void  ArgumentParser::print_help() {
		this->print_usage();
		cout << endl << endl;
		cout << this->description;
		cout << endl << endl;
		cout << "positional arguments:" << endl;
		Argument *ptr = this->head;
		while (ptr) {
			if (ptr->arg_imp_type == tPositional) {
				cout << "  " << ptr->name;
				for (unsigned int i = 0; i < 20 - (ptr->name).length(); ++i)
					cout << " ";
				cout << "\t\t" << ptr->help << endl;
			}
			ptr = ptr->next;
		}
		ptr = this->head;
		cout << endl;
		cout << "optional arguments:" << endl;
		while (ptr) {
			if (ptr->arg_imp_type == tOptional) {
				cout << "  " << ptr->name;
				for (unsigned int i = 0; i < 20 - (ptr->name).length(); ++i)
					cout << " ";
				cout << "\t\t" << ptr->help << endl;
			}
			ptr = ptr->next;
		}
		cout << endl;
	}

	void  ArgumentParser::print_no_positionals() {
		this->print_usage();
		Argument *ptr = this->head;
		string args_required = "";
		while (ptr) {
			if (ptr->arg_imp_type == tPositional) {
				args_required = ptr->name + " " + args_required;
			}
			ptr = ptr->next;
		}
		cout << this->executable_name << " error: the following arguments are required: " << args_required;
		cout << endl << endl;
	}

	bool  ArgumentParser::add_argument(string name, string help, ArgDataType arg_data_type) {
		if (name == "--help" || name == "-h") {
			cout << "You can't create optional argument with name --help or -h" << endl;
			return false;
		}

		// Check if argument already exists
		if (this->arg_name_exists(name)) {
			cout << "Argument '" << name << "' already exists" << endl;
			this->terminate_parse = true;
			return false;
		}

		// RegExp check argument name
		ArgImpType arg_imp_type;
		arg_imp_type = tError;
		std::regex re_positional("^[a-zA-z]+$");
		std::regex re_optional("^[-]{1,2}[a-zA-z][a-zA-z-]+$");
		std::cmatch m;
		if (std::regex_match(name.c_str(), m, re_positional))
			arg_imp_type = tPositional;
		if (std::regex_match(name.c_str(), m, re_optional))
			arg_imp_type = tOptional;

		// tError
		if (arg_imp_type == tError) {
			cout << "Argument name: '" << name << "' isn't valid" << endl;
			this->terminate_parse = true;
			return false;
		}

		// tPositional with store
		if (
			(arg_imp_type == tPositional && arg_data_type == tStoreFalse)
			|| (arg_imp_type == tPositional && arg_data_type == tStoreTrue)
			) {
			cout << "Positional argument can't store boolean value" << endl;
			this->terminate_parse = true;
			return false;
		}

		// Convenction exception
		if (arg_imp_type == tOptional) {
			if (
				(this->convention_check == "--" && name.find("--") != 0)
				|| (this->convention_check == "-" && name.find("--") == 0)
				) {
				cout << "Keep convention with: " <<
					this->convention_check << " for optional arguments" << endl
					<< "Error: " << name << endl;
				this->terminate_parse = true;
				return false;
			}
		}

		// Convention check
		if (arg_imp_type == tOptional) {
			if (name.find("--") == 0 && this->convention_check == "")
				this->convention_check = "--";
			if (name.find("-") == 0 && this->convention_check == "")
				this->convention_check = "-";
		}

		int argv_index = (arg_imp_type == tPositional) ? ++this->argv_index : -1;
		this->head = new Argument{
			this->head, name, "<str_value_not_set>", help, arg_data_type, arg_imp_type, argv_index
		};
		this->argc_added++;

		//cout << "Argument added: " << name << endl;
		return true;
	}

	bool  ArgumentParser::parse_args(int argc, char* argv[]) {
		if (this->terminate_parse) return false;

		// Get executable name
		this->executable_name = argv[0];
		this->executable_name.erase(
			this->executable_name.begin(),
			this->executable_name.begin()
			+ this->executable_name.find_last_of(os_sep) + 1
		);

		// Check if argc indicates that positionals were passed
		if (argc < argv_index) {
			this->print_no_positionals();
			return false;
		}

		// Copy argv to string array and check if help was passed
		this->str_argv = new string[argc];
		for (int it = 0; it < argc; ++it) {
			str_argv[it] = argv[it];
			if (str_argv[it] == "--help" || str_argv[it] == "-h") {
				this->print_help();
				return false;
			}
		}

		// Check if optional misspelled
		Argument *ptr = this->head;
		bool misspelled;
		for (int i = 0; i < argc; ++i) {
			if (this->convention_check == "") break;
			misspelled = true;
			if (str_argv[i].find(this->convention_check) == 0) {
				while (ptr) {
					if (str_argv[i].find(ptr->name) != string::npos) {
						misspelled = false;
						break;
					}
					ptr = ptr->next;
				}
			}
			else {
				misspelled = false;
			}
			if (misspelled) {
				cout << "[-] Misspelled: " << str_argv[i] << endl;
				this->terminate_parse;
				return false;
			}
			ptr = this->head;
		}


		// Parse positionals
		ptr = this->head;
		while (ptr) {
			if (ptr->arg_imp_type == tPositional) {
				if ((ptr->argv_index < argc) & (str_argv[ptr->argv_index].find("-") == string::npos))
					ptr->str_value = str_argv[ptr->argv_index];
				else {
					cout << "[-] Error while parsing '" << ptr->name << "' positional" << endl;
					return false;
				}
			}
			ptr = ptr->next;
		}
		ptr = this->head;

		// Parse optionals
		string tmp;
		while (ptr) {
			// Optionals with user set value
			if (
				ptr->arg_imp_type == tOptional
				&& ptr->arg_data_type != tStoreFalse
				&& ptr->arg_data_type != tStoreTrue
				) {
				for (int i = 0; i < argc; ++i) {
					if (str_argv[i].find(ptr->name + "=") == 0) {
						tmp = str_argv[i];
						tmp.erase(tmp.begin(), tmp.begin() + tmp.find("=") + 1);
						ptr->str_value = tmp;
						continue;
					}
					if (str_argv[i] == ptr->name) {
						if ((i + 1) < argc)
							ptr->str_value = str_argv[i + 1];
						else {
							cout << "[-] Optional index exceeded argc: " << ptr->name << endl;
							return false;
						}
						continue;
					}
				}
			}
			// Store optionals (flags)
			if (
				ptr->arg_imp_type == tOptional
				&& (ptr->arg_data_type == tStoreFalse || ptr->arg_data_type == tStoreTrue)
				) {
				for (int i = 0; i < argc; ++i) {
					if (str_argv[i] == ptr->name)
						ptr->str_value = "<set>";
				}
			}

			ptr = ptr->next;
		}
		ptr = this->head;
		this->parse_mappings();
		return true;
	}

	bool  ArgumentParser::arg_name_exists(string name) {
		Argument *ptr = this->head;
		while (ptr) {
			if (ptr->name == name)
				return true;
			ptr = ptr->next;
		}
		return false;
	}

	void  ArgumentParser::debug_print_arguments() {
		Argument *ptr = this->head;
		while (ptr) {
			cout << "Name      : " << ptr->name << endl;
			cout << "Value     : " << ptr->str_value << endl;
			cout << "Argv idx  : " << ptr->argv_index << endl;
			cout << "Data Type : " << ptr->arg_data_type << endl;
			cout << "Imp Type  : " << ptr->arg_imp_type << endl;
			cout << endl;
			ptr = ptr->next;
		}
	}

	bool  ArgumentParser::get_str(string name, string &target) {
		std::map<string, string>::iterator map_it = this->map_str.begin();
		while (map_it != this->map_str.end()) {
			if (map_it->first == name) {
				target = map_it->second;
				return true;
			}
			++map_it;
		}
		return false;
	}

	bool  ArgumentParser::get_bool(string name, bool &target) {
		std::map<string, bool>::iterator map_it = this->map_bool.begin();
		while (map_it != this->map_bool.end()) {
			if (map_it->first == name) {
				target = map_it->second;
				return true;
			}
			++map_it;
		}
		return false;
	}

	bool  ArgumentParser::get_int(string name, int &target) {
		std::map<string, int>::iterator map_it = this->map_int.begin();
		while (map_it != this->map_int.end()) {
			if (map_it->first == name) {
				target = map_it->second;
				return true;
			}
			++map_it;
		}
		return false;
	}

	bool  ArgumentParser::get_float(string name, float &target) {
		std::map<string, float>::iterator map_it = this->map_float.begin();
		while (map_it != this->map_float.end()) {
			if (map_it->first == name) {
				target = map_it->second;
				return true;
			}
			++map_it;
		}
		return false;
	}

} // namespace argparse

