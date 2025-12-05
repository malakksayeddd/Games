/**
 * @file SUS_Classes.h
 * @brief Defines the SUS game classes.
 *
 * In this variant:
 * - Player 1 places 'S' marks
 * - Player 2 places 'U' marks
 * - Players score points by creating "SUS" sequences
 * - The player with more sequences at the end wins
 */

#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
#include <utility>
using namespace std;

/**
 * @class SUS_Board
 * @brief Represents the SUS game board.
 *
 * A 3x3 board where players try to create "SUS" sequences
 * (rows, columns, or diagonals that spell "SUS").
 *
 * @see Board
 */
class SUS_Board : public Board<char> {
private:
    int sequences; ///< Current total count of SUS sequences.

    /**
     * @brief Checks if three characters form "SUS".
     * @param a First character.
     * @param b Second character.
     * @param c Third character.
     * @return true if the sequence is "SUS", false otherwise.
     */
    static bool seq(char a, char b, char c) {
        return (a == 'S' && b == 'U' && c == 'S');
    }

public:
    /**
     * @brief Constructs an empty SUS board.
     */
    SUS_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the move containing coordinates and symbol.
     * @return true if the move is valid, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if there are any SUS sequences.
     * @param p Pointer to the player (unused).
     * @return true if sequences exist, false otherwise.
     */
    bool is_win(Player<char>* p) override;

    /**
     * @brief Checks if the player has lost.
     * @param p Pointer to the player to check.
     * @return Always returns false.
     */
    bool is_lose(Player<char>* p) override;

    /**
     * @brief Checks if the game is a draw.
     * @param p Pointer to the player to check.
     * @return true if board is full with no sequences, false otherwise.
     */
    bool is_draw(Player<char>* p) override;

    /**
     * @brief Checks if the game is over (board full).
     * @param p Pointer to the player to evaluate.
     * @return true if board is full, false otherwise.
     */
    bool game_is_over(Player<char>* p) override;

    /**
     * @brief Places a symbol at the specified position.
     * @param r Row index.
     * @param c Column index.
     * @param sym The symbol to place ('S' or 'U').
     * @return true if placement was valid, false otherwise.
     */
    bool place(int r, int c, char sym);

    /**
     * @brief Removes a symbol from a position (for AI backtracking).
     * @param r Row index.
     * @param c Column index.
     */
    void undo(int r, int c);

    /**
     * @brief Gets the value at a cell.
     * @param r Row index.
     * @param c Column index.
     * @return The character at the cell.
     */
    char getCell(int r, int c);

    /**
     * @brief Counts all current SUS sequences on the board.
     * @return The number of SUS sequences.
     */
    int countSequences();

    /**
     * @brief Gets the stored sequence count.
     * @return The stored sequence count.
     */
    int getSequences() const;

    /**
     * @brief Sets the stored sequence count.
     * @param s The new sequence count.
     */
    void setSequences(int s);

    /**
     * @brief Checks if the board is full.
     * @return true if no empty cells remain, false otherwise.
     */
    bool full();

    /**
     * @brief Displays the current board state.
     */
    void display();
};

/**
 * @class SUS_Game
 * @brief Manages the SUS game flow.
 *
 * Handles scoring, turns, and AI opponent using Minimax.
 */
class SUS_Game {
private:
    SUS_Board board;   ///< The game board.
    int scoreP1;       ///< Player 1's score (S player).
    int scoreP2;       ///< Player 2's score (U player).
    bool turnP1;       ///< True if it's Player 1's turn.
    bool vsAI;         ///< True if playing against AI.

    string player1;    ///< Player 1's name.
    string player2;    ///< Player 2's name.

    /**
     * @brief Finds the best move for AI using Minimax.
     * @return Pair of (row, column) for the best move.
     */
    pair<int, int> bestMove();

public:
    /**
     * @brief Constructs a SUS game.
     * @param name1 Player 1's name (plays 'S').
     * @param name2 Player 2's name (plays 'U').
     * @param ai True if Player 2 is AI.
     */
    SUS_Game(string name1, string name2, bool ai);

    /**
     * @brief Runs the main game loop.
     */
    void play();
};
