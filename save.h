#pragma once
#include "file_manager.h"

// @brief Klasa odpowiedzialna za zapisywanie stanu gry
//
// Klasa dziedziczaca po FileManager, ktora:
// - zarzadza zapisem stanu gry do pliku
// - obsluguje operacje zapisu i odczytu danych gry
// - zapewnia podstawowa funkcjonalnosc do zarzadzania plikami zapisu
class SaveFile : public FileManager {
public:
	// @brief Konstruktor klasy zapisu
	// @param filename Nazwa pliku do zapisu
	SaveFile(std::string filename);

	// @brief Zapisuje dnae do pliku
	// @return true Jesli zapis sie udal
	virtual bool write_to_file() = 0;
};
