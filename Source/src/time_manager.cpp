#include "time_manager.h"
#include <ctime>
#include <sstream>
#include <iomanip>

std::chrono::system_clock::rep Time::get_current_timestamp() {
	// Pobranie aktualnego znacznika czasu
	return std::chrono::system_clock::now().time_since_epoch().count();
}

std::string Time::format_timestamp(std::chrono::system_clock::rep timestamp) {
	// Konwersja znacznika czasu na czytelna date i czas
	std::chrono::system_clock::duration duration = std::chrono::system_clock::duration(timestamp);
	std::chrono::system_clock::time_point time_point = std::chrono::system_clock::time_point(duration);

	// Konwersja na format time_t
	__time64_t time_t = std::chrono::system_clock::to_time_t(time_point);
	
	// Konwersja na strukture tm
	tm tm_s = {}; // Struktura przechowujaca czas w formacie lokalnym
	localtime_s(&tm_s, &time_t);

	// Formatowanie do stringa w formacie DD-MM-YY HH:MM:SS
	std::ostringstream oss; // Strumien do formatowania stringa
	oss << std::put_time(&tm_s, "%d-%m-%y %H:%M:%S");
	return oss.str();
}