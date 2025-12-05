/**
 * @file NumericalTTT_Classes.h
 * @brief Defines the Numerical Tic-Tac-Toe game classes.
 *
 * In this variant, players use numbers instead of X and O:
 * - Player 1 uses odd numbers (1, 3, 5, 7, 9)
 * - Player 2 uses even numbers (2, 4, 6, 8)
 * 
 * The goal is to make a line (row, column, or diagonal) that sums to 15.
 */

#pragma once
#ifndef NUMERICAL_TTT_CLASSES_H
#define NUMERICAL_TTT_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Numerical_Board
 * @brief Represents the Numerical Tic-Tac-Toe game board.
 *
 * A 3x3 board where players place numbers. The winner is the first
 * to create a line summing to exactly 15.
 *
 * @see Board
 */
class Numerical_Board : public Board<int> {
private:
    int blank_symbol = 0; ///< Value representing an empty cell.

public:
    /**
     * @brief Constructs a 3x3 Numerical board.
     */
    Numerical_Board();

    /**
     * @brief Checks if the player has lost.
     * @param Unused parameter.
     * @return Always returns false.
     */
    bool is_lose(Player<int>*) { return false; }

    /**
     * @brief Checks if the game is a draw.
     * @param player Pointer to the player to check.
     * @return true if board is full with no winner, false otherwise.
     */
    bool is_draw(Player<int>* player);

    /**
     * @brief Checks if the game is over.
     * @param player Pointer to the player to evaluate.
     * @return true if game has ended (win or draw), false otherwise.
     */
    bool game_is_over(Player<int>* player);

    /**
     * @brief Places a number on the board.
     * @param move Pointer to the move containing coordinates and number.
     * @return true if the move is valid, false otherwise.
     */
    bool update_board(Move<int>* move);

    /**
     * @brief Checks if any line sums to 15.
     * @param player Pointer to the player to check.
     * @return true if a winning line exists, false otherwise.
     */
    bool is_win(Player<int>* player);
};

/**
 * @class Numerical_UI
 * @brief User Interface class for the Numerical Tic-Tac-Toe game.
 *
 * Handles player interaction and number selection validation.
 *
 * @see UI
 */
class Numerical_UI : public UI<int> {
public:
    /**
     * @brief Constructs the Numerical Tic-Tac-Toe UI.
     */
    Numerical_UI();

    /**
     * @brief Destructor for Numerical_UI.
     */
    ~Numerical_UI() {}

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol The player's identifier (odd or even indicator).
     * @param type The type of player (Human or Computer).
     * @return Pointer to the created Player object.
     */
    Player<int>* create_player(string& name, int symbol, PlayerType type);

    /**
     * @brief Gets a move from the player (position and number).
     * @param player Pointer to the current player.
     * @return Pointer to the Move object.
     */
    virtual Move<int>* get_move(Player<int>* player);
};

#endif 
