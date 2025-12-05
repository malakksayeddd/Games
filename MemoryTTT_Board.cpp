/**
 * @file MemoryTTT_Board.cpp
 * @brief Implementation of the Memory Tic-Tac-Toe board class.
 *
 * Contains the implementation of MemoryTTT_Board with hidden display logic.
 */

#include "MemoryTTT_Board.h"
#include <iostream>
using namespace std;

/**
 * @brief Constructs a 3x3 Memory board with all cells empty.
 */
MemoryTTT_Board::MemoryTTT_Board()
    : Board<char>(N, N)
{
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            board[i][j] = '.';
    n_moves = 0;
}

/**
 * @brief Updates the board with a player's move.
 * @param move Pointer to the move containing coordinates and symbol.
 * @return true if the move was valid and applied, false otherwise.
 */
bool MemoryTTT_Board::update_board(Move<char>* move) {
    if (!move) return false;
    int r = move->get_x();
    int c = move->get_y();
    if (!in_range(r,c)) return false;
    if (board[r][c] != '.') return false;

    board[r][c] = move->get_symbol();
    n_moves++;
    return true;
}

/**
 * @brief Checks if a symbol has 3 in a row.
 * 
 * Checks rows, columns, and both diagonals.
 * 
 * @param s The symbol to check ('X' or 'O').
 * @return true if 3 in a row exists, false otherwise.
 */
bool MemoryTTT_Board::symbol_has_triplet(char s) const {
    // Check rows
    for (int r=0;r<N;r++) {
        bool ok=true;
        for (int c=0;c<N;c++)
            if (board[r][c] != s) ok=false;
        if (ok) return true;
    }

    // Check columns
    for (int c=0;c<N;c++) {
        bool ok=true;
        for (int r=0;r<N;r++)
            if (board[r][c] != s) ok=false;
        if (ok) return true;
    }

    // Check main diagonal
    bool ok=true;
    for (int i=0;i<N;i++)
        if (board[i][i] != s) ok=false;
    if (ok) return true;

    // Check anti-diagonal
    ok=true;
    for (int i=0;i<N;i++)
        if (board[i][N-1-i] != s) ok=false;
    if (ok) return true;

    return false;
}

/**
 * @brief Checks if the player has won.
 * @param p Pointer to the player to check.
 * @return true if the player has 3 in a row, false otherwise.
 */
bool MemoryTTT_Board::is_win(Player<char>* p) {
    return symbol_has_triplet(p->get_symbol());
}

/**
 * @brief Checks if the player has lost.
 * @param p Pointer to the player to check.
 * @return true if the opponent has 3 in a row, false otherwise.
 */
bool MemoryTTT_Board::is_lose(Player<char>* p) {
    char s = p->get_symbol();
    char o = (s=='X' ? 'O' : 'X');
    return symbol_has_triplet(o);
}

/**
 * @brief Checks if the game is a draw.
 * @param Unused parameter.
 * @return true if board is full with no winner, false otherwise.
 */
bool MemoryTTT_Board::is_draw(Player<char>*) {
    if (n_moves < N*N) return false;
    if (symbol_has_triplet('X') || symbol_has_triplet('O')) return false;
    return true;
}

/**
 * @brief Checks if the game is over.
 * @param p Pointer to the player to evaluate.
 * @return true if game has ended (win, lose, or draw), false otherwise.
 */
bool MemoryTTT_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}

/**
 * @brief Gets a list of all empty cells on the board.
 * @return Vector of (row, column) pairs for empty cells.
 */
vector<pair<int,int>> MemoryTTT_Board::empty_cells() const {
    vector<pair<int,int>> v;
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            if (board[i][j] == '.') v.push_back({i,j});
    return v;
}

/**
 * @brief Displays the board with all cells hidden.
 * 
 * Shows the grid structure but hides all cell values.
 */
void MemoryTTT_Board::display_hidden() const {
    cout << "\n    0   1   2\n";
    cout << "  -------------\n";
    for (int r=0;r<N;r++) {
        cout << r << " | ";
        for (int c=0;c<N;c++)
            cout << ". | ";
        cout << "\n  -------------\n";
    }
}

/**
 * @brief Debug function to print the actual board state.
 * 
 * Reveals all cell values for debugging purposes.
 */
void MemoryTTT_Board::debug_print_memory() const {
    cout << "\nActual board:\n";
    for (int r=0;r<N;r++) {
        for (int c=0;c<N;c++)
            cout << board[r][c] << " ";
        cout << "\n";
    }
}
