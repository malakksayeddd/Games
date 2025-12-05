/**
 * @file PyramidTTT_Classes.h
 * @brief Defines the Pyramid Tic-Tac-Toe game classes.
 *
 * This variant uses a pyramid-shaped board with 3 rows:
 * - Row 0: 1 cell (top)
 * - Row 1: 3 cells (middle)
 * - Row 2: 5 cells (bottom)
 * 
 * Players win by getting 3 in a row on valid winning lines.
 */

#ifndef PYRAMID_TTT_CLASSES_H
#define PYRAMID_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
using namespace std;

/**
 * @class Pyramid_Board
 * @brief Represents the Pyramid Tic-Tac-Toe game board.
 *
 * A pyramid-shaped board with specific valid positions and winning lines.
 *
 * @see Board
 */
class Pyramid_Board : public Board<char> {
public:
    /**
     * @brief Constructs a pyramid board with empty playable cells.
     */
    Pyramid_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the move containing coordinates and symbol.
     * @return true if the move is valid, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the player has won (3 in a row on winning lines).
     * @param p Pointer to the player to check.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* p) override;

    /**
     * @brief Checks if the player has lost.
     * @param p Pointer to the player to check.
     * @return true if the opponent has won, false otherwise.
     */
    bool is_lose(Player<char>* p) override;

    /**
     * @brief Checks if the game is a draw.
     * @param p Pointer to the player to check.
     * @return true if board is full with no winner, false otherwise.
     */
    bool is_draw(Player<char>* p) override;

    /**
     * @brief Checks if the game is over.
     * @param p Pointer to the player to evaluate.
     * @return true if game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* p) override;

    /**
     * @brief Gets a list of all empty playable cells.
     * @return Vector of (row, column) pairs for empty cells.
     */
    vector<pair<int,int>> get_empty_cells() const;

    /**
     * @brief Gets the value at a specific cell.
     * @param r Row index.
     * @param c Column index.
     * @return The character at the cell, or '#' if out of bounds.
     */
    char get_cell(int r,int c) const;

private:
    vector<vector<pair<int,int>>> winning_lines; ///< All valid winning line combinations.

    /**
     * @brief Builds the list of valid winning lines for the pyramid.
     */
    void build_winning_lines();
};

/**
 * @class Pyramid_UI
 * @brief User Interface class for the Pyramid Tic-Tac-Toe game.
 *
 * @see UI
 */
class Pyramid_UI : public UI<char> {
public:
    /**
     * @brief Constructs the Pyramid Tic-Tac-Toe UI.
     */
    Pyramid_UI() : UI<char>(3) {}

    /**
     * @brief Gets a move from the player.
     * @param p Pointer to the current player.
     * @return Pointer to the Move object.
     */
    Move<char>* get_move(Player<char>* p) override;

    /**
     * @brief Displays the pyramid-shaped board.
     * @param matrix The board matrix to display.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const override;

    /**
     * @brief Sets up both players for the game.
     * @return Array of two Player pointers.
     */
    Player<char>** setup_players() override;
};

/**
 * @class Pyramid_AI_Player
 * @brief AI player using Minimax algorithm for Pyramid TTT.
 *
 * @see Player
 */
class Pyramid_AI_Player : public Player<char> {
public:
    /**
     * @brief Constructs an AI player.
     * @param n The player's name.
     * @param s The player's symbol ('X' or 'O').
     */
    Pyramid_AI_Player(string n, char s)
        : Player<char>(n, s, PlayerType::COMPUTER) {}

    /**
     * @brief Gets the best move using Minimax.
     * @return Pointer to the optimal Move.
     */
    Move<char>* get_move();

private:
    /**
     * @brief Finds the best move using Minimax algorithm.
     * @param board Pointer to the game board.
     * @param ai_symbol The AI's symbol.
     * @return Pointer to the best Move.
     */
    Move<char>* minimax_best_move(Pyramid_Board* board, char ai_symbol);

    /**
     * @brief Minimax algorithm with alpha-beta pruning.
     * @param board Pointer to the game board.
     * @param maximizingPlayer True if AI's turn.
     * @param ai_symbol The AI's symbol.
     * @param depth Current search depth.
     * @param alpha Alpha value for pruning.
     * @param beta Beta value for pruning.
     * @return The evaluation score for the position.
     */
    int minimax(Pyramid_Board* board, bool maximizingPlayer, char ai_symbol, int depth, int alpha, int beta);
};

#endif
