#ifndef MEMORY_TTT_CLASSES_H
#define MEMORY_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <string>

inline Player<char>* create_memory_human(const std::string &name, char symbol) {
    return new Player<char>(name, symbol, PlayerType::HUMAN);
}

inline Player<char>* create_memory_computer(const std::string &name, char symbol) {
    return new Player<char>(name, symbol, PlayerType::COMPUTER);
}

#endif
