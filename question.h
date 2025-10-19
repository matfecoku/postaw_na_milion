#pragma once
#include <string>
#include <vector>
#include "answer.h"

// @brief Kategorie pytan w grze
enum CATEGORY {OGOLNE,
				KULTURA,
				HISTORIA,
				PRZYRODA,
				SPORT,
				NAUKA,
				TECHNIKA,
				ROZRYWKA,
				UNKNOWN // Nieznana, na wypadek bledu
};

// @brief Stala okreslajaca liczbe mozliwych odpowiedzi na pytanie
constexpr int ANSWER_AMOUNT = 4;

// @class Question
// @brief Klasa reprezentujaca pytanie w grze
//
// Klasa odpowiedzialna za:
// - przechowywanie tresci pytania
// - zarzadzanie odpowiedziami
// - okreslanie kategorii pytania
class Question {
public:
	// @brief Konstruktor domyslny
	Question();

	// @brief Ustawia tresc pytania
	// @param question Tresc pytania
	void set_question(std::string question);

	// @brief Zwraca tresc pytania
	// @return Tresc pytania
	std::string get_question() const;

	// @brief Zwraca ID kategorii
	// @return ID kategorii
	CATEGORY get_category_id() const;

	// @brief Zwraca nazwe kategorii jako string
	// @return Nazwa kategorii jako string
	std::string get_category_str() const;

	// @brief Ustawia odpowiedz o podanym indeksie
	// @param id Indeks odpowiedzi
	// @param answer Obiekt odpowiedzi
	void set_answer(int id, Answer answer);

	// @brief Zwraca odpowiedz o podanym indeksie
	// @param id Indeks odpowiedzi
	// @return Obiekt odpowiedzi
	Answer get_answer(int id) const;

	// @brief Zwraca liczbe mozliwych odpowiedzi
	// @return Liczba odpowiedzi
	int get_answerAmount() const;

	// @brief Ustawia kategorie pytania
	// @return cat Kategoria do ustawienia
	void set_category(CATEGORY cat);

	// @brief Konwertuje string na kategorie
	// @param string Nazwa kategorii
	// @return Odpowiadajaca wartosc enum CATEGORY
	CATEGORY string_to_category(std::string string) const;

	// @brief Konwertuje kategorie na string
	// @param cat Kategoria do konwersji
	// @return Nazwa kategorii jako string
	std::string category_to_string(CATEGORY cat) const;
private:
	// @brief Tresc pytania
	std::string m_question;

	// @brief Kategoria pytania
	CATEGORY m_category;

	// @brief Tablica mozliwych odpowiedzi
	Answer m_answer[ANSWER_AMOUNT];
};