#pragma once
#include <string>

// @class Answer
// @brief Klasa reprezentujaca odpowiedz na pytanie
//
// Klasa przechowuje:
// - tresc odpowiedzi
// - informacje czy odpowiedz jest poprawna
class Answer {
public:
	// @brief Konstruktor domyslny
	Answer();

	// @brief Konstruktor z parametrami
	// @param isCorrect Czy odpowiedz jest poprawna
	// @param label Tresc odpowiedzi
	Answer(bool isCorrect, std::string label);

	// @brief Ustawia tresc odpowiedzi
	// @param answer Nowa tresc odpowiedzi
	void set_label(std::string answer);

	// @brief Ustawia flage poprawnosci odpowiedzi
	// @param isCorrect Czy odpowiedz jest poprawna
	void set_isCorrect(bool isCorrect);

	// @brief Zwraca tresc odpowiedzi
	// @return Tresc odpowiedzi
	std::string get_label() const;

	// @brief Sprawdza czy odpowiedz jest poprawna
	// @return true jesli odpowiedz jest poprawna
	bool get_isCorrect() const;
private:
	// @brief Tresc odpowiedzi
	std::string m_label;

	// @brief Flaga okreslajaca czy odpowiedz jest poprawna
	bool m_isCorrect;
};