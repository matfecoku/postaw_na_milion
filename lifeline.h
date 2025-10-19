#pragma once
#include "game_element.h"
#include "question.h"
#include "trapdoor.h"
#include <vector>

// @class LifeLine
// @brief Klasa reprezentujaca kolo ratunkowe - telefon do przyjaciela
//
// Klasa odpowiedzialna za:
// - zarzadzanie dostepnoscia kola ratunkowego
// - symulacje pomocy przyjaciela przy odpowiedzi na pytanie
class LifeLine : GameElement {
public:
    // @brief Sprawdza czy kolo ratunkowe jest dostepne
    // @return true Jesli kolo ratunkowe jest dostepne
    virtual bool get_isAvailable() const override;

    // @brief Ustawia dostepnosc kola ratunkowego
    // @param isAvailable Nowy stan dostepnosci
    virtual void set_isAvailable(bool isAvailable) override;

    // @brief Symuluje pomoc przyjaciela w odpowiedzi na pytanie
    // @param question Pytanie na ktore przyjaciel ma odpowiedziec
    // @return Indeks wybranej odpowiedzi (0-3)
    int call_a_friend(Question& question, std::vector<Trapdoor>& trapdoors) const;
};