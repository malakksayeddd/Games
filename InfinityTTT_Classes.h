/**
 * @file InfinityTTT_Classes.h
 * @brief Defines the Infinity Tic-Tac-Toe game classes.
 *
 * This file provides:
 * - `Infinity_Board`: A 3x3 board where only the last 3 moves per player remain.
 * - `Infinity_UI`: User interface for the Infinity Tic-Tac-Toe game.
 *
 * In this variant, each player can only have 3 marks on the board at a time.
 * When placing a 4th mark, the oldest mark is automatically removed.
 */

#pragma once
#ifndef INFINITY_TTT_CLASSES_H
#define INFINITY_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <queue>
#include <utility>

/// @brief Character representing an empty cell on the board.
const char blanksymbol = '_';

/**
 * @class Infinity_Board
 * @brief Represents the Infinity Tic-Tac-Toe game board.
 *
 * Each player maintains a history of their last 3 moves. When a 4th move
 * is made, the oldest move is automatically removed from the board.
 *
 * @see Board
 */
class Infinity_Board : public Board<char> {
private:
    std::queue<std::pair<int, int>> historyX; ///< Move history for player X.
    std::queue<std::pair<int, int>> historyO; ///< Move history for player O.

public:
    /**
     * @brief Constructs a 3x3 Infinity board.
     */
    Infinity_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the move containing coordinates and symbol.
     * @return true if the move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the player has won (3 in a row).
     * @param player Pointer to the player to check.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the player has lost.
     * @param player Pointer to the player to check.
     * @return Always returns false (no lose condition in this variant).
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Checks if the game is a draw.
     * @param player Pointer to the player to check.
     * @return Always returns false (no draw in this variant).
     */
    bool is_draw(Player<char>* player) override { return false; }

    /**
     * @brief Checks if the game is over.
     * @param player Pointer to the player to evaluate.
     * @return true if any player has won, false otherwise.
     */
    bool game_is_over(Player<char>* player);

    /**
     * @brief Checks if a symbol has 3 in a row.
     * @param s The symbol to check ('X' or 'O').
     * @return true if 3 in a row exists, false otherwise.
     */
    bool is_win_symbol(char s);

    /**
     * @brief Processes player history and removes oldest move if needed.
     * @param s The player's symbol.
     */
    void process_player_history(char s);
};

/**
 * @class Infinity_UI
 * @brief User Interface class for the Infinity Tic-Tac-Toe game.
 *
 * Handles player interaction for the Infinity variant.
 *
 * @see UI
 */
class Infinity_UI : public UI<char> {
public:
    /**
     * @brief Constructs the Infinity Tic-Tac-Toe UI.
     */
    Infinity_UI();

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol The player's symbol.
     * @param type The type of player (Human or Computer).
     * @return Pointer to the created Player object.
     */
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move from the player.
     * @param player Pointer to the current player.
     * @return Pointer to the Move object.
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif
