#include "gameshow.h"
#include "round.h"
#include "load.h"
#include "info.h"
#include <iostream>

bool GameShow::begin_gameshow(std::string questions_filename,
	Player& player,
	int rounds) {

	// Rozpoczecie nowej rozgrywki
	m_isGameRunning = true;
	LifeLine ll; // Obiekt kola ratunkowego
	init_questions(questions_filename);
	for (int i = 1; i <= rounds; ++i)
	{
		if (!m_isGameRunning) {
			return false;
		};
		Info info;
		info.round_status(i);
		start_round(player, i, ll);
		if (player.money.get_money() == 0)
			break;
	}
	return true;
}

bool GameShow::begin_gameshow(std::vector<Question>& questions,
	Player& player,
	int round_id,
	int rounds_left,
	int questionId,
	bool isLifelineAvailable) {
	// Rozpoczecie rozgrywki z wczytanego stanu
	m_isGameRunning = true;
	m_questions = questions;
	LifeLine ll; // Obiekt kola ratunkowego
	ll.set_isAvailable(isLifelineAvailable);
	if (!m_isGameRunning) return false;
	Info info;
	info.round_status(round_id);
	start_round(player, round_id, questionId, ll);
	if (player.money.get_money() == 0)
		return true;
	for (int i = round_id+1; i <= rounds_left; ++i) // Petla uruchamiajaca kolejne rundy
	{
		if (!m_isGameRunning) {
			return false;
		};
		Info info;
		info.round_status(i);
		start_round(player, i, ll);
		if (player.money.get_money() == 0)
			break;
	}
	return true;
}

void GameShow::start_round(Player& player, int id, LifeLine& ll) {
	// Rozpoczecie nowej rundy
	Round round(player, id, m_questions, m_isGameRunning, ll, m_wasEarlyExit);
	round.start_round();
}

void GameShow::start_round(Player& player, int id, int questionId, LifeLine& ll) {
	// Rozpoczecie nowej rundy z okreslonym pytaniem
	Round round(player, id, m_questions, m_isGameRunning, ll, m_wasEarlyExit);
	round.start_round(questionId);
}

bool GameShow::init_questions(std::string questions_filename) {
	// Inicjalizacja pytan z pliku
	LoadFile load(questions_filename); // Obiekt do wczytywania pytan
	if (!load.load_questions(m_questions))
	{
		std::cerr << "Nie mozna zaladowac pytan.";
		return false;
	}
	return true;
}

bool GameShow::get_wasEarlyExit() const {
	return m_wasEarlyExit;
}

void GameShow::set_wasEarlyExit(bool early_exit) {
	m_wasEarlyExit = early_exit;
}

GameShow::GameShow() : m_wasEarlyExit(false) {}