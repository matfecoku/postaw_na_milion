#include "lifeline.h"
#include "randomizer.h"

#include <iostream>

bool LifeLine::get_isAvailable() const {
	return m_isAvailable;
}

void LifeLine::set_isAvailable(bool isAvailable) {
	m_isAvailable = isAvailable;
}

int LifeLine::call_a_friend(Question& question, std::vector<Trapdoor>& trapdoors) const {
	// Symulacja telefonu do przyjaciela w odpowiedzi na pytanie

	Random rng; // Generator liczb losowych
	int roll = rng.randomize_between(1, 10); // Liczba losowa od 1 do 10
	int correctIdx = -1; // Indeks poprawnej odpowiedzi
	int idx_roll = -1; // Indeks wybranej odpowiedzi

	// Znalezienie poprawnej odpowiedzi
	for (int i = 0; i < question.get_answerAmount(); ++i)
	{
		if (trapdoors[i].get_isCorrect()) {
			correctIdx = i;
			break;
		}
	}

	// 30% szans na bledna odpowiedz
	// 70% na poprawna
	if (roll < 4)
	{
		// Wybor losowej blednej odpowiedzi
		std::vector<int> valid_idxs;

		for (int i = 0; i < question.get_answerAmount(); ++i) {
			if (i != correctIdx && trapdoors[i].get_isAvailable()) {
				valid_idxs.push_back(i);
			}
		}

		if (!valid_idxs.empty()) {
			idx_roll = valid_idxs[rng.randomize_between(0, valid_idxs.size() - 1)]; // Wybor losowej blednej odpowiedzi
		}

		if (idx_roll == -1 && trapdoors[correctIdx].get_isAvailable()) {
			idx_roll = correctIdx; // Wybor poprawnej odpowiedzi
		}
		
	}
	else
	{
		idx_roll = correctIdx;
	}
	return idx_roll;
}