#include "info.h"
#include "menu.h"
#include <iostream>
#include "style_manager.h"

Info::Info() : m_maxRange(0)
{
	
}

void Info::main_menu(bool canContinue) {
	// Wyswietlenie glownego menu gry
	int index = 0;
	std::cout << "Wybierz opcje:" << std::endl;
	StyleManager style; // Obiekt formatowania tekstu
	std::cout << style.yellow() << "[" << ++index << "] " << style.reset() << "Rozpocznij gre" << std::endl;
	if (canContinue) std::cout << style.yellow() << "[" << ++index << "] " << style.reset() << "Kontynuuj gre" << std::endl;
	std::cout << style.yellow() << "[" << ++index << "] " << style.reset() << "Pokaz tabele wynikow" << std::endl;
	std::cout << style.yellow() << "[" << ++index << "] " << style.reset() << "Zakoncz gre" << std::endl;
	m_maxRange = index;
}

int Info::get_maxRange() const {
	return m_maxRange;
}

void Info::player_status(const Player& player) const {
	// Wyswietlenie statusu gracza
	std::cout << "Pozostala gotowka: " << // Obiekt do formatowania tekstu
		player.money.pretty_print() <<
		std::endl;
}

void Info::trapdoor_status() const {
	// Wyswietla informacje o tym co mozna zrobic z zapadka
	StyleManager style;
	std::cout <<
		"Wybierz opcje:" <<
		std::endl <<
		style.yellow() <<
		"[1] " <<
		style.reset() <<
		"Poloz pieniadze" <<
		std::endl <<
		style.yellow() <<
		"[2] " <<
		style.reset() <<
		"Usun pieniadze" <<
		std::endl <<
		style.yellow() <<
		"[3] " <<
		style.reset() <<
		"Wroc" <<
		std::endl <<
		std::endl;
}

void Info::round_status(int id) const {
	if (id < 1) {
		return;
	}
	std::cout <<
		std::endl <<
		std::endl <<
		std::string(20, '-') <<
		" Runda " <<
		id <<
		" " <<
		std::string(20, '-') <<
		std::endl <<
		std::endl <<
		std::endl;
}