#include "menu.h"
#include "input.h"

// Maksymalna liczba opcji w menu glownym
constexpr int MAX_ACCEPTABLE_RANGE = 4;

Menu::Menu(int max_range)
	: m_maxRange(max_range) // IKnicjalizacja maksymalnego zakresu opcji
{
	// Inicjalizacja menu i wczytanie wyboru uzytkownika
	Input user_input; // Obiekt do obslugi wejscia uzytkownika
	m_choice = user_input.number(max_range); // Wczytanie wyboru uzytkownika
	handle_user_input();
}


void Menu::handle_user_input() {
	// Obsluga wyboru uzytkownika w zaleznosci od dostepnych opcji
	switch (m_choice)
	{
	case START:
		m_choice = START; // Wybor rozpoczecia nowej gry
		break;
	case CONTINUE:
		if (m_maxRange == MAX_ACCEPTABLE_RANGE) {
			m_choice = CONTINUE; // Wybor kontynuacji gry
		}
		else
		{
			m_choice = LEADERBOARD; // Przekierowanie do tabeli wynikow
		}
		break;
	case EXIT:
		{
			m_choice = EXIT; // Wyjscie z gry
		}
		break;
	case LEADERBOARD:
		if (m_maxRange == MAX_ACCEPTABLE_RANGE)
		{
			m_choice = LEADERBOARD; // Wybor tabeli wynikow
		}
		else
		{
			m_choice = EXIT; // Przekierowanie do wyjscia
		}
		break;
	default:
		break;
	}
}

int Menu::get_choice() {
	return m_choice;
}