#pragma once
#include "question.h"
#include "load.h"
#include <vector>
#include "player.h"

// @brief Klasa odpowiedzialna za wyswietlanie informacji
//
// Klasa odpowiedzialna za:
// - wyswietlanie glownego menu
// - prezentacje statusu gracza
// - formatowanie wyswietlanych informacji
// - zarzadzanie interfejsem uzytkownika
// - obsluge wyswietlania komunikatow systemowych
class Info {
private:
	// @brief Maksymalna liczba dostepnych opcji
	int m_maxRange;
public:
	// @brief Konstruktor domyslny
	Info();

	// @brief Wyswietla glowne menu gry
	// @param canContinue Czy mozna kontynuowac gre
	void main_menu(bool canContinue);

	// @brief Zwraca maksymalny zakres opcji
	// @return Maksymalna liczba dostepnych opcji
	int get_maxRange() const;

	// @brief Wyswietla status gracza
	// @param p Referencja do obiektu gracza
	void player_status(const Player& p) const;

	// @brief Wyswietla informacje o tym co mozna zrobic z zapadka
	void trapdoor_status() const;

	// @brief Wyswietla informacje o numerze rundy, nie wyswietla nic gdy id < 1
	// @param id Numer rundy
	void round_status(int id) const;
};