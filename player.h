#pragma once
#include "money.h"
#include <string>

// @class Player
// @brief Klasa reprezentujaca gracza
//
// Klasa przechowuje informacje o graczu, w tym:
// - stan konta gracza (obiekt Money)
class Player {
public:
	// @brief Konstruktor tworzacy nowego gracza
	// @param start_amount Poczatkowa kwota pieniedzy dla gracza
	Player(int start_amount);

	// @brief Obiekt przechowujacy stan konta gracza
	Money money;
};