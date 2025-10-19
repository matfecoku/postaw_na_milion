#pragma once
#include <string>
#include "player.h"
#include "game_element.h"

// @brief Klasa reprezentujaca zapadke w grze
class Trapdoor : GameElement {
public:
	// @brief Konstruktor zapadki
	// @param label Podpis zapadki
	Trapdoor(std::string label, bool isCorrect);

	// @brief Stawia pieniadze na zapadce
	// @param p Referencja do obiektu gracza
	// @param amount Kwota do postawienia
	// @return true Jesli udalo sie postawic pieniadze
	bool place_money(Player& p, int amount);

	// @brief Zabiera pieniadze z zapadki
	// @param p Referencja do obiektu gracza
	// @param amount Kwota do zabrania
	// @return true Jesli udalo sie zabrac pieniadze
	bool remove_money(Player& p, int amount);

	// @brief Zwraca kwote pieniedzy na zapadce
	// @return Kwota pieniedzy na zapadce
	int get_moneyPlaced() const;

	// @brief Zwraca czy zapadka jest prawidlowa odpowiedzia
	// @return true Jesli zapadka jest prawidlowa odpowiedzia
	bool get_isCorrect() const;

	// @brief Zwraca podpis na zapadce
	// @return Podpis na zapadce
	std::string get_label() const;

	// @brief Zwraca czy zapadka jest dostepna
	// @return true Jesli zapadka jest dostepna
	bool get_isAvailable() const override;

	// @brief Ustawia czy zapadka jest dostepna
	// @param isAvailable Nowy stan dostepnosci
	void set_isAvailable(bool isAvailable) override;
private:
	// @brief Flaga czy odpowiedz jest poprawna
	bool m_isCorrect;

	// @brief Ilosc pieniedzy na zapadce
	int m_moneyPlaced;

	// @brief Podpis zapadki
	std::string m_label;
};