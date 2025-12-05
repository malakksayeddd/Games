/**
 * @file MisereTTT_Classes.h
 * @brief Defines the Misère (Inverse) Tic-Tac-Toe game classes.
 *
 * In this variant, the player who makes three-in-a-row LOSES.
 * The objective is to force your opponent to complete a line.
 */

#ifndef MISERE_TTT_CLASSES_H
#define MISERE_TTT_CLASSES_H

#include <iostream>
#include <string>
using namespace std;

/**
 * @class MisereBoard
 * @brief Represents the Misère Tic-Tac-Toe game board.
 *
 * A standard 3x3 board where completing three-in-a-row results in a loss.
 */
class MisereBoard {
private:
    char board[3][3]; ///< The 3x3 game board.

public:
    /**
     * @brief Constructs an empty 3x3 board.
     */
    MisereBoard();

    /**
     * @brief Displays the current board state.
     */
    void display();

    /**
     * @brief Checks if the board is completely filled.
     * @return true if no empty cells remain, false otherwise.
     */
    bool is_full();

    /**
     * @brief Places a mark at the specified position.
     * @param r Row index (0-2).
     * @param c Column index (0-2).
     * @param mark The mark to place ('X' or 'O').
     * @return true if the move was valid, false otherwise.
     */
    bool place_mark(int r, int c, char mark);

    /**
     * @brief Checks if a mark has created three-in-a-row.
     * 
     * In Misère rules, creating three-in-a-row means the player loses.
     * 
     * @param mark The mark to check ('X' or 'O').
     * @return true if three-in-a-row exists, false otherwise.
     */
    bool makes_three_in_row(char mark);
};

/**
 * @class MisereGame
 * @brief Manages the Misère Tic-Tac-Toe game flow.
 *
 * Handles turn management and determines the winner (the player
 * who does NOT complete three-in-a-row).
 */
class MisereGame {
private:
    MisereBoard board;  ///< The game board.
    string p1;          ///< Player 1's name.
    string p2;          ///< Player 2's name.
    char turn;          ///< Current turn ('X' or 'O').

public:
    /**
     * @brief Constructs a Misère game with two players.
     * @param p1 Name of player 1 (plays 'X').
     * @param p2 Name of player 2 (plays 'O').
     */
    MisereGame(string p1, string p2);

    /**
     * @brief Runs the main game loop.
     */
    void play();
};

#endif
