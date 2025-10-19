#include "trapdoor.h"
#include "input.h"
#include <iostream>
#include <string>
#include "style_manager.h"

Trapdoor::Trapdoor(std::string label, bool isCorrect)
	: m_label(label),
	m_isCorrect(isCorrect),
	m_moneyPlaced(0)
{};

bool Trapdoor::place_money(Player& p, int amount) {
	// Stawianie pieniedzy na zapadce
	if (p.money.get_money() >= amount)
	{
		m_moneyPlaced += amount;
		p.money.deduct_money(amount);
		return true;
	}
	// Prosba o postawienie wszystkcih dostepnych pieniedzy
	StyleManager style; // Menedzer stylow do formatowania tekstu
	std::cerr << style.red() <<
		"Nie masz wystarczajaco pieniedzy." <<
		style.reset() << std::endl
		<< "Czy chcesz polozyc wszystkie dostepne pieniadze? " <<
		style.yellow() <<
		"[T / N]" <<
		style.reset() <<
		std::endl;
	Input user_input; // Obiekt do obslugi wejscia uzytkownika
	if (user_input.yes_no()) {
		int currentMoney = p.money.get_money(); // Aktualna kwota pieniedzy gracza
		m_moneyPlaced += currentMoney;
		p.money.deduct_money(currentMoney);
		return true;
	}
	return false;
}

bool Trapdoor::remove_money(Player& p, int amount)
{
	StyleManager style; // Menadzer stylow do formatowania tekstu
	// Zabieranie pieniedzy z zapadki
	if (m_moneyPlaced == 0)
	{
		std::cerr <<
			style.red() <<
			"Zapadka jest pusta." <<
			style.reset() <<
			std::endl <<
			std::endl;
		return false;
	}

	if (m_moneyPlaced >= amount)
	{
		m_moneyPlaced -= amount;
		p.money.add_money(amount);
		return true;
	}
	// Prosba o zabranie wszystkcih pieniedzy
	std::cerr << style.red() 
		<< "Podana wartosc przekracza ilosc pieniedzy na zapadce." << 
		style.reset() << std::endl
		<< "Czy chcesz usunac cala kwote? " << 
		style.yellow() << 
		"[T / N]" << 
		style.reset() << 
		std::endl;
	Input user_input; // Obiekt do obslugi wejscia uzytkownika
	if (user_input.yes_no()) {
		p.money.add_money(m_moneyPlaced);
		m_moneyPlaced = 0;
		return true;
	}
	return false;
}

std::string Trapdoor::get_label() const {
	return m_label;
}

int Trapdoor::get_moneyPlaced() const {
	return m_moneyPlaced;
}

bool Trapdoor::get_isCorrect() const {
	return m_isCorrect;
}

bool Trapdoor::get_isAvailable() const {
	return m_isAvailable;
}

void Trapdoor::set_isAvailable(bool isAvailable) {
	m_isAvailable = isAvailable;
}