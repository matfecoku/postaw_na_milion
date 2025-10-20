#include "save_state.h"
#include <fstream>
#include "game.h"
#include <iostream>
#include <sstream>

SaveState::SaveState(const std::string filename,
	std::vector<Question>& questions,
	int money_left, int question_id, int round_id, bool is_lifeline_available)
	: SaveFile(filename),
	m_questions(questions),
	m_moneyLeft(money_left),
	m_questionId(question_id),
	m_roundId(round_id),
	m_isLifelineAvailable(is_lifeline_available)
{}

SaveState::SaveState(const std::string filename, 
	std::vector<Question>& question) 
	: SaveFile(filename),
	m_questions(question)
{
	
}

bool SaveState::write_to_file() {
	// Otwarcie pliku do zapisu
	std::fstream file; // Strumien do zapisu pliku

	bool fileExists = this->get_fileExists(); // Sprawdzanie czy plik istnieje
	file.open(this->get_filename(), std::fstream::out);
	if (!file.is_open()) return false;

	// Zapisanie podstawowych informacji o stanie gry
	// Format: money_left question_id round_id is_lifeline_available
	file << m_moneyLeft << '\t' << m_questionId << '\t' << m_roundId << '\t' << m_isLifelineAvailable << '\n';

	// Zapisanie pytan i odpowiedzi
	// Dla kazdego pytania:
	// - tekst pytania
	// - ID kategorii
	// - dla kazdej odpowiedzi:
	// - - podpis
	// - - flaga poprawnosci
	for (int i = 0; i < m_questions.size(); ++i)
	{
		// Zapisanie tekstu pytania i ID kategorii
		file << m_questions[i].get_question() << '\t' << m_questions[i].get_category_id() << '\t';

		// Zapisanie odpowiedzi na pytania
		for (int j = 0; j < ANSWER_AMOUNT; ++j)
		{
			file << m_questions[i].get_answer(j).get_label() << '\t' << m_questions[i].get_answer(j).get_isCorrect() << '\t';
		}

		// Dodanie nowej linii po kazdym pytaniu oprocz ostatniego
		if (i != m_questions.size()-1)
			file << '\n';
	}

	// Informacja o pomyslnym zapisie
	std::cout << "Zapisano postep do pliku." << std::endl;

	// Zamkniecie pliku
	file.close();
	return true;
}

SaveInfo::SaveInfo(std::vector<Question>& question_list,
	int money_left,
	int question_id,
	int round_id,
	bool is_lifeline_available)
	: questions(question_list), 
	moneyLeft(money_left),
	questionId(question_id),
	roundId(round_id),
	isLifelineAvailable(is_lifeline_available)
{
}

SaveInfo SaveState::read_save_state() {
	std::fstream file; // Strumien do odczytu plikow
	bool fileExists = this->get_fileExists(); // Sprawdzenie czy plik istnieje
	file.open(this->get_filename(), std::fstream::in);
	if (!file.is_open()) {};
	file >> m_moneyLeft >> m_questionId >> m_roundId >> m_isLifelineAvailable;
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	m_questions.clear();
	std::string line; // Bufor na wczytana linie

	while (std::getline(file, line)) {
		std::istringstream iss(line); // Strumien do parsowania linii
		std::string field; // Bufor na wczytane pole

		std::string questionText; // Tekst pytania
		std::getline(iss, questionText, '\t');

		std::getline(iss, field, '\t');
		int categoryId = std::stoi(field); // ID kategorii

		Question q; // Obiekt pytania
		q.set_question(questionText);
		q.set_category(static_cast<CATEGORY>(categoryId));

		for (int i = 0; i < ANSWER_AMOUNT; ++i) {
			std::string label; // Podpis odpowiedzi
			std::getline(iss, label, '\t');

			std::string isCorrectStr; // String okreslajacy poprawnosc odpowiedzi
			std::getline(iss, isCorrectStr, '\t');

			bool isCorrect = (isCorrectStr == "1"); // Konwersja na bool
			Answer ans; // Obiekt odpowiedzi
			ans.set_label(label);
			ans.set_isCorrect(isCorrect);
			q.set_answer(i, ans);
		}

		m_questions.push_back(q);
	}

	file.close();
	return SaveInfo(m_questions, m_moneyLeft, m_questionId, m_roundId, m_isLifelineAvailable);
}