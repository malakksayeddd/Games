/**
 * @file FiveByFiveTTT_Classes.h
 * @brief Defines the 5x5 Tic-Tac-Toe game classes.
 *
 * This file provides:
 * - `FiveByFive_Board`: A 5x5 board where players compete to get more three-in-a-row sequences.
 * - `FiveByFive_UI`: User interface for the 5x5 Tic-Tac-Toe game.
 *
 * In this variant, the game ends when 24 cells are filled (1 empty remaining),
 * and the winner is whoever has more three-in-a-row sequences.
 */

#ifndef FIVEBYFIVE_CLASSES_H
#define FIVEBYFIVE_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class FiveByFive_Board
 * @brief Represents a 5x5 Tic-Tac-Toe game board.
 *
 * This class implements a variant where players compete to create the most
 * three-in-a-row sequences. The game ends when only one cell remains empty.
 *
 * @see Board
 */
class FiveByFive_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character representing an empty cell.

public:
    /**
     * @brief Constructs a 5x5 board initialized with empty cells.
     */
    FiveByFive_Board();
    
    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the move containing coordinates and symbol.
     * @return true if the move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the player has won (has more three-in-a-row sequences).
     * @param player Pointer to the player to check.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the player has lost.
     * @param player Pointer to the player to check.
     * @return true if the player has lost, false otherwise.
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks if the game ended in a draw.
     * @param player Pointer to the player to check.
     * @return true if scores are equal, false otherwise.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game is over (24 moves made).
     * @param player Pointer to the player to evaluate.
     * @return true if game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Counts all three-in-a-row sequences for a given symbol.
     * @param sym The symbol ('X' or 'O') to count sequences for.
     * @return The number of three-in-a-row sequences.
     */
    int count_three_in_a_row(char sym) const;

    /**
     * @brief Gets the value at a specific cell.
     * @param r Row index.
     * @param c Column index.
     * @return The character at the specified cell.
     */
    char get_cell(int r, int c) const { return board[r][c]; }

    /**
     * @brief Sets the value at a specific cell.
     * @param r Row index.
     * @param c Column index.
     * @param val The value to set.
     */
    void set_cell(int r, int c, char val) { board[r][c] = val; }

    /**
     * @brief Decrements the move counter (used for undo operations).
     */
    void decrement_moves() { n_moves--; }
};

/**
 * @class FiveByFive_UI
 * @brief User Interface class for the 5x5 Tic-Tac-Toe game.
 *
 * Handles player interaction and move input for the 5x5 variant.
 *
 * @see UI
 */
class FiveByFive_UI : public UI<char> {
private:
    FiveByFive_Board* boardPtr; ///< Pointer to the game board.

public:
    /**
     * @brief Constructs the UI for 5x5 Tic-Tac-Toe.
     */
    FiveByFive_UI();

    /**
     * @brief Launches the 5x5 Tic-Tac-Toe game.
     */
    void launch();

    /**
     * @brief Sets the board pointer for the UI.
     * @param b Pointer to the FiveByFive_Board.
     */
    void set_board(FiveByFive_Board* b) { boardPtr = b; }

    /**
     * @brief Gets a move from the player (human or AI).
     * @param player Pointer to the current player.
     * @return Pointer to the Move object.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Displays the board matrix.
     * @param matrix The board matrix to display.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};

#endif // FIVEBYFIVE_CLASSES_H
