#pragma once
#include <string>
#include <vector>

// @class Input
// @brief Klasa zarzadzajaca wprowadzaniem danych
//
// Klasa odpowiedzialna zA:
// - obsluge wprowadzania roznych typow danych
// - walidacje wprowadzonych wartosci
// - czyszczenie bufora wejscia
class Input {
public:
	// @brief Wczytuje liczbe z zakresu [0, max_range]
	// @param max_range Maksymalna dozwolona wartosc
	// @return Wczytana liczba
	int number(int max_range) const;

	// @brief Wczytuje liczbe z zakresu [min_range, max_range]
	// @param min_range Minimalna dozwolona wartosc
	// @param max_range Maksymalna dozwolona wartosc
	// @return Wczytana liczba
	int number(int min_range, int max_range) const;

	// @brief Wczytuje odpowiedz tak/nie
	// @return true dla 't' (lub 'T')
	// @return false dla 'n' (lub 'N')
	bool yes_no() const;

	// @brief Wczytuje dowolny string
	std::string string() const;

	// @brief Wczytuje string o maksymalnej dlugosci
	// @param max_length Maksymalna dozwolona dlugosc
	// @return Wczytany string
	std::string string(int max_length) const;

	// @brief Czysci bufor wejscia
	void clear_buffer() const;
private:

	// @brief Przechowuje ostatnio wczytana wartosc
	int m_choice;

	// @brief Szablonowa metoda do obslugi wczytywania danych
	// @tparam T Typ wczytywania danych
	// @param input Referencja do zmiennej, do ktorej wczytujemy
	template<typename T>
	void handle_input_field(T& input) const;

	// @brief Obsluguje nieprawidlowe dane wejsciowe
	void handle_failed_input() const;
};