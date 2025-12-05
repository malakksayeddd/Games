/**
 * @file MemoryTTT_UI.h
 * @brief Defines the User Interface for Memory Tic-Tac-Toe.
 *
 * Provides the UI functionality for the Memory variant where
 * the board state is hidden from players.
 */

#ifndef MEMORY_TTT_UI_H
#define MEMORY_TTT_UI_H

#include "BoardGame_Classes.h"
#include "MemoryTTT_Board.h"

/**
 * @class MemoryTTT_UI
 * @brief User Interface class for the Memory Tic-Tac-Toe game.
 *
 * Handles player interaction with hidden board display.
 * Players must remember where pieces are placed.
 *
 * @see UI
 */
class MemoryTTT_UI : public UI<char> {
public:
    /**
     * @brief Constructs the Memory Tic-Tac-Toe UI.
     */
    MemoryTTT_UI();

    /**
     * @brief Virtual destructor.
     */
    virtual ~MemoryTTT_UI() = default;

    /**
     * @brief Gets a move from the player.
     * @param player Pointer to the current player.
     * @return Pointer to the Move object.
     */
    virtual Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Sets up both players for the game.
     * @return Array of two Player pointers.
     */
    virtual Player<char>** setup_players() override;

    /**
     * @brief Displays the board matrix with cells hidden.
     * 
     * Overrides the default display to show a hidden board.
     * 
     * @param matrix The board matrix (values are hidden from display).
     */
    virtual void display_board_matrix(const vector<vector<char>>& matrix) const override;

};

#endif
