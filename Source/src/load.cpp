#include "load.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "question.h"

LoadFile::LoadFile(std::string filename)
					: FileManager(filename) {
}

bool LoadFile::load_leaderboard(std::vector<LeaderboardEntry>& leaderboard) {
	if (!get_fileExists())
	{
		std::cerr << "Nie mozna otworzyc pliku z tabela wynikow." << std::endl;
		return false;
	}

	std::ifstream file(this->get_filename()); // Strumien do odczytu pliku
	std::string line; // Bufor na wczytana linie
	while (std::getline(file, line)) {
		std::stringstream ss(line); // Strumien do parsowania linii
		std::string timestamp, name, money_left; // Pola w tabeli wynikow

		if (std::getline(ss, timestamp, '\t') &&
			std::getline(ss, name, '\t') &&
			std::getline(ss, money_left)) {
			try {
				LeaderboardEntry entry; // Nowy wpis w tabeli wynikow
				entry.timestamp = std::stoll(timestamp);
				entry.name = name;
				entry.money = std::stoi(money_left);
				leaderboard.push_back(entry);
			}
			catch (const std::exception& e) {
				std::cerr << "Pomijanie zlej linii: " << line << std::endl;
				continue;
			}
		}
		else {
			std::cerr << "Pomijanie zlej linii: " << line << std::endl;
		}
	}
	file.close();
	return true;
}

bool LoadFile::load_questions(std::vector<Question>& question_list) {
	if (!get_fileExists())
	{
		std::cerr << "Nie mozna otworzyc pliku z pytaniami." << std::endl;
		return false;
	}
	std::ifstream file(this->get_filename()); // Strumien do odczytu pliku
	std::string line; // Bufor na wczytana linie
	while (std::getline(file, line)) {
		std::stringstream ss(line); // Strumien do parsowania linii
		std::string category; // Kategoria pytania
		std::string question; // Tresc pytania
		std::string correct_answer; // Poprawna odpowiedz
		std::string wrong_answers[ANSWER_AMOUNT-1]; // Tablica blednych odpowiedzi

		Question quest; // Obiekt pytania
		try {
			if (std::getline(ss, category, '\t') &&
				std::getline(ss, question, '\t'))
			{
				quest.set_category(quest.string_to_category(category));
				quest.set_question(question);
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Nie mozna zaladowac pytania, pomijanie: " << line << std::endl;
			continue;
		}
		try {

			if (std::getline(ss, correct_answer, '\t'))
			{
				Answer ans(true, correct_answer); // Utworzenie poprawnej odpowiedzi
				quest.set_answer(0, ans);
			}
			for (int i = 1; i < ANSWER_AMOUNT; i++)
			{
				if (std::getline(ss, wrong_answers[i - 1], '\t'))
				{
					Answer ans(false, wrong_answers[i - 1]); // Utworzenie blednej odpowiedzi
					quest.set_answer(i, ans);
				}
			}
			question_list.push_back(quest);
		}
		catch (const std::exception& e) {
			std::cerr << "Pomijanie zlej linii: " << line << std::endl;
			continue;
		}
	}
	file.close();
	return true;
}