#include <iostream>
#include "game.h"
#include "info.h"
#include "load.h"
#include "menu.h"
#include "save.h"
#include "leaderboard.h"
#include "gameshow.h"
#include "input.h"
#include "question.h"
#include <vector>
#include "style_manager.h"

Game::Game()
{
	// Inicjalizacja gry i wyswietlenie powitania
	StyleManager style; // Obiekt do formatowania tekstu
	std::cout << style.reset();
	std::cout << "Witaj w Postaw na Milion!" << std::endl;
}

void Game::init() {
	// Uruchomienie glownego menu gry
	main_menu();
}

Game::~Game() {
	// Zamkniecie gry przy zniszczeniu obiektu
	close_game();
}

void Game::close_game() {
	// Wyswietlenie komunikatu koncowego i zakonczenie programu
	std::cout << std::endl << "Zakonczono program." << std::endl;
	exit(0);
}

void Game::start_game(SaveInfo& saveInfo) {
	// Rozpoczecie gry z wczytanego stanu
	std::cout << "Zaladowano rozgrywke." << std::endl;
	GameShow game; // Obiekt zarzadzajacy rozgrywka
	Player p(saveInfo.moneyLeft); // Utworzenie gracza z wczytana kwota
	bool safeQuit = game.begin_gameshow(saveInfo.questions,
		p,
		saveInfo.roundId,
		ROUNDS,
		saveInfo.questionId,
		saveInfo.isLifelineAvailable);
	if (safeQuit && !game.get_wasEarlyExit())
		save_to_leaderboard(p);
}

void Game::start_game() {
	// Rozpoczecie nowej gry
	std::cout << "Zaczeto rozgrywke." << std::endl;
	GameShow game; // Obiekt zarzadzajacy rozgrywka
	Player p(START_AMOUNT); // Utworzenie gracza z poczatkowa kwota
	bool safeQuit = game.begin_gameshow(QUESTIONS_FILE_NAME,
		p,
		ROUNDS);
	if (safeQuit && !game.get_wasEarlyExit())
		save_to_leaderboard(p);
}

void Game::load_game() {
	// Wczytanie zapisanej gry
	std::vector<Question> questions; // Wektor do przechowywania pytan
	SaveState loader(SAVE_FILE_NAME, questions); // Obiekt do wczytywania stanu gry
	SaveInfo si = loader.read_save_state();
	start_game(si);
}

void Game::save_to_leaderboard(Player& p) {
	// Zapisanie wyniku gracza do tabeli wynikow
	FileManager f(SAVE_FILE_NAME);
	f.remove_file(); // Usuwanie pliku z zapisem by nie mozna bylo wczytac przegranej gry
	std::string username; // Nazwa uzytkownika
	std::cout << "Podaj swoja nazwe uzytkownika (maks. " <<
		MAX_PLAYER_NAME_LENGTH <<
		" znakow): " << std::endl;
	Input in; // Obiekt do obslugi wejscia uzytkownika
	username = in.string(MAX_PLAYER_NAME_LENGTH);
	Leaderboard leaderboard(LEADERBOARD_FILE_NAME, username, p.money.get_money()); // Obiekt tabeli wynikow
	leaderboard.write_to_file();
}

void Game::show_leaderboard() {
	// Wyswietlenie tabeli wynikow
	Leaderboard leaderboard(LEADERBOARD_FILE_NAME); // Obiekt tabeli wynikow
	leaderboard.show_leaderboard();
}

void Game::main_menu() {
	// Obsluga glownego menu gry
	Info main_menu_info;
	while (true) {
		LoadFile loadSaveFile(SAVE_FILE_NAME); // Obiekt do sprawdzania istnienia pliku zapisu
		main_menu_info.main_menu(loadSaveFile.get_fileExists()); // Obiekt informacji o menu
		Menu menu(main_menu_info.get_maxRange()); // Obiekt menu
		std::cout << std::endl;
		switch (menu.get_choice()) {
			case START:
			{
				start_game(); // Zacznij gre
				break;
			}
			case CONTINUE:
				load_game(); // Wczytaj gre
				break;
			case EXIT:
				close_game(); // Zamknij gre
				break;
			case LEADERBOARD:
			{
				show_leaderboard(); // Pokaz tabele wynikow
				break;
			}
			default:
				std::cout << std::endl;
				break;
		}
		std::cout << std::endl;
	}
}