/**
 * @file MemoryTTT_Classes.h
 * @brief Helper functions for creating Memory Tic-Tac-Toe players.
 *
 * Provides factory functions for creating human and computer players
 * for the Memory Tic-Tac-Toe variant.
 */

#ifndef MEMORY_TTT_CLASSES_H
#define MEMORY_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <string>

/**
 * @brief Creates a human player for Memory Tic-Tac-Toe.
 * @param name The player's name.
 * @param symbol The player's symbol ('X' or 'O').
 * @return Pointer to the created Player object.
 */
inline Player<char>* create_memory_human(const std::string &name, char symbol) {
    return new Player<char>(name, symbol, PlayerType::HUMAN);
}

/**
 * @brief Creates a computer player for Memory Tic-Tac-Toe.
 * @param name The player's name.
 * @param symbol The player's symbol ('X' or 'O').
 * @return Pointer to the created Player object.
 */
inline Player<char>* create_memory_computer(const std::string &name, char symbol) {
    return new Player<char>(name, symbol, PlayerType::COMPUTER);
}

#endif
