#pragma once
#include <string>

class GameElement {
public:
    // @brief Wirtualny destruktor
    virtual ~GameElement() = default;

    // @brief Sprawdza czy element jest dostepny
    // @return true jesli element jest dostepny
    virtual bool get_isAvailable() const = 0;

    // @brief Ustawia dostepnosc elementu
    // @param isAvailable Nowa wartosc dla dostepnosci
    virtual void set_isAvailable(bool isAvailable) = 0;
protected:
    // @brief Flaga okreslajaca czy element jest dostepny
    bool m_isAvailable = true;
};