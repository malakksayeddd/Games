/**
 * @file UltimateTTT_Classes.h
 * @brief Defines the Ultimate Tic-Tac-Toe game classes.
 *
 * Ultimate TTT is played on a 9x9 board consisting of nine 3x3 sub-boards.
 * To win the main game, a player must win three sub-boards in a row.
 * After winning a sub-board, it's claimed on the main 3x3 meta-board.
 */

#ifndef ULTIMATETTT_CLASSES_H
#define ULTIMATETTT_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Ultimate_Board
 * @brief Represents the Ultimate Tic-Tac-Toe game board.
 *
 * Manages both the 9 sub-boards (3x3 each) and the main meta-board
 * that tracks which player has won each sub-board.
 *
 * @see Board
 */
class Ultimate_Board : public Board<char> {
private:
    char subBoards[3][3][3][3];  ///< Sub-boards: [subRow][subCol][cellRow][cellCol]
    char mainBoard[3][3];        ///< Main board tracking sub-board winners ('X', 'O', '#'=draw, '.'=open)
    int currentSubRow;           ///< Current active sub-board row (-1 = free choice)
    int currentSubCol;           ///< Current active sub-board column (-1 = free choice)
    
    /**
     * @brief Checks if three values match a symbol.
     * @param a First value.
     * @param b Second value.
     * @param c Third value.
     * @param sym Symbol to match.
     * @return true if all three match the symbol, false otherwise.
     */
    bool check_three(char a, char b, char c, char sym) const;

    /**
     * @brief Checks if a player has won a sub-board.
     * @param sr Sub-board row index.
     * @param sc Sub-board column index.
     * @param sym The player's symbol.
     * @return true if the player won the sub-board, false otherwise.
     */
    bool check_sub_winner(int sr, int sc, char sym) const;

    /**
     * @brief Checks if a sub-board is completely filled.
     * @param sr Sub-board row index.
     * @param sc Sub-board column index.
     * @return true if the sub-board is full, false otherwise.
     */
    bool is_sub_full(int sr, int sc) const;
    
public:
    /**
     * @brief Constructs an empty Ultimate board.
     */
    Ultimate_Board();
    
    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the move (9x9 coordinates mapped to sub-board).
     * @return true if the move is valid, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the player has won the main game.
     * @param player Pointer to the player to check.
     * @return true if 3 sub-boards in a row, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the player has lost.
     * @param Unused parameter.
     * @return Always returns false.
     */
    bool is_lose(Player<char>*) override { return false; }

    /**
     * @brief Checks if the game is a draw.
     * @param player Pointer to the player to check.
     * @return true if all sub-boards completed with no winner, false otherwise.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game is over.
     * @param player Pointer to the player to evaluate.
     * @return true if game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;
    
    /**
     * @brief Gets a cell value from a sub-board.
     * @param sr Sub-board row.
     * @param sc Sub-board column.
     * @param cr Cell row within sub-board.
     * @param cc Cell column within sub-board.
     * @return The character at the cell.
     */
    char get_sub_cell(int sr, int sc, int cr, int cc) const { return subBoards[sr][sc][cr][cc]; }

    /**
     * @brief Gets the main board cell value (sub-board winner).
     * @param r Row index on main board.
     * @param c Column index on main board.
     * @return The winner of that sub-board or '.' if open.
     */
    char get_main_cell(int r, int c) const { return mainBoard[r][c]; }

    /**
     * @brief Checks if a sub-board is completed.
     * @param sr Sub-board row.
     * @param sc Sub-board column.
     * @return true if won or drawn, false if still playable.
     */
    bool is_sub_completed(int sr, int sc) const { return mainBoard[sr][sc] != '.'; }

    /**
     * @brief Gets the current active sub-board row.
     * @return Row index, or -1 if free choice.
     */
    int get_current_sub_row() const { return currentSubRow; }

    /**
     * @brief Gets the current active sub-board column.
     * @return Column index, or -1 if free choice.
     */
    int get_current_sub_col() const { return currentSubCol; }

    /**
     * @brief Sets the current active sub-board.
     * @param r Row index.
     * @param c Column index.
     */
    void set_current_sub(int r, int c) { currentSubRow = r; currentSubCol = c; }
};

/**
 * @class Ultimate_UI
 * @brief User Interface class for Ultimate Tic-Tac-Toe.
 *
 * Handles the complex display and input for the nested board structure.
 *
 * @see UI
 */
class Ultimate_UI : public UI<char> {
private:
    Ultimate_Board* boardPtr; ///< Pointer to the game board.

public:
    /**
     * @brief Constructs the Ultimate Tic-Tac-Toe UI.
     */
    Ultimate_UI();

    /**
     * @brief Sets the board pointer.
     * @param b Pointer to the Ultimate_Board.
     */
    void set_board(Ultimate_Board* b) { boardPtr = b; }
    
    /**
     * @brief Gets a move from the player.
     * @param player Pointer to the current player.
     * @return Pointer to the Move object (9x9 coordinates).
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Displays the main board and current sub-board.
     */
    void display_board() const;

    /**
     * @brief Override to use custom display format.
     * @param matrix Ignored - uses display_board() instead.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const override { display_board(); }

    /**
     * @brief Launches the Ultimate Tic-Tac-Toe game.
     */
    void launch();
};

#endif // ULTIMATETTT_CLASSES_H
