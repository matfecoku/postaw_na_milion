#pragma once
#include <string>

// @brief Klasa odpowiedzialna za formatowanie tekstu w konsoli
//
// Klasa odpowiedzialna za:
// - zarzadzanie stylami tekstu w konsoli
// - definiowanie kolorow i formatowania
// - zapewnienie spojnego wygladu interfejsu
// - osluge kodow ANSI do formatowania tekstu
// - resetowanie stylow do domyslnych wartosci
class StyleManager {
public:
    // @brief Destruktor domyslny resetujacy formatowanie
	~StyleManager();

    // @brief Resetuje formatowanie tekstu
    // @return String z kodem resetujacym formatowanie
    std::string reset() const;

    // @brief Ustawia kolor czerwony
    // @return String z kodem czerwonym
    std::string red() const;

    // @brief Ustawia kolor cyjanowy
    // @return String z kodem cyjanowym
    std::string cyan() const;

    // @brief Ustawia kolor zielony
    // @return String z kodem zielonym
    std::string green() const;

    // @brief Ustawia kolor zolty
    // @return String z kodem zoltym
    std::string yellow() const;

    // @brief Ustawia kolor szary
    // @return String z kodem szarym
    std::string gray() const;

    // @brief Ustawia kolor jasno zielony
    // @return String z kodem jasno zielonym
    std::string bright_green() const;

    // @brief Ustawia kolor jasno czerwony
    // @return String z kodem jasno czerwonym
    std::string bright_red() const;

    // @brief Ustawia pogrubenie tekstu
    // @return String z kodem pogrubienia
    std::string bold() const;

    // @brief Ustawia przekreslenie tekstu
    // @return String z kodem przekreslenia
    std::string strikethrough() const;
};