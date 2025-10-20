#include <random>

// @brief Klasa odpowiedzialna za generowanie liczb losowych
class Random {
public:
	// @brief Konstruktor klasy losujacej
	Random();

	// @brief Generuje losowa liczbe z podanego zakresu
	// @param min Minimalna wartosc
	// @param max Maksymalna wartosc
	// @return Losowa liczba z zakresu [min, max]
	int randomize_between(int min, int max);

	// @brief Zwraca generator liczb losowych
	// @return Generator liczb losowych
	std::mt19937 get_gen() const;
private:

	// @brief Generator liczb losowych
	std::random_device m_rd;

	// @brief Silnik generowania liczb losowych
	std::mt19937 m_gen;
};