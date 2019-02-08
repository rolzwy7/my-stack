#pragma once
#include <fstream>
#include <string>
#include "array2d.h"

/*! \file cnn_dataset.h
	\brief Implementuje �adowanie danych i ich walidacje
*/

namespace neural {

	/**
	* Funkcja zape�niaj�ca macierze danymi wej�ciowymi i wyj�ciowymi z wektora
	* @param inputs Wska�nik na dane wej�ciowe
	* @param outputs Wska�nik na dane wyj�ciowe
	* @param mat_num Ilo�� weirszy danych
	* @param inputs_col Liczba kolumn w macierzy warstwy wej�ciowej
	* @param outputs_col Liczba kolumn w macierzy warstwy wyj�ciowej
	* @param training_data Wektor danych treningowych
	* @return void
	*/
	void populate_matrices(
		math::collections::Matrix * inputs,
		math::collections::Matrix * outputs,
		int mat_num,
		int inputs_col,
		int outputs_col,
		std::vector<double> & training_data
	);

	//! Klasa reprezentuj�ca zbi�r danych wej�ciowych
	/*!
	Klasa reprezentuj�ca zbi�r danych wej�ciowych w formacie csv oraz odpowiedzialna za ich walidacje
	*/
	class CNNDataset {
		public:
			/** Uchwyt do pliku z danymi */
			std::fstream file_handle;
			/** �cie�ka do pliku z danymi */
			std::string filepath;
			/** Wska�nik na tablic� zawieraj�c� nag��wki danych */
			std::string * headers;
			/** Liczba za�adowanych linii danych */
			int datalines;
			/** Spodziewana liczba kolumn pliku csv */
			int expected_data_num;
			/**
			* Konstruktor
			* @param filepath �cie�ka do pliku
			* @param expected_data_num Oczekiwana ilo�� danych (kolumn pliku csv)
			* @return void
			*/
			CNNDataset(std::string filepath, int expected_data_num);
			/**
			* Destruktor klasy. Zwalnia pami��.
			*/
			~CNNDataset();
			/**
			* Metoda odpowiedzialna za �adowanie danych z pliku i ich walidacje
			* @param msg Wiadomo�� wy�wietlana u�ytkownikowi po zako�czeniu dzia�ania funkcji
			* @param data_vector Wektor do kt�rego zostan� za�adowane zwalidowane dane
			* @return Pradwa je�li walidacja przebieg�a pomy�lnie. Fa�sz w przeciwnym razie.
			*/
			bool validate(std::string & msg, std::vector<double> & data_vector);
	};

} // namespace neural