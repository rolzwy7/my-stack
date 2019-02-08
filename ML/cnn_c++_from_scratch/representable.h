#pragma once
#include <string>

/*! \file representable.h
	\brief Zawiera klas� czysto wirtualn� wspomagaj�c� wy�wietlanie obiekt�w innych klas w konsoli.
*/

//! Klasa wirtualna implementuj�ca wy�wietlanie macierzy
/*!
Klasa odpowiadaj�ca za wy�wietlanie macierzy w czytelny spos�b.
*/
class Representable {
public:
	/**
	* Czysto wirtualny dekonstruktor
	*/
	virtual ~Representable() {}
	/**
	* Wirtualna metoda zwracaj�ca macierz jako tekst
	* @return Tekst reprezentuj�cy macierz w czytelnym formacie.
	*/
	virtual std::string asText() const = 0;
};
/**
* Przeci�zenie operatora wyj�cia strumienia dla klasy dziedzicz�cej po klasie Representable
* @param stream Strumie� wyj�ciowy.
* @param printable Sta�a referencja na objekt klasy Representable
* @return Strumie� wyj�ciowy.
*/
std::ostream & operator<<(std::ostream & stream, const Representable & printable);