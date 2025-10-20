#pragma once
#include "question.h"
#include "player.h"
#include "lifeline.h"
#include <vector>

// @class GameShow
// @brief Klasa zarzadzajaca przebiegiem gry
//
// Klasa odpowiedzialna za:
// - inicjalizacje i prowadzenie rozgrywki
// - zarzadzanie rundami gry
// - obsluge pytan i odpowiedzi
// - interakcje z graczem
class GameShow {
public:
	// @brief Podstawowy konstruktor
	GameShow();

	// @brief Rozpoczyna nowa rozgrywke
	// @param questions_filename Nazwa pliku z pytaniami
	// @param player Referencja do obiektu gracza
	// @param rounds Liczba rund do rozegrania
	// @return true Jesli rozgrywka sie powiodla
	bool begin_gameshow(std::string questions_filename, Player& player, int rounds);

	// @brief Rozpoczyna rozgrywke z wczytanego stanu
	// @param questions Wektor pytan
	// @param player Referencja do obiektu gracza
	// @param rounds Calkowita liczba rund
	// @param rounds_left Pozostala liczba rund
	// @param question_id ID aktualnego pytania
	// @param isLifelineAvailable Dostepnosc kola ratunkowego
	// @return true Jesli rozgrywka sie powiodla
	bool begin_gameshow(std::vector<Question>& questions, 
		Player& player, 
		int rounds, 
		int rounds_left, 
		int question_id, 
		bool isLifelineAvailable);

	// @brief Getter do m_wasEarlyExit
	bool get_wasEarlyExit() const;

	// @brief Setter do m_wasEarlyExit
	// @param bool early_exit
	void set_wasEarlyExit(bool early_exit);
private:

	// @brief Inicjalizuje pytania z pliku
	// @param questions_filename Nazwa pliku z pytaniami
	// @return true Jesli incijalizacja sie powiodla
	bool init_questions(std::string questions_filename);

	// @brief Rozpoczyna nowa runde
	// @param player Referencja do obiektu gracza
	// @param id ID rundy
	// @param ll Referencja do obiektu kola ratunkowego
	// @param wasEarlyExit Referencja do m_wasEarlyExit
	void start_round(Player& player, int id, LifeLine& ll);

	// @brief Rozpoczyna runde z okreslonym pytaniem
	// @param player Referencja do obiektu gracza
	// @param id ID rundy
	// @param questionId ID pytania
	// @param ll Referencja do obiektu kola ratunkwoego
	// @param wasEarlyExit Referencja do m_wasEarlyExit
	void start_round(Player& player, int id, int questionId, LifeLine& ll);

	// @brief Wektor przechowujacy pytania do gry
	std::vector<Question> m_questions;

	// @brief Flaga okreslajaca czy gra jest aktywna
	bool m_isGameRunning;

	// @brief Flaga okreslajaca czy gra zostala zakonczona przedwczesnie
	bool m_wasEarlyExit;
};