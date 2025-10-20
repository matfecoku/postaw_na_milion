#include "question.h"
#include <unordered_map>
#include <iostream>

// Mapowanie nazw kategorii na ich identyfikatory
const std::unordered_map<std::string, CATEGORY> stringToCategory = {
		{"OGOLNE", CATEGORY::OGOLNE},
		{"KULTURA", CATEGORY::KULTURA},
		{"HISTORIA", CATEGORY::HISTORIA},
		{"PRZYRODA", CATEGORY::PRZYRODA},
		{"SPORT", CATEGORY::SPORT},
		{"NAUKA", CATEGORY::NAUKA},
		{"TECHNIKA", CATEGORY::TECHNIKA},
		{"ROZRYWKA", CATEGORY::ROZRYWKA}
};

void Question::set_question(std::string question) {
	m_question = question;
}

std::string Question::get_question() const {
	return m_question;
}

void Question::set_answer(int id, Answer answer) {
	// Sprawdza czy indeks sie zgadza
	if (id < 0 || id > ANSWER_AMOUNT) return;
	m_answer[id] = answer;
}

Answer Question::get_answer(int id) const {
	// Sprawdza czy indeks sie zgadza
	if (id < 0 || id > ANSWER_AMOUNT) return m_answer[0];
	return m_answer[id];
}

int Question::get_answerAmount() const {
	return ANSWER_AMOUNT;
}

void Question::set_category(CATEGORY cat) {
	m_category = cat;
}

CATEGORY Question::string_to_category(std::string string) const {
	auto it = stringToCategory.find(string); // Wyszukanie kategorii w mapie
	return (it != stringToCategory.end()) ? it->second : CATEGORY::UNKNOWN; // Ustawienie na odpowiednia kategorie lub na UNKNOWN
}

std::string Question::category_to_string(CATEGORY cat) const {
	CATEGORY category = static_cast<CATEGORY>(cat);
	for (const auto& p : stringToCategory) { // Wyszukanie pary
		if (p.second == category)
		{
			return p.first;
		}
	}
	return "UNKNOWN";
}

CATEGORY Question::get_category_id() const {
	return m_category;
}

std::string Question::get_category_str() const {
	return category_to_string(m_category);
}

Question::Question()
	: m_question(),
	m_category(),
	m_answer() 
{

}