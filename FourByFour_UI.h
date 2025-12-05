/**
 * @file FourByFour_UI.h
 * @brief Defines the User Interface for 4x4 Tic-Tac-Toe.
 *
 * Provides user interaction functionality for the 4x4 variant
 * where players move pieces instead of placing them.
 */

#ifndef FOURBYFOUR_UI_H
#define FOURBYFOUR_UI_H

#include "../BoardGame_Classes.h"

/**
 * @class FourByFour_UI
 * @brief User Interface class for the 4x4 Tic-Tac-Toe game.
 *
 * Handles player input for piece movement and integrates with the AI
 * for computer-controlled players.
 *
 * @see UI
 */
class FourByFour_UI : public UI<char> {
public:
    /**
     * @brief Constructs the 4x4 Tic-Tac-Toe UI with welcome message.
     */
    FourByFour_UI();

    /**
     * @brief Gets a move from the player.
     * 
     * For human players, prompts for source and destination coordinates.
     * For computer players, uses the AI to calculate the best move.
     * 
     * @param player Pointer to the current player.
     * @return Pointer to the Move object with source and destination.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol The player's symbol ('X' or 'O').
     * @param t The type of player (Human or Computer).
     * @return Pointer to the created Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType t) override;
};

#endif
