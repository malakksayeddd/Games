/**
 * @file MemoryTTT_Board.h
 * @brief Defines the Memory Tic-Tac-Toe board class.
 *
 * In this variant, the board is hidden from players - they must
 * remember where pieces have been placed. Players cannot see
 * the actual board state during gameplay.
 */

#ifndef MEMORY_TTT_BOARD_H
#define MEMORY_TTT_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>

/**
 * @class MemoryTTT_Board
 * @brief Represents the Memory Tic-Tac-Toe game board.
 *
 * A hidden 3x3 board where players must rely on memory to
 * remember cell states. The actual board is only revealed
 * for debugging purposes.
 *
 * @see Board
 */
class MemoryTTT_Board : public Board<char> {
public:
    static const int N = 3; ///< Board dimension (3x3).

    /**
     * @brief Constructs a 3x3 Memory board with all cells empty.
     */
    MemoryTTT_Board();

    /**
     * @brief Virtual destructor.
     */
    virtual ~MemoryTTT_Board() = default;

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the move containing coordinates and symbol.
     * @return true if the move is valid and applied, false otherwise.
     */
    virtual bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the player has won (3 in a row).
     * @param Pointer to the player to check.
     * @return true if the player has won, false otherwise.
     */
    virtual bool is_win(Player<char>*) override;

    /**
     * @brief Checks if the player has lost.
     * @param Pointer to the player to check.
     * @return true if the opponent has 3 in a row, false otherwise.
     */
    virtual bool is_lose(Player<char>*) override;

    /**
     * @brief Checks if the game is a draw.
     * @param Pointer to the player to check.
     * @return true if board is full with no winner, false otherwise.
     */
    virtual bool is_draw(Player<char>*) override;

    /**
     * @brief Checks if the game is over.
     * @param Pointer to the player to evaluate.
     * @return true if game has ended, false otherwise.
     */
    virtual bool game_is_over(Player<char>*) override;

    /**
     * @brief Gets a list of all empty cells on the board.
     * @return Vector of (row, column) pairs for empty cells.
     */
    std::vector<std::pair<int,int>> empty_cells() const;

    /**
     * @brief Displays the board with all cells hidden.
     */
    void display_hidden() const;

    /**
     * @brief Debug function to print the actual board state.
     */
    void debug_print_memory() const;

private:
    /**
     * @brief Checks if a symbol has 3 in a row.
     * @param symbol The symbol to check ('X' or 'O').
     * @return true if 3 in a row exists, false otherwise.
     */
    bool symbol_has_triplet(char symbol) const;

    /**
     * @brief Checks if coordinates are within board bounds.
     * @param r Row index.
     * @param c Column index.
     * @return true if within bounds, false otherwise.
     */
    bool in_range(int r, int c) const { return r>=0 && r<N && c>=0 && c<N; }
};

#endif
