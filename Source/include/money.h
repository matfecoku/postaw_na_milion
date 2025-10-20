#pragma once
#include <string>

// @class Money
// @brief Klasa zarzadzajaca pieniedzmi w grze
//
// Klasa odpowiedzialna za:
// - przechowywanie aktualnej kwoty pieniedzy
// - operacje na pieniadzach (dodawanie, odejmowanie)
// - formatowanie kwot do wyswietlania
class Money {
public:
	// @brief Konstruktor inicjalizujacy kwote poczatkowa
	// @param start_amount Poczatkowa kwota pieniedzy
	Money(int start_amount);

	// @brief Konstruktor domyslny
	Money();

	// @brief Odejmuje okreslona kwote od stanu konta
	// @param amount Kwota do odjecia
	// @return true Jesli operacja sie udala
	// @return false Jesli brak srodkow
	bool deduct_money(const int amount);

	// @brief Dodaje okreslona kwote do stanu konta
	// @param amount Kwota do dodania
	// @return true Jesli operacja sie udala
	bool add_money(const int amount);

	// @brief Zwraca aktualna kwote pieniedzy
	// @return Aktualny stan konta
	int get_money() const;

	// @brief Formatuje aktualna kwote do wyswietlania
	// @return Sformatowany string z kwota
	std::string pretty_print() const;

	// @brief Formatuje podana kwote do wyswietlenia
	// @param amount Kwota do sformatowania
	// @return Sformatowany string z kwota
	static std::string pretty_print(const int amount);
private:

	// @brief Aktualna kwota pieniedzy
	int m_amountHeld;

	// @brief Poczatkowa kwota pieniedzy
	const int m_startAmount;
};