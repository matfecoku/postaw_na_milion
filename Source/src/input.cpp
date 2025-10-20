#include "input.h"
#include <iostream>
#include "style_manager.h"

int Input::number(int max_range) const{
	// Wczytanie liczby z zakresu [1, max_range]
	int input = 0; // Zmienna do przechowywania wczytanej liczby
	while (true) {
		handle_input_field(input);
		if (!std::cin.fail() && input > 0 && input <= max_range) break;
		handle_failed_input();
	}
	return input;
}

int Input::number(int min_range, int max_range) const {
	// Wczytanie liczby z zakresu [min_range, max_range]
	int input = 0; // Zmienna do przechowywania wczytanej liczby
	while (true) {
		handle_input_field(input);
		if (!std::cin.fail() && input >= min_range && input <= max_range) break;
		handle_failed_input();
	}
	return input;
}


bool Input::yes_no() const{
	// Wczytanie odpowiedzi tak/nie (t/n)
	const char CORRECT_VAL = 't'; // Wartosc oznaczajaca "tak"
	const char INCORRECT_VAL = 'n'; // Wartosc oznaczajaca "nie"
	char input = '0'; // Zmienna do przechowywania wczytanego znaku
	while (true)
	{
		handle_input_field(input);
		input = std::tolower(input); // Konwersja na mala litere
		if (!std::cin.fail() &&
			(input == CORRECT_VAL ||
			input == INCORRECT_VAL)
			) break;
		handle_failed_input();
	}
	switch (input) {
	case CORRECT_VAL:
		return true;
	case INCORRECT_VAL:
	default:
		return false;
	}
}

std::string Input::string() const{
	// Wczytanie dowolnego stringa
	std::string input; // Zmienna do przechowywania wczytanego tekstu
	while (true) {
		handle_input_field(input);
		if (!std::cin.fail()) break;
		handle_failed_input();
	}
	return input;
}

std::string Input::string(int max_length) const {
	std::string input;
	while (true) {
		handle_input_field(input);
		if (!std::cin.fail() &&
			input.length() <= max_length) 
			break;
		handle_failed_input();
	}
	return input;
}

template<typename T>
void Input::handle_input_field(T& input) const{
	// Obsluga wczytywania danych z konsoli
	std::cout << ">> ";
	StyleManager style; // Obiekt do formatowania tekstu
	std::cout << style.cyan();
	std::cin >> input;
}

void Input::handle_failed_input() const{
	// Obsluga blednego wprowadzenia danych
	std::cerr << "Wprowadzono bledne dane." << std::endl;
	clear_buffer();
}

void Input::clear_buffer() const {
	// Czyszczenie bufora wjescia
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}