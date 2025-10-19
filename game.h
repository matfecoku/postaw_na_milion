#pragma once
#include <cstdint>
#include "player.h"
#include "save_state.h"

// @brief Nazwy plikow uzywanych w grze
const std::string LEADERBOARD_FILE_NAME = "leaderboard.txt"; // Plik z tabela wynikow
const std::string SAVE_FILE_NAME = "savefile.txt"; // Plik zapisu gry
const std::string QUESTIONS_FILE_NAME = "questions.txt"; // Plik z pytaniami

// @brief Stale konfiguracyjne uzywane w grze
constexpr int START_AMOUNT = 1'000'000; // Poczatkowa kwota w grze
constexpr int ROUNDS = 8; // Liczba rund w grze
constexpr int MAX_PLAYER_NAME_LENGTH = 12; // Maksymalna dlugosc imienia gracza

// @class Game
// @brief Glowna klasa zarzadzajaca rozgrywka
//
// Klasa odpowiedzialna za zarzadzanie rozgrywka w tym:
// - inicjalizacje gry
// - zarzadzanie rundami
// - obsluge zapisu i wczytywania gry
// - zarzadzanie tabela wynikow
class Game {
public:
	// @brief Konstruktor domyslny
	Game();

	// @brief Destruktor
	~Game();

	// @brief Inicjalizacja gry i jej komponentow
	void init();

	// @brief Zamykanie gry i czyszczenie
	void close_game();

	// @brief Rozpoczecie gry z wczytanego stanu
	// @param saveInfo Informacje o zapisie
	void start_game(SaveInfo& saveInfo);

	// @brief Rozpoczecie nowej gry
	void start_game();

	// @brief Wczytanie zapisanej gry
	void load_game();

	// @brief Wyswietlenie tabeli wynikow
	void show_leaderboard();

	// @brief Wyswietlenie glownego menu
	void main_menu();

	// @brief Zapisanie wyniku do tabeli wynikow
	// @param p Obiekt gracza do zapisania
	void save_to_leaderboard(Player& p);
private:
};