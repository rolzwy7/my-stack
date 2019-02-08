#pragma once

/*! \file activation.h
	\brief Zawiera funkcje aktywacyjne i funkcje wspomagaj�ce generowanie liczb psedolosowych.

	Plik implementuje funkcje aktywacyjne oraz funkcje generuj�ce liczby pseudolosowe u�ywane w zape�nianiu warstw sieci warto�ciami.
*/

/**
* Losuje liczbe typu double.
* @param a Pocz�tek zakresu losowania.
* @param b Koniec zakresu losowania.
* @return Losowa liczba typu double.
*/
double random_double(double a, double b);

/**
* Alias funkcji random_double()
* @return Losowa liczba typu double z zakresu od 0,01 do 0,99.
*/
double get_random_weight();

/**
* Funkcja sigmoid https://en.wikipedia.org/wiki/Sigmoid_function
* @param value Warto�� przekazywana do funkcji.
* @param constant Sta�a c.
* @return double
*/
double sigmoid(double value, int constant);