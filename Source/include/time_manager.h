#pragma once

#include <chrono>
#include <string>

// @class Time
// @brief Klasa zarzadzajaca operacjami czasowymi
//
// Klasa odpowiedzialna za:
// - pobieranie aktualnego czasu
// - formatowanie znacznikow czasu
class Time {
public:
	// @brief Pobiera aktualny znacznik czasu
	// @return Znacznik czasu w formacie system_clock::rep
	std::chrono::system_clock::rep get_current_timestamp();

	// @brief Formatuje znacznik czasu do czytelnej postaci
	// @param timestamp Znacznik czasu do sformatowania
	// @return Sformatowany string z data i czasem
	std::string format_timestamp(std::chrono::system_clock::rep timestamp);
};