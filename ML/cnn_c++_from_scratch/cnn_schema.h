#pragma once
#include <string>
#include <vector>

/*! \file cnn_schema.h
	\brief Implementuje objekty obs�uguj�ce pliki zawieraj�ce schemat sieci
*/

namespace neural {

	//! Klasa reprezentuj�ca plik schematu
	/*!
	Klasa reprezentuj�ca plik schematu oraz implementuj�ca jego �adowanie i walidacj�.
	*/
	class CNNSchemaFile {
	public:
		/** Nazwa pliku schematu */
		std::string filename;
		/** Zawarto�� pliku schematu */
		std::string content;
		/** Liczba wej�� sieci */
		int inputs;
		/** Liczba wyj�� sieci */
		int outputs;
		/**
		* Konstruktor
		* @param filename �cie�ka do pliku schematu
		*/
		CNNSchemaFile(const std::string & filename);
		/**
		* Metoda �aduj�ca zawarto�� pliku schematu do pola content().
		* Wykonywana jest tak�e wst�pna walidacja b�d�ca wst�pem do walidacji szczeg�owej wykonywaniej przez metod� validate().
		* @param msg Wiadomo�� wy�wietlana u�ytkownikowi
		* @return Prawda je�li plik zosta� poprawnie za�adowany. Fa�sz w przeciwnym razie.
		*/
		bool load(std::string & msg);
		/**
		* Metoda wykonywuj�ca szczeg�ow� walidacj� plik schematu i dystrybucje danych do wektor�w wyj�ciowych
		* @param reason Wiadomo�� wy�wietlana u�ytkownikowi
		* @param ref_layers Wczytana z pliku liczba warstw sieci przekazywana przez referencje
		* @param ref_hidden_r Wczytane z pliku informacje o wierszach warstw ukrytych
		* @param ref_hidden_c Wczytane z pliku informacje o kolumnach warstw ukrytych
		* @param hidden_weights Wczytane z pliku informacje o wagach warstw ukrytych
		* @param hidden_biases Wczytane z pliku informacje o obci��eniach warstw ukrytych
		* @return Prawda je�li walidacja przebieg�a pomy�lnie. Fa�sz w przeciwym razie.
		*/
		bool validate(
			std::string & reason,
			int & ref_layers,
			std::vector<int> & ref_hidden_r,
			std::vector<int> & ref_hidden_c,
			std::vector<double> & hidden_weights,
			std::vector<double> & hidden_biases
		);
	};

	//! Klasa generatora schematu
	/*!
	Klasa implementuj�ca generator pliku schematu sieci o wymiarach podanych przez u�ytkownika
	*/
	class CNNSchemaGenerator {
	public:
		/** Ci�g tekstowy zawieraj�cy w sobie kod schematu */
		std::string target_str;
		/**
		* Konstruktor
		* @param code Kod schematu
		*/
		CNNSchemaGenerator(std::string code);
		/**
		* Metoda generuj�ca plik schematu i wy�wietlaj�ca go w konsoli.
		* @return Prawda je�li uda�o si� wygenerowa� plik schematu. Fa�sz w przeciwnym razie.
		*/
		bool generate();
	};

} // namespace neural