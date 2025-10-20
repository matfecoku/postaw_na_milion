#include "style_manager.h"
#include <iostream>

#define USE_COLORS 1

#if USE_COLORS == 1
std::string StyleManager::reset() const {
    return "\033[0m"; // Kod resetujacy formatowanie tekstu
}

StyleManager::~StyleManager() {
	std::cout << reset(); // Resetowanie formatowania przy zniszczeniu obiektu
}

std::string StyleManager::red() const {
    return "\033[31m"; // Kod koloru czerwonego
}

std::string StyleManager::green() const {
    return "\033[32m"; // Kod koloru zielonego
}

std::string StyleManager::yellow() const {
    return "\033[33m"; // Kod koloru zoltego
}

std::string StyleManager::cyan() const {
    return "\033[36m"; // Kod koloru cyjanowego
}

std::string StyleManager::gray() const {
    return "\033[90m"; // Kod koloru szarego
}

std::string StyleManager::bright_red() const {
    return "\033[91m"; // Kod koloru jasno czerwonego
}

std::string StyleManager::bright_green() const {
    return "\033[92m"; // Kod koloru jasno zielonego
}

std::string StyleManager::bold() const {
    return "\033[1m"; // Kod pogrubienia tekstu
}

std::string StyleManager::strikethrough() const {
    return "\033[9m"; // Kod przekreslenia tekstu
}
#else
std::string StyleManager::reset() const {
    return "";
}

StyleManager::~StyleManager() {
    std::cout << reset();
}

std::string StyleManager::red() const {
    return "";
}

std::string StyleManager::green() const {
    return "";
}

std::string StyleManager::yellow() const {
    return "";
}

std::string StyleManager::cyan() const {
    return "";
}

std::string StyleManager::gray() const {
    return "";
}

std::string StyleManager::bright_red() const {
    return "";
}

std::string StyleManager::bright_green() const {
    return "";
}

std::string StyleManager::bold() const {
    return "";
}

std::string StyleManager::strikethrough() const {
    return "";
}
#endif
