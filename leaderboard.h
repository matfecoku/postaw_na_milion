#pragma once
#include <string>
#include <vector>
#include <chrono>
#include "money.h"
#include "save.h"

// @struct LeaderboardEntry
// @brief Struktura reprezentujaca pojedynczy wpis tabeli wynikow
//
// Struktura przechowuje:
// - czas zapisu wyniku
// - imie gracza
// - wygrana kwote
struct LeaderboardEntry {
	// @brief Znacznik czasu zapisu wyniku
	std::chrono::system_clock::rep timestamp;

	// @brief Imie gracza
	std::string name;

	// @brief Wygrana kwota
	unsigned int money;
};

// @class Leaderboard
// @brief Klasa zarzadzajaca tabela wynikow
//
// Klasa odpowiedzialna za:
// - przechowywanie wynikow graczy
// - wyswietlanie tabeli wynikow
// - zapisywanie wynikow do pliku
class Leaderboard : SaveFile {
public:
	// @brief Konstruktor z nazwa pliku
	// @param filename Nazwa pliku z tabela wynikow
	Leaderboard(std::string filename);

	// @brief Konstruktor z pelnymi parametrami
	// @param filename Nazwa pliku z tabela wynikow
	// @param name Nazwa gracza
	// @param money MObiekt z wygrana kwota
	Leaderboard(std::string filename, 
		std::string name,
		Money money);

	// @brief Wyswietla tabele wynikow
	// @return true Jesli wyswietlanie sie powiodlo
	bool show_leaderboard();

	// @brief Zapisuje tabele wynikow do pliku
	// @return true Jesli zapis sie powiodl
	bool write_to_file() override;
private:

	// @brief Wektor przechowujacy wpisy w tabeli wynikow
	std::vector<LeaderboardEntry> m_leaderboard;

	// @brief Nazwa gracza
	std::string m_name;

	// @brief Obiekt przechowujacy wygrana kwote
	Money m_money;

	// @brief Znacznik czasu wpisu
	std::chrono::system_clock::rep m_timestamp;
};