#pragma once

// @brief Opcje dostepne w menu glownym
enum MENU_OPTIONS {START=1, CONTINUE, LEADERBOARD, EXIT};

// @class Menu
// @brief Klasa zarzadzajaca menu glownym
//
// Klasa odpowiedzialna za:
// - wyswietlanie opcji menu
// - obsluge wyboru uzytkownika
// - walidacje wprowadzanych danych
class Menu {
public:
	// @brief Konstruktor menu
	// @param max_range Maksymalna liczba dostepnych opcji
	Menu(int max_range);

	// @brief Wczytuje wybor od uzytkownika
	// @return Numer wybranej opcji
	int get_choice();
private:
	// @brief Przechowuje wybor uzytkownika
	int m_choice;

	// @brief Maksymalna liczba dostepnych opcji
	int m_maxRange;

	// @brief Obsluguje wprowadzanie danych przez uzytkownika
	void handle_user_input();
};