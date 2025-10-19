#pragma once
#include "file_manager.h"
#include <vector>
#include "leaderboard.h"
#include "question.h"

// @brief Klasa odpowiedzialna za wczytanie danych gry
//
// Klasa dziedziczaca po FileManager, ktora:
// - zarzadza wczytywaniem danych z plikow
// - obsluguje wczytywanie tabeli wynikow
// - obsluguje wczytywanie pytan do gry
// - zapewnia podstawowa funkcjonalnosc do zarzadzania plkikami do odczytu
class LoadFile : public FileManager {
public:
	// @brief Konstruktor klasy wczytujacej pliki
	// @param filename Nazwa pliku do wczytania
	LoadFile(std::string filename);

	// @brief Wczytuje tabele wynikow z pliku
	// @param leaderboard Referencja do wektora wpisow w tabeli wynikow
	// @return true Jesli wczytanie sie powiodlo
	bool load_leaderboard(std::vector<LeaderboardEntry>& leaderboard);

	// @brief Wczytuje pytania z pliku
	// @param question_list Referencja do wektora pytan
	// @return true Jesli wczytanie sie powiodlo
	bool load_questions(std::vector<Question>& question_list);
};