#include "round.h"
#include "style_manager.h"
#include <math.h>
#include "randomizer.h"
#include <iostream>
#include "info.h"
#include "save_state.h"
#include "game.h"

// @brief Stala mowiaca co ile rund ma zmniejszyc sie ilosc zapadek
constexpr int DECREASE_PER = 3;

// @brief Stala mowiaca ile jest wyborow kategorii
constexpr int CATEGORIES_CHOICE = 2;

void Round::start_round() {
	init_round(); // Inicjalizuje runde (wybor kategorii, przygotowanie odpowiedzi)
	run_round(); // Uruchamia glowna petle rundy
}

void Round::start_round(int questionId) {
	m_questionId = questionId;
	init_loaded_round(); // Inicjalizuje runde z wczytanego stanu
	run_round(); // Uruchamia glowna petle rundy
}

void Round::run_round() {
	Info info;
	std::cout << std::endl;
	bool validate = true;
	while (!m_isRoundFinished)
	{
		validate = true;
		show_question(); // Wyswietla pytanie
		show_answers(); // Wyswietla odpowiedzi 
		info.player_status(m_player); // Wyswietla status gracza
		choose_trapdoor(); // Obsluguje wybor zapadki przez gracza
		if (m_currentTrapdoorId == ANSWER_AMOUNT) { // Sprawdza czy gracz uzyl kola ratunkowego
			check_for_lifeline();
			continue;
		}
		if (m_currentTrapdoorId == ANSWER_AMOUNT + 1) { // Sprawdza czy gracz chce wyjsc
			if (check_for_exit()) {
				break;
			}
			else {
				continue;
			}
		}
		if (m_currentTrapdoorId == ANSWER_AMOUNT + 2) { // Sprawdza czy gracz chce wyjsc i zapisac
			if (check_for_save_and_exit()) {
				validate = false;
				break;
			}
			else {
				continue;
			}
		}
		interact_trapdoor(); // Obsluguje interakcje z wybrana zapadka
	}
	if (validate) // Czy trzeba sprawdzic odpowiedzi
	{
		m_isGameRunning = true;
		validate_answers(); // Weryfikuje odpowedzi i aktualizuje stan gry
	}
}

bool Round::check_for_lifeline() {
	StyleManager style;
	if (m_lifeLine.get_isAvailable()) // Sprawdza czy kolo ratunkowe jest dostepne
	{
		int roll = m_lifeLine.call_a_friend(m_questions[m_questionId], m_activeTrapdoors); // Losuje odpowiedz
		std::cout << "Jestem prawie pewny ze to odpowiedz " <<
			style.yellow() <<
			m_activeTrapdoors[roll].get_label() <<
			style.reset() <<
			std::endl <<
			std::endl;
		m_lifeLine.set_isAvailable(false); // Dezaktywuje kolo ratunkowe
		return true;
	}
	
	std::cerr <<
		style.red() <<
		"Juz wykorzystales telefon do przyjaciela w tej grze!" <<
		std::endl <<
		std::endl;
	return false;
}

bool Round::check_for_exit() {
	m_isRoundFinished = finish_round(); // Sprawdza czy runda moze sie skonczyc
	return m_isRoundFinished;
}

bool Round::check_for_save_and_exit() {
	for (auto const& trapdoor : m_activeTrapdoors) // Sprawdza czy w jakiejs zapadce znajduja sie pieniadze
	{
		if (trapdoor.get_moneyPlaced() != 0) {
			StyleManager style;
			std::cout <<
				style.red()
				<< "Nie mozna wyjsc i zapisac gdy na jakiejs zapadce znajduja sie pieniadze."
				<< std::endl
				<< std::endl;
			return false;
		}
	}
	save_and_exit();
	return true;
}

bool Round::save_and_exit() {
	SaveState save(SAVE_FILE_NAME, m_questions, m_moneyAtStart, m_questionId, m_roundId, m_lifeLine.get_isAvailable());
	save.write_to_file(); // Zapisuje informacje podane wyzej do pliku
	m_isGameRunning = false;
	m_wasEarlyExit = true;
	return true;
}

void Round::choose_trapdoor() {
	std::cout << 
		"Wybierz zapadke, z ktora chcesz wejsc w interakcje:" << 
		std::endl;
	int user_choice = m_input.number(1, ANSWER_AMOUNT+3); // Wczytuje wybor gracza
	m_currentTrapdoorId = user_choice-1; // Aktualizuje relatywnie ID wybranej zapadki
	std::cout << std::endl;
}

bool Round::finish_round() const {
	StyleManager style;
	if (m_player.money.get_money() == 0) // Jezeli gracz ma 0 pieniedzy (polozyl wszystkie na zapadkach) konczy runde
		return true;
	std::cerr <<
		style.red() <<
		"Musisz rozlozyc wszystkie dostepne pieniadze!" <<
		std::endl <<
		std::endl;
	return false;
}

void Round::interact_trapdoor() {
	StyleManager style;
	if (!m_activeTrapdoors[m_currentTrapdoorId].get_isAvailable()) { // Sprawdza czy zapadka jest dostepna
		std::cerr <<
			style.red() <<
			"Ta zapadka jest wylaczona." <<
			std::endl <<
			std::endl;
		return;
	}
	// Komunikat o wybranej zapadce
	std::cout << "Wybrana zapadka: " <<
		style.yellow() <<
		"[" <<
		m_currentTrapdoorId+1
		<<
		"] " << 
		style.reset() <<
		style.bold() <<
		m_activeTrapdoors[m_currentTrapdoorId].get_label() <<
		style.reset() <<
		std::endl;
	// Komunikat o opcjach dotyczacych zapadek
	Info i;
	i.trapdoor_status();

	int user_choice = m_input.number(1, 3); // Wybor uzytkownika
	int amount_to_modify = 0; // Kwota do modyfikacji
	switch (user_choice) {
	case 1:
	case 2:
		std::cout <<
			std::endl <<
			"Ilosc pieniedzy na zapadce: " <<
			style.green() <<
			Money::pretty_print(m_activeTrapdoors[m_currentTrapdoorId].get_moneyPlaced()) <<
			std::endl;
		amount_to_modify = read_amount(); // Wczytanie kwoty
		break;
	case 3:
		return; // Powrot do poprzedniego menu
		break;
	}
	switch (user_choice) { // Sprawdzenie czy uzytkownik chce rozlozyc pieniadze na wszystkie zapadki
	case 1:
	{
		int trapdoorsWithMoney = 0;
		int maxTrapdoorsWithMoney = -1;
		for (const auto& trapdoor : m_activeTrapdoors)
		{
			if (trapdoor.get_isAvailable())
				++maxTrapdoorsWithMoney;
			if (trapdoor.get_moneyPlaced() > 0)
				++trapdoorsWithMoney;
		}

		bool isSelectedEmpty = m_activeTrapdoors[m_currentTrapdoorId].get_moneyPlaced() == 0;

		if (isSelectedEmpty && trapdoorsWithMoney >= maxTrapdoorsWithMoney)
		{
			std::cerr <<
				style.red() <<
				"Nie mozesz rozlozyc pieniedzy na wszystkich zapadkach! Jedna musi pozostac pusta." <<
				style.reset() <<
				std::endl << std::endl;
			return;
		}

		m_activeTrapdoors[m_currentTrapdoorId].place_money(m_player, amount_to_modify); // Polozenie pieniedzy
		break;
	}
	case 2:
		m_activeTrapdoors[m_currentTrapdoorId].remove_money(m_player, amount_to_modify); // Zdjecie pieniedzy
		break;
	}
}

int Round::read_amount() {
	Info info;
	info.player_status(m_player); // Wyswietla status gracza (ilosc pieniedzy)
	std::cout <<
		"Wpisz kwote:" <<
		std::endl;
	return m_input.number(1, std::numeric_limits<int>::max()); // Zwraca wpisana kwote
}

void Round::init_round() {
	pick_categories(); // Wybierz kategorie
	populate_answers(); // Zapelnij odpowiedzi
	shuffle_answers(); // Przetasuj odpowiedzi
}

void Round::init_loaded_round() {
	populate_answers(); // Zapelnij odpowiedzi
	shuffle_answers(); // Przetasuj odpowiedzi
}

void Round::show_question() const {
	StyleManager style;
	std::cout <<
		"Pytanie: " <<
		style.bold() <<
		m_questions[m_questionId].get_question() <<
		std::endl <<
		std::endl;
}

void Round::populate_answers() {
	for (int i = 0; i < ANSWER_AMOUNT; ++i) { // Zrob n (ILOSC ODPOWIEDZI) miejsca dla odpowiedzi i zapisz do wektora m_activeTrapdoors
		Trapdoor trapdoor(m_questions[m_questionId].get_answer(i).get_label(),
			m_questions[m_questionId].get_answer(i).get_isCorrect());
		m_activeTrapdoors.push_back(trapdoor);
	}
	for (int i = ANSWER_AMOUNT - 1; i >= m_trapdoorsPerRound; --i) { // Wylacz odpowiednie zapadki
		m_activeTrapdoors[i].set_isAvailable(false);
	}
}

void Round::show_answers() {
	StyleManager style;
	for (int i = 0; i < ANSWER_AMOUNT; ++i)
	{
		if (!m_activeTrapdoors[i].get_isAvailable()) { // Pokaz przekreslona zapadke jesli jest wylaczona
			std::cout <<
				style.gray() <<
				style.strikethrough() <<
				"[" <<
				i + 1 <<
				"] " <<
				m_activeTrapdoors[i].get_label() <<
				" (" <<
				m_activeTrapdoors[i].get_moneyPlaced() <<
				")" <<
				style.reset() <<
				std::endl;
			continue;
		}
		// Wyswietl normalnie jesli zapadka jest wlaczona
		std::cout << 
			style.yellow() <<
			"[" << 
			i+1 <<
			"] " << 
			style.reset() <<
			m_activeTrapdoors[i].get_label() <<
			style.yellow() <<
			" (" <<
			m_activeTrapdoors[i].get_moneyPlaced() <<
			")" <<
			style.reset() <<
			std::endl;
	}
	std::cout << std::endl;
	if (m_lifeLine.get_isAvailable()) { // Sprawdzenie czy jest dostepne kolo ratunkowe
		std::cout << style.yellow() <<
		"[" <<
		(ANSWER_AMOUNT + 1) <<
		"] " <<
		style.reset() <<
		"Telefon do przyjaciela" <<
		std::endl;
	}
	else
	{ // Kolo ratunkowe nie dostepne
		std::cout <<
			style.gray() <<
			style.strikethrough() <<
			"[" <<
			(ANSWER_AMOUNT + 1) <<
			"] " <<
			"Telefon do przyjaciela" <<
			style.reset() <<
			std::endl;
	}
	// Konczenie rundy
	std::cout <<
		style.yellow() <<
		"[" <<
		(ANSWER_AMOUNT + 2) <<
		"] " << 
		style.reset() <<
		"Zakoncz runde" <<
		std::endl;
	// Konczenie gry
	std::cout <<
		style.yellow() <<
		"[" <<
		(ANSWER_AMOUNT + 3) <<
		"] " <<
		style.reset() <<
		"Zakoncz gre (zapisz)" <<
		std::endl <<
		std::endl;
}

void Round::remove_current_question() {
	m_questions.erase(m_questions.begin() + m_questionId); // Usuniecie biezacego pytania
}

int Round::trapdoors_per_round() const {
	// Obliczenie ile zapadek powinno byc aktywnych:
	// ILOSC_ODPOWIEDZI (stala) - zaokraglenie w dol (nr rundy / CO ILE RUND ZMNIEJSZYC (stala))
	return ANSWER_AMOUNT - 
		floor(m_roundId / static_cast<double>(DECREASE_PER));
}

void Round::pick_categories() {
	StyleManager style;
	Random rng;
	int idx1 = rng.randomize_between(0, m_questions.size() - 1); // Losuje pierwszy index (pierwsza kategorie)
	Question q1 = m_questions[idx1];
	CATEGORY f1 = q1.get_category_id();

	std::vector<int> valid_idx; // Wektor ktory zawiera wszystkie pytania ktore nie maja tej samej kategorii co idx1
	for (int i = 0; i < m_questions.size(); ++i) {
		if (i != idx1 && m_questions[i].get_category_id() != f1) {
			valid_idx.push_back(i);
		}
	}

	if (valid_idx.size() == 0) { // Jezeli nie ma pytan o innej kategorii wyswietl blad
		std::cerr << 
			style.red() <<
			"Nie ma pytan ktore roznia sie kategoria." <<
			style.reset() << std::endl;
		m_questionId = idx1;
		return;
	}

	int idx2 = valid_idx[rng.randomize_between(0, valid_idx.size() - 1)]; // Ustawia idx2 na losowy indeks z innej kategorii

	Input user_input{};
	std::cout <<
		"Wybierz jedna z dwoch kategorii: " <<
		std::endl;
	std::cout <<
		style.yellow() <<
		"[1] " <<
		style.reset() <<
		m_questions[idx1].get_category_str() <<
		std::endl;
	std::cout <<
		style.yellow() <<
		"[2] " <<
		style.reset() <<
		m_questions[idx2].get_category_str()
		<< std::endl <<
		std::endl;
	int category_choice = user_input.number(1, 2);
	if (category_choice == 1) {
		m_questionId = idx1;
	}
	else
	{
		m_questionId = idx2;
	}
}

void Round::shuffle_answers() {
	Random rng;
	std::shuffle(m_activeTrapdoors.begin(), m_activeTrapdoors.end(), rng.get_gen()); // Tasuje odpowiedzi by byly w roznej kolejnosci
}

void Round::validate_answers() {
	std::cout <<
		"Poprawna odpowiedz:" <<
		std::endl;
	for (const auto& trapdoor : m_activeTrapdoors)
	{
		if (trapdoor.get_isCorrect()) { // Szuka poprawnej odpowiedzi
			m_player.money.add_money(trapdoor.get_moneyPlaced());
			StyleManager style;
			std::cout <<
				style.bright_green() <<
				trapdoor.get_label() <<
				std::endl <<
				std::endl;
			break;
		}
	}
	StyleManager style;
	int money_lost = m_moneyAtStart - m_player.money.get_money(); // Oblicza stracone pieniadze w tej rundzie
	std::cout <<
		"Stracone pieniadze: " << 
		((money_lost == 0) ? style.bright_green() : style.bright_red()) <<
		money_lost <<
		std::endl <<
		std::endl;
}

Round::~Round() {
	remove_current_question(); // Usuwa aktualne pytanie
}

Round::Round(Player& p, int id,
	std::vector<Question>& questions, bool& isGameRunning, LifeLine& LifeLine, bool& wasEarlyExit)
	: m_player(p),
	m_roundId(id),
	m_trapdoorsPerRound(trapdoors_per_round()),
	m_isRoundFinished(false),
	m_moneyAtStart(p.money.get_money()),
	m_questions(questions),
	m_isGameRunning(isGameRunning),
	m_lifeLine(LifeLine),
	m_wasEarlyExit(wasEarlyExit)
{
	Input user_input{};
	m_input = user_input;
}