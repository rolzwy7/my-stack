#pragma once
#include <string>
#include <sstream>
#include <map>

/*! \file argparse.h
	\brief Obs�uga argument�w konsolowych

	Plik implementuje "parser" argument�w konsolowych.
*/

namespace argparse {

	/** Typ wyliczeniowy.
	*  Przechowywuje kody typ�w danych dodawanych argument�w.
	*/
	enum ArgType {
		/** Wskazuje na to, �e argument jest typu string */
		tString = 1,
		/** Wskazuje na to, �e argument jest typu int */
		tInt = 2,
		/** Wskazuje na to, �e argument jest typu double */
		tDouble = 3, 
		/** Wskazuje na to, �e argument jest typu bool (domy�lnie prawda) */
		tStoreTrue = 4 
	};
	/** Typ wyliczeniowy.
	*  Przechowywuje kody typ�w wa�no�ci dodawanych argument�w.
	*/
	enum ArgImp {
		/** Wskazuje na to, �e argument jest pozycyjny */
		iPositional = 21,
		/** Wskazuje na to, �e argument jest opcjonalny */
		iOptional = 22 
	};
	/** Typ wyliczeniowy.
	*  Przechowywuje kody inforumuj�ce o tym czy argument powoduje zaprzestanie wczytywania argument�w pozycyjnych.
	*/
	enum ArgDrop {
		/** Wskazuje na to, �e argument powoduje zaprzestanie wczytywania argument�w pozycyjnych. */
		dDrop = 31,
		/** Wskazuje na to, �e argument NIE powoduje zaprzestania wczytywania argument�w pozycyjnych. */
		dNone = 32 
	};
	//! Klasa przechowywuj�ca argument konsolowy.
	/*!
	Klasa odpowiadaj�ca za przechowywanie argument�w przekazanych przez konsol� wraz z dodatkowymi informacjami.
	*/
	struct Argument {
		/** Pozycja argumentu w wektorze. */
		int position;
		/** Nazwa nadana argumentowi. */
		std::string name;
		/** Tekst pomocy dla argumentu.  */
		std::string help;
		/** Typ danych argumentu. */
		ArgType arg_type;
		/** Typ wa�no�ci argumentu. */
		ArgImp arg_imp;
		/** Element typu wyliczeniowego ArgDrop */
		ArgDrop arg_drop;
	};

	//! Klasa obs�uguj�ca argumenty konsolowe.
	/*!
	Klasa odpowiadaj�ca za obs�ug� i interpretacje argument�w przekazanych przez konsol�.
	*/
	class ArgumentParser {
	private:
		/** Liczba dodanych argument�w. */
		int _arg_count; 
		/** Liczba dodanych argument�w opcjonalnych. */
		int _arg_count_optional;
		/** Liczba dodanych argument�w pozycyjnych (obowi�zkowych). */
		int _arg_count_positional; 
		/** Maksymalna dozwolona d�ugo�� nazwy argumentu. */
		int max_arg_name_len;
		/** Ignoruj argumenty pozycyjne. */
		bool drop_positionals;
		/** Wska�nik na tablic� objekt�w typu Argument. */
		Argument * _arg_ptr;
		/** Opis programu. */
		std::string description;
		/** Obecna nazwa pliku wykonywalnego. */
		std::string exec_name;
		/** Mapa przechowywuj�ca argumenty konsolowe typu string. */
		std::map<std::string, std::string> map_string;
		/** Mapa przechowywuj�ca argumenty konsolowe typu int. */
		std::map<std::string, int> map_int;
		/** Mapa przechowywuj�ca argumenty konsolowe typu double. */
		std::map<std::string, double> map_double;
		/** Mapa przechowywuj�ca argumenty konsolowe typu bool. */
		std::map<std::string, bool> map_bool;
	public:

		/**
		* Metoda mapuj�ca argument do odpowiedniego pola klasy.
		* @param str Nazwa argumentu.
		* @param obj Objekt klasy Argument.
		* @see Argument
		* @see map_string()
		* @see map_int()
		* @see map_double()
		* @see map_bool()
		* @return void
		*/
		void arg_convert(std::string str, Argument obj);
		/**
		* Konstruktor klasy ArgumentParser.
		* @param description opis programu.
		* @param argc Liczba argument�w przekazanych do konsoli.
		* @param argv Wektor zawieraj�cy argumenty przekazane do konsoli.
		*/
		ArgumentParser(std::string description, int argc, char * argv[]);
		/**
		* Dekonstruktor klasy ArgumentParser. Zwalnia pami�� na kt�r� wskazuje _arg_ptr()
		*/
		~ArgumentParser();
		/**
		* Metoda mapuj�ca argument do odpowiedniego pola klasy.
		* @param argc Liczba argument�w przekazanych przez konsole.
		* @param argv Wektor przechowywuj�cy argumenty przekazane przez konsole.
		* @return Prawda gdy argumenty zosta�y wczytane poprawnie. Fa�sz w przeciwnym razie.
		*/
		bool parse_args(int argc, char * argv[]);
		/**
		* Wy�wietla zawarto�� map na ekran.
		* @return void
		*/
		void print_maps();
		/**
		* Wy�wietla pomoc.
		* @param only_usage Wy�wietla tylko spos�b uzycia.
		* @return void
		*/
		void print_help(bool only_usage = false);
		/**
		* Wy�wietla wiadomo�ci o b��dach zwi�zane z argumentami pozycyjnymi.
		* @return void
		*/
		void print_positional_argument_err_msg();
		/**
		* Dodaje nowy argument.
		* @param name Nazwa argumentu.
		* @param help Tekst pomocy dla argumentu.
		* @param tType Typ danych argumentu.
		* @param tImp Typ wa�no�ci argumentu.
		* @param tDrop Zobacz ArgDrop().
		* @return void
		*/
		void add_argument(std::string name, std::string help, ArgType tType = tString, ArgImp tImp = iOptional, ArgDrop tDrop = dNone);
		
		/**
		* �aduje warto�� argumentu do zmiennej. (przeci��enie dla typu string)
		* @param name Nazwa argumentu.
		* @param target Zmienna do kt�rej ma zosta� wczytana warto�� argumentu.
		* @return Prawda je�li argument istnieje. Fa�sz w przeciwnym razie.
		*/
		inline bool get_arg(std::string name, std::string & target);
		/**
		* �aduje warto�� argumentu do zmiennej. (przeci��enie dla typu int)
		* @param name Nazwa argumentu.
		* @param target Zmienna do kt�rej ma zosta� wczytana warto�� argumentu.
		* @return Prawda je�li argument istnieje. Fa�sz w przeciwnym razie.
		*/
		inline bool get_arg(std::string name, int & target);
		/**
		* �aduje warto�� argumentu do zmiennej. (przeci��enie dla typu double)
		* @param name Nazwa argumentu.
		* @param target Zmienna do kt�rej ma zosta� wczytana warto�� argumentu.
		* @return Prawda je�li argument istnieje. Fa�sz w przeciwnym razie.
		*/
		inline bool get_arg(std::string name, double & target);
		/**
		* �aduje warto�� argumentu do zmiennej. (przeci��enie dla typu bool)
		* @param name Nazwa argumentu.
		* @param target Zmienna do kt�rej ma zosta� wczytana warto�� argumentu.
		* @return Prawda je�li argument istnieje. Fa�sz w przeciwnym razie.
		*/
		inline bool get_arg(std::string name, bool & target);
	};

	inline bool ArgumentParser::get_arg(std::string name, std::string & target) {
		target = (map_string.count(name)) ? map_string[name] : "";
		return (target != "") ? true : false;
	}

	inline bool ArgumentParser::get_arg(std::string name, int & target) {
		target = (map_int.count(name)) ? map_int[name] : 0;
		return (target != 0) ? true : false;
	}

	inline bool ArgumentParser::get_arg(std::string name, double & target) {
		target = (map_double.count(name)) ? map_double[name] : .0;
		return (target != .0) ? true : false;
	}

	inline bool ArgumentParser::get_arg(std::string name, bool & target) {
		if (map_bool.count(name)) {
			target = map_bool[name];
			return true;
		} 
		return false;
	}

} // namespace argparse
