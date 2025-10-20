#pragma once
#include "save.h"
#include "question.h"
#include <string>
#include <vector>

// @struct SaveInfo
// @brief Struktura przechowujaca informacje o zapisanym stanie gry
//
// Struktura zawiera wszystkie niezbedne informacje do przywrocenia stanu gry:
// - liste pytan
// - pozostala kwote pieniedzy
// - aktualne pytanie i runde
// - stan kola ratunkwoego
struct SaveInfo {
	// @brief Konstruktor struktury
	// @param questions Referencja do wektora pytan
	// @param moneyLeft Pozostala kwota pieniedzy
	// @param questionId ID aktualnego pytania
	// @param roundId ID aktualnej rundy
	// @param isLifelineAvailable Dostepnosc kola ratunkowego
	SaveInfo(std::vector<Question>&, 
		int moneyLeft, 
		int questionId, 
		int roundId,
		bool isLifelineAvailable);
	std::vector<Question>& questions; // Lista pytan w grze
	int moneyLeft; // Pozostala kwota pieniedzy
	int questionId; // ID aktualnego pytania
	int roundId; // ID aktualnej rundy
	bool isLifelineAvailable; // Dostepnosc kola ratunkowego
};

// @class SaveState
// @brief Klasa zarzadzajaca zapisem i odczytem stanu gry
//
// Klasa odpowiedzialna za:
// - zapisywanie aktualnego stanu gry do pliku
// - wczytywanie zapisanego stanu gry
// - przechowywanie informacji o stanie gry
class SaveState : SaveFile {
public:
	// @brief Konstruktor z pelnymi parametrami
	// @param filename Nazwa pliku zapisu
	// @param questions Referencja do wektora pytan
	// @param money_left Pozostala kwota pieniedzy
	// @param question_id ID aktualnej rundy
	// @param round_id ID aktualnej rundy
	// @param is_lifeline_available Dostepnosc kola ratunkowego
	SaveState(const std::string filename, 
		std::vector<Question>& questions, 
		int money_left,
		int question_id,
		int round_id,
		bool is_lifeline_available);

	// @brief Konstruktor z podstawowymi parametrami
	// @param filename Nazwa pliku zapisu
	// @param question s Referencja do wektora pytan
	SaveState(const std::string filename,
		std::vector<Question>& questions);

	// @brief Zapisuje stan gry do pliku
	// @return true Jesli zapis sie powiodl
	bool write_to_file() override;;

	// @brief Wczytuje stan gry z pliku
	// @return true Jesli zapis sie powiodl
	SaveInfo read_save_state();
private:
	std::vector<Question>& m_questions; // Referencja do wektora pytan
	int m_moneyLeft; // Pozostala kwota pieniedzy
	int m_questionId; // ID aktualnego pytania
	int m_roundId; // ID aktualnej rundy
	bool m_isLifelineAvailable; // Dostepnosc kola ratunkowego
};