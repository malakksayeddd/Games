#ifndef DIAMOND_TTT_H
#define DIAMOND_TTT_H

#include <vector>
#include <utility>
#include <string>
#include "BoardGame_Classes.h"   

/**
 * @class DiamondTTT
 * @brief Implements the Diamond-shaped TicTacToe game
 *        and inherits from Board<char>.
 *
 * The board is 5x5 but only diamond-shaped cells are valid.
 * The player wins by forming a line of 3 AND a line of 4
 * in different directions with at most one overlapping cell.
 */
class DiamondTTT : public Board<char> {
public:

    /**
     * @brief Constructs a Diamond TicTacToe board.
     *
     * Initializes internal board, valid cells, and all winning lines.
     */
    DiamondTTT();

    /**
     * @brief Runs the main interactive gameplay loop.
     */
    void play();

    // -------- Required overrides from Board<char> -------- //

    /**
     * @brief Updates the board using a Move<char> object.
     * @param move Pointer to move containing (x,y,symbol).
     * @return true if move is valid and placed, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the given player has won.
     * @param p Pointer to Player<char>.
     * @return true if this player has a winning configuration.
     */
    bool is_win(Player<char>* p);

    /**
     * @brief DiamondTTT has no losing condition, always returns false.
     */
    bool is_lose(Player<char>* p);

    /**
     * @brief Checks if the game is draw.
     * @return true if all valid cells were used.
     */
    bool is_draw(Player<char>* p);

    /**
     * @brief Checks whether game ended (win or draw).
     */
    bool game_is_over(Player<char>* p);

private:

    /**
     * @brief Internal 5x5 board storing only '.' , 'X' , 'O'.
     */
    char board_internal[7][7];

    /**
     * @brief Stores all valid diamond-shaped coordinates.
     */
    std::vector<std::pair<int, int>> valid_cells;

    /**
     * @brief Contains all possible lines (size 3 and 4)
     *        generated on diamond-shaped area.
     */
    std::vector<std::vector<std::pair<int, int>>> all_lines;

    // ---------- Internal helper functions ---------- //

    /**
     * @brief Fills board_internal with '.'.
     */
    void init_board();

    /**
     * @brief Calculates all valid board positions in a diamond shape.
     */
    void collect_valid_cells();

    /**
     * @brief Computes all straight lines that fit inside the diamond.
     */
    void build_all_lines();

    /**
     * @brief Prints current board state to console.
     */
    void print_board() const;

    /**
     * @brief Prints game instructions.
     */
    void print_instructions() const;

    /**
     * @brief Checks if cell lies inside the diamond shape.
     * @return true if (r,c) is valid.
     */
    bool is_valid_cell(int r, int c) const;

    /**
     * @brief Places a mark if valid and empty.
     */
    bool place_mark(int r, int c, char mark);

    /**
     * @brief Checks both winning conditions for a mark.
     */
    bool check_player_wins(char mark) const;

    /**
     * @brief Checks whether the entire line L is filled with the same mark.
     */
    bool line_filled(const std::vector<std::pair<int, int>>& L, char mark) const;
};

#endif
