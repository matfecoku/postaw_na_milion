#include "answer.h"

Answer::Answer()
	: m_isCorrect(false),
	m_label("") {};

Answer::Answer(bool isCorrect, std::string label)
	: m_isCorrect(isCorrect),
	m_label(label) {};

void Answer::set_label(std::string answer) {
	m_label = answer;
}

void Answer::set_isCorrect(bool isCorrect) {
	m_isCorrect = isCorrect;
}

std::string Answer::get_label() const {
	return m_label;
}

bool Answer::get_isCorrect() const {
	return m_isCorrect;
}