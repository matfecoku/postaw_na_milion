#include "randomizer.h"

Random::Random() : m_gen(m_rd()) {} // Inicjalizacja generatora liczb losowych

int Random::randomize_between(int min, int max) {
	std::uniform_int_distribution<> dis(min, max); // Rozklad w zakresie [min, max]
	return dis(m_gen);
}

std::mt19937 Random::get_gen() const {
	return m_gen; // Zwrocenie generatora liczb losowych
}