#pragma once
#include <string>

// @brief Klasa bazowa do zarzadzania plikami
//
// Klasa odpowiedzialna za:
// - podstawowa obsluge operacji na plikach
// - zarzadzanie nazwami plikow
// - sprawdzanie istnienia plikow
// - zapewnienie wspolnej funkcjonalnosci dla klas dziedziczacych
// - obsluge bledow zwiazanych z operacjami na plikach
class FileManager {
public:
	// @brief Konstruktor klasy zarzadzajacej plikami
	// @param filename Nazwa pliku do zarzadzania
	FileManager(std::string filename);

	// @brief Sprawdza czy plik istnieje
	// @return true Jesli plik istnieje
	bool get_fileExists();

	// @brief Zwraca nazwe pliku
	// @return Nazwa pliku
	std::string get_filename();

	// @brief Usuwa plik
	// @return Zwraca true Jezeli usuwanie plikow sie powiedzie
	bool remove_file();
private:
	// @brief Nazwa pliku
	std::string m_filename;
	// @brief Flaga okreslajaca czy plik istnieje
	bool m_fileExists;
};