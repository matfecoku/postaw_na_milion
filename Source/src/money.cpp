#include "money.h"
#include <sstream>
#include "style_manager.h"

Money::Money(int start_amount) 
	: m_amountHeld(start_amount), // Aktualnie trzymana kwota
	m_startAmount(start_amount) // Poczatkowa kwota pieniedzy
	{}

Money::Money() : m_amountHeld(1'000'000), m_startAmount(1'000'000) {}

bool Money::deduct_money(const int amount) {
	if (amount > m_amountHeld)
	{
		m_amountHeld = 0;
		return false;
	}
	m_amountHeld -= amount;
	return true;
}

int Money::get_money() const { return m_amountHeld; }

std::string Money::pretty_print() const {
	// Dodaje przecinki dla duzych cyfr dla latwiejszej czytelnosci
	std::string num = std::to_string(m_amountHeld); // Konwersja liczby na string
	std::string result; // Wynikowy string ze sfrormatowana liczba
	int len = num.length(); // Dlugosc liczby w stringu

	for (int i = 0; i < len; ++i) {
		// Dodaj przecinek co 3 cyfry od prawej (ale nie na poczatku)
		// i > 0 - nie dodawaj przecinka na poczatku
		// (len - i) % 3 == 0 - sprawdz czy jestesmy co 3 cyfry od prawej
		if (i > 0 && (len - i) % 3 == 0) {
			result += ',';
		}
		result += num[i];
	}
	
	StyleManager style; // Obiekt do formatowania

	return style.bright_green() + result + style.reset() ;
}

bool Money::add_money(const int amount) {
	if (amount > m_startAmount)
	{
		m_amountHeld = m_startAmount;
		return false;
	}
	m_amountHeld += amount;
	return true;
}

std::string Money::pretty_print(const int amount) {
	std::string num = std::to_string(amount);
	std::string result;
	int len = num.length();

	// Dodaj przecinek co 3 cyfry od prawej (ale nie na poczatku)
	// i > 0 - nie dodawaj przecinka na poczatku
	// (len - i) % 3 == 0 - sprawdz czy jestesmy co 3 cyfry od prawej
	for (int i = 0; i < len; ++i) {
		if (i > 0 && (len - i) % 3 == 0) {
			result += ',';
		}
		result += num[i];
	}

	return result;
}