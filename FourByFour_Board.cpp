/**
 * @file FourByFour_Board.cpp
 * @brief Implementation of the 4x4 Tic-Tac-Toe board class.
 */

#include "FourByFour_Board.h"
#include <cmath>

/**
 * @brief Constructs a 4x4 board with initial piece placement.
 * 
 * Sets up the board with alternating X and O pieces on the top and bottom rows.
 */
FourByFour_Board::FourByFour_Board()
    : Board<char>(4, 4)
{
    board = {
        {'O', 'X', 'O', 'X'},
        {'.', '.', '.', '.'},
        {'.', '.', '.', '.'},
        {'X', 'O', 'X', 'O'}
    };
}


/**
 * @brief Checks if coordinates are within board bounds.
 * @param r Row index.
 * @param c Column index.
 * @return true if coordinates are valid (0-3), false otherwise.
 */
bool FourByFour_Board::in_bounds(int r, int c) {
    return r >= 0 && r < 4 && c >= 0 && c < 4;
}


/**
 * @brief Updates the board by moving a piece.
 * 
 * Validates that:
 * - Source and destination are in bounds
 * - Player is moving their own piece
 * - Destination is empty
 * - Move is exactly one cell horizontally or vertically
 * 
 * @param move Pointer to the move containing source and destination.
 * @return true if the move was valid and applied, false otherwise.
 */
bool FourByFour_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int nx = move->getNewX();
    int ny = move->getNewY();
    char s = move->get_symbol();

    if (!in_bounds(x, y) || !in_bounds(nx, ny))
        return false;

    // must move your own symbol
    if (board[x][y] != s) return false;

    // dest must be empty
    if (board[nx][ny] != '.') return false;

    // move must be hor or ver only
    int dr = abs(nx - x);
    int dc = abs(ny - y);

    if (dr + dc != 1) return false;

    // apply move
    board[x][y] = '.';
    board[nx][ny] = s;

    return true;
}


/**
 * @brief Checks if a symbol has 3 in a row anywhere on the board.
 * 
 * Checks rows, columns, and both diagonals.
 * 
 * @param sym The symbol to check ('X' or 'O').
 * @return true if 3 in a row exists, false otherwise.
 */
bool FourByFour_Board::check_three_in_line(char sym) {
    // check rows
    for (int r = 0; r < 4; r++)
        for (int c = 0; c <= 1; c++)
            if (board[r][c] == sym && board[r][c+1] == sym && board[r][c+2] == sym)
                return true;

    // check columns
    for (int c = 0; c < 4; c++)
        for (int r = 0; r <= 1; r++)
            if (board[r][c] == sym && board[r+1][c] == sym && board[r+2][c] == sym)
                return true;

    // diagonals
    // top-left to bottom-right
    for (int r = 0; r <= 1; r++)
        for (int c = 0; c <= 1; c++)
            if (board[r][c] == sym && board[r+1][c+1] == sym && board[r+2][c+2] == sym)
                return true;

    // top-right to bottom-left
    for (int r = 0; r <= 1; r++)
        for (int c = 2; c < 4; c++)
            if (board[r][c] == sym && board[r+1][c-1] == sym && board[r+2][c-2] == sym)
                return true;

    return false;
}

/**
 * @brief Checks if the player has won.
 * @param p Pointer to the player to check.
 * @return true if the player has 3 in a row, false otherwise.
 */
bool FourByFour_Board::is_win(Player<char>* p) {
    return check_three_in_line(p->get_symbol());
}

/**
 * @brief Checks if the player has lost.
 * @param p Pointer to the player to check.
 * @return true if the opponent has 3 in a row, false otherwise.
 */
bool FourByFour_Board::is_lose(Player<char>* p) {
    char opponent = (p->get_symbol() == 'X' ? 'O' : 'X');
    return check_three_in_line(opponent);
}

/**
 * @brief Checks if the game is a draw.
 * @param Unused parameter.
 * @return Always false (no draws in this variant).
 */
bool FourByFour_Board::is_draw(Player<char>*) {
    return false;
}

/**
 * @brief Checks if the game is over.
 * @param p Pointer to the player to evaluate.
 * @return true if either player has won, false otherwise.
 */
bool FourByFour_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p);
}
