/**
 * @file FourByFour_Board.h
 * @brief Defines the 4x4 Tic-Tac-Toe board class.
 *
 * This variant uses a pre-set 4x4 board where players move their tokens
 * instead of placing new ones. A player wins by getting 3 in a row.
 */

#ifndef FOURBYFOUR_BOARD_H
#define FOURBYFOUR_BOARD_H

#include "../BoardGame_Classes.h"

/**
 * @class FourByFour_Board
 * @brief Represents a 4x4 Tic-Tac-Toe board with movable pieces.
 *
 * In this variant, players start with pieces already on the board
 * and move them horizontally or vertically to adjacent empty cells.
 * The goal is to get 3 pieces in a row.
 *
 * @see Board
 */
class FourByFour_Board : public Board<char> {
public:
    /**
     * @brief Constructs a 4x4 board with initial piece placement.
     * 
     * Initializes the board with X and O pieces in starting positions.
     */
    FourByFour_Board();

    /**
     * @brief Updates the board by moving a piece.
     * @param move Pointer to the move containing source and destination coordinates.
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
     * @return true if the opponent has 3 in a row, false otherwise.
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks if the game is a draw.
     * @param player Pointer to the player to check.
     * @return Always returns false (no draws in this variant).
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game is over.
     * @param player Pointer to the player to evaluate.
     * @return true if any player has won, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Checks if a symbol has 3 in a row anywhere on the board.
     * @param symbol The symbol to check ('X' or 'O').
     * @return true if 3 in a row exists, false otherwise.
     */
    bool check_three_in_line(char symbol);

    /**
     * @brief Gets a reference to the board matrix.
     * @return Reference to the 2D vector board.
     */
    vector<vector<char>>& get_board() {
        return board;}

private:
    /**
     * @brief Checks if coordinates are within board bounds.
     * @param r Row index.
     * @param c Column index.
     * @return true if within bounds, false otherwise.
     */
    bool in_bounds(int r, int c);
  
};

#endif
