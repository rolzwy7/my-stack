#pragma once
#include <string>
#include "array2d.h"

/*! \file cnn.h
	\brief Plik implementuje splotow� sie� neuronow�
*/

namespace neural {

	//! Klasa reprezentuj�ca splotow� sie� neuronow�
	/*!
		Klasa reprezentuj�ca splotow� sie� neuronow� oraz metody umo�liwiaj�ce jej wytrenowanie.
	*/
	class ConvolutionalNeuralNetwork {
		
	public:
		/** Czy aktualizowa� obci��enia */
		bool bias_update;
		/** Ilo�� warstw sieci */
		unsigned int layers;
		/** Ca�kowity b��d sieci */
		double total_error;
		/** Szybko�� uczenia si� */
		double learning_rate;
		/** Wska�nik na tablic� wag */
		math::collections::Matrix * weights;
		/** Wska�nik na tablic� obci��e� */
		math::collections::Matrix * biases;
		/** Wska�nik na tablic� warto�ci wyj�ciowych neuron�w */
		math::collections::Matrix * out_values;

		/**
		* Konstruktor
		* @param layers Ilo�� warstw sieci
		* @param learning_rate Szybko�� uczenia si�
		*/
		ConvolutionalNeuralNetwork(unsigned int layers, double learning_rate);
		/**
		* Deksonstruktor. Zwalnia alokowan� pami��.
		*/
		~ConvolutionalNeuralNetwork();
		/**
		* Algorytm "feedforward" (karmienie sieci do przodu)
		* @param input Dane wej�ciowe
		* @param output Dane wynikowe
		* @return void
		*/
		void feedforward(const math::collections::Matrix & input, math::collections::Matrix & output);
		/**
		* Algorytm "feedbackward" (karmienie sieci od ty�u)
		* @param ideal Dane "idealne"
		* @return void
		*/
		void feedbackward(const math::collections::Matrix & ideal);
		/**
		* Trenuje sie� na podstawie pojedy�czego rekordu danych
		* @param input Dane wej�ciowe
		* @param ideal Dane "idealne"
		* @return Ca�kowity b��d sieci
		* @see feedforward()
		* @see feedbackward()
		*/
		double train(const math::collections::Matrix & input, const math::collections::Matrix & ideal);
		/**
		* Wy�wietla na ekran budow� sieci
		* @return void
		*/
		void print_details();
		/**
		* Zapisuje plik schematu sieci do pliku
		* @param filepath �cie�ka do pliku
		* @param msg Wiadomo�� wy�wietlana u�ytkownikowi
		* @return Prawda je�li uda�o si� zapisa� plik schematu. Fa�sz w przeciwnym razie.
		*/
		bool save(std::string filepath, std::string & msg);
	};
}
