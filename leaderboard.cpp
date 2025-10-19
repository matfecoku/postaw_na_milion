#include "leaderboard.h"
#include "load.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "time.h"
#include "money.h"
#include <iostream>
#include <fstream>

// Liczba najlepszych wynikow do wyswietlenia
constexpr int TOP_SCORES_AMOUNT = 5;

Leaderboard::Leaderboard(std::string filename,
	std::string name,
	Money money) 
	: SaveFile(filename), 
	m_name(name),
	m_money(money)
{
	// Inicjalizacja snowego wpisu w tabeli wynikow
	Time time; // Obiekt do obslugi czasu
	m_timestamp = time.get_current_timestamp();
}

Leaderboard::Leaderboard(std::string filename) : SaveFile(filename) {}

bool Leaderboard::write_to_file() {
	// Zapisanie wyniku do pliku tabeli wynikow
	std::fstream file; // Strumien do zapisu plikow
	
	bool fileExists = this->get_fileExists();
	file.open(this->get_filename(), std::fstream::app);
	if (!file.is_open()) return false;
	if (fileExists) file << '\n';
	file << m_timestamp << '\t' << m_name << '\t' << m_money.get_money();
	std::cout << "Zapisano wynik do tabeli wynikow." << std::endl;
	return true;
}

bool Leaderboard::show_leaderboard() {
	// Wyswietlenie najlepszych wynikow
	LoadFile save(this->get_filename()); // Obiekt do wczytywania wynikow
	m_leaderboard.clear();
	if (!save.load_leaderboard(m_leaderboard)) {
		std::cerr << "Nie znaleziono pliku " << this->get_filename() << std::endl;
		std::cerr << "Nie mozna bylo zaladowac tabeli wynikow." << std::endl;
		return false;
	}

	// Sortowanie wynikow malejaco
	std::sort(m_leaderboard.begin(), m_leaderboard.end(),
		[](const LeaderboardEntry& a, const LeaderboardEntry& b) {
			return a.money > b.money;
		});

	// Wyswietlenie naglowka tabeli
	std::cout << "Najlepsze " << TOP_SCORES_AMOUNT << " wynikow:" << std::endl;
	std::cout << "Nr   | Nazwa      | Wynik      | Data" << std::endl;
	std::cout << std::string(50, '-') << std::endl;

	Time t; // Obiekt do formatowania czasu

	// Wyswietlenie najlepszych wynikow
	for (int i = 0; i < std::min<int>(TOP_SCORES_AMOUNT, m_leaderboard.size()); ++i) {
		std::cout << std::left << std::setw(4) << i + 1 << " | "
			<< std::setw(10) << m_leaderboard[i].name << " | "
			<< std::setw(10) << Money::pretty_print(m_leaderboard[i].money) << " | "
			<< t.format_timestamp(m_leaderboard[i].timestamp) << std::endl;
	}
	return true;
}