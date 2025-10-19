#pragma once
#include "player.h"
#include "question.h"
#include "trapdoor.h"
#include "input.h"
#include "lifeline.h"

// @brief Klasa reprezentujaca runde w grze
//
// Klasa odpowiedzialna za:
// - zarzadzanie pojedyncza runda gry
// - obsluge pytan i odpowiedzi w rundzie
// - zarzadzanie zapadkami i stawianiem pieniedzy
// - obsluge interakcji gracza z zapadkami
// - weryfikacje odpowiedzi i aktualizacje stanu gry
// - obsluge kol ratunkowych i zapisu
class Round {
public:
	// @brief Konstruktor rundy
	// @param p Referencja do obiektu gracza
	// @param id ID rundy
	// @param questions Referencja do wektora pytan
	// @param isGameRunning Referencja do flagi aktywnosci gry
	// @param LifeLine Referencja do obiektu kola ratunkowego
	// @param wasEarlyExit Referencja do m_wasEarlyExit
	Round(Player& p, int id,
		std::vector<Question>& questions, bool& isGameRunning, LifeLine& LifeLine, bool& wasEarlyExit);

	// @brief Destruktor rundy
	~Round();

	// @brief Rozpoczyna runde z okreslonym pytaniem
	// @param questionId ID pytania do wyswietlenia
	void start_round(int questionId);

	// @brief Rozpoczyna nowa runde
	void start_round();
private:
	// @brief Oblicza liczbe zapadek w rundzie
	// @return Liczba zapadek w rundzie
	int trapdoors_per_round() const;

	// @brief Inicjalizuje nowa runde
	void init_round();

	// @brief Wyswietla aktualne pytanie
	void show_question() const;

	// @brief Wyswietla dostepne odpowiedzi
	void show_answers();

	// @brief Wypelnia wektor odpowiedziami
	void populate_answers();

	// @brief Usuwa aktualne pytanie z puli
	void remove_current_question();

	// @brief Obsluguje wybor zapadki przez gracza
	void choose_trapdoor();

	// @brief Wybiera kategorie pytan
	void pick_categories();

	// @brief Obsluguje interakcje z wybrana zapadka
	void interact_trapdoor();

	// @brief Wczytuje kwote od gracza
	// @return Wczytana kwota
	int read_amount();

	// @brief Sprawdza czy runda moze sie zakonczyc
	// @return true Jesli runda moze sie zakonczyc
	bool finish_round() const;

	// @brief Miesza kolejnosc odpowiedzi
	void shuffle_answers();

	// @brief Weryfikuje odpowiedzi i aktualizuje stan gry
	void validate_answers();

	// @brief Sprawdza czy gracz chce zakonczyc gre
	// @return true Jesli gracz chce zakonczyc
	bool check_for_exit();

	// @brief Zapisuje stan gry i konczy gre
	// @param true Jesli zapis sie powiodl
	bool save_and_exit();

	// @brief Sprawdza czy gracz chce zapisac i zakonczyc gre
	// @return true Jesli gracz chce zapisac i zakonczyc gre
	bool check_for_save_and_exit();

	// @brief Sprawdza czy gracz chce uzyc kola ratunkowego
	// @return true Jesli kolo ratunkowe zostalo uzyte
	bool check_for_lifeline();

	// @brief ID aktualnej rundy
	const int m_roundId;

	// @brief Liczba zapadek w rundzie
	int m_trapdoorsPerRound;

	// @brief ID aktualnego pytania
	int m_questionId;

	// @brief ID aktualnie wybranej zapadki
	int m_currentTrapdoorId;

	// @brief Flaga okreslajaca czy runda jest zakonczona
	bool m_isRoundFinished;

	// @brief Kwota pieniedzy na poczatku rundy
	int m_moneyAtStart;

	// @brief Uruchamia glowna petle rundy
	void run_round();

	// @brief Inicjalizuje runde z wczytanego stanu
	void init_loaded_round();

	// @brief Referencja do obiektu gracza
	Player& m_player;

	// @brief Obiekt do obslugi wejscia uzytkownika
	Input m_input;

	// @brief Wektor aktywnych zapadek w rundzie
	std::vector<Trapdoor> m_activeTrapdoors;

	// @brief Referencja do wektora pytan
	std::vector<Question>& m_questions;

	// @brief Referencja do flagi okreslajacej czy gra jest w toku
	bool& m_isGameRunning;

	// @brief Referencja do obiektu kola ratunkowego
	LifeLine& m_lifeLine;

	// @brief Referencja do flagi okreslajacej czy gra zostala zakonczona przedwczesnie
	bool& m_wasEarlyExit;
};