/**
 * @file MisereTTT_Classes.cpp
 * @brief Implementation of the Misère (Inverse) Tic-Tac-Toe game classes.
 */

#include "MisereTTT_Classes.h"
#include <iostream>
#include <limits>

using namespace std;

// ==================== MisereBoard Implementation ====================

/**
 * @brief Constructs an empty 3x3 board.
 */
MisereBoard::MisereBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

/**
 * @brief Displays the current board state.
 */
void MisereBoard::display() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

/**
 * @brief Checks if the board is completely filled.
 * @return true if no empty cells remain, false otherwise.
 */
bool MisereBoard::is_full() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

/**
 * @brief Places a mark at the specified position.
 * @param r Row index (0-2).
 * @param c Column index (0-2).
 * @param mark The mark to place ('X' or 'O').
 * @return true if the move was valid, false otherwise.
 */
bool MisereBoard::place_mark(int r, int c, char mark) {
    if (r < 0 || r > 2 || c < 0 || c > 2) return false;
    if (board[r][c] != ' ') return false;

    board[r][c] = mark;
    return true;
}

/**
 * @brief Checks if a mark has created three-in-a-row.
 * 
 * Checks rows, columns, and diagonals for three matching marks.
 * 
 * @param m The mark to check ('X' or 'O').
 * @return true if three-in-a-row exists (player loses), false otherwise.
 */
bool MisereBoard::makes_three_in_row(char m) {
    // Check rows
    for (int i = 0; i < 3; i++)
        if (board[i][0] == m && board[i][1] == m && board[i][2] == m)
            return true;

    // Check columns
    for (int j = 0; j < 3; j++)
        if (board[0][j] == m && board[1][j] == m && board[2][j] == m)
            return true;

    // Check diagonals
    if (board[0][0] == m && board[1][1] == m && board[2][2] == m)
        return true;

    if (board[0][2] == m && board[1][1] == m && board[2][0] == m)
        return true;

    return false;
}

// ==================== MisereGame Implementation ====================

/**
 * @brief Constructs a Misère game with two players.
 * @param p1 Name of player 1 (plays 'X').
 * @param p2 Name of player 2 (plays 'O').
 */
MisereGame::MisereGame(string p1, string p2) {
    this->p1 = p1;
    this->p2 = p2;
    turn = 'X';
}

/**
 * @brief Runs the main game loop.
 * 
 * Alternates turns between players until someone makes three-in-a-row
 * (and loses) or the board is full (draw).
 */
void MisereGame::play() {
    while (true) {
        board.display();

        string current_player_name = (turn == 'X' ? p1 : p2);
        cout << current_player_name << " (" << turn << ") enter row and column (0-2): ";

        int r, c;
        if (!(cin >> r >> c)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter two integers (row and column between 0 and 2).\n";
            continue;
        }

        if (!board.place_mark(r, c, turn)) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        // Check if current player made three-in-a-row (loses!)
        if (board.makes_three_in_row(turn)) {
            board.display();
            cout << current_player_name << " (" << turn << ") made three-in-a-row and loses! ";
            cout << "Winner is " << (turn == 'X' ? p2 : p1) << ".\n";
            break;
        }

        // Check for draw
        if (board.is_full()) {
            board.display();
            cout << "Board is full. It's a draw \n";
            break;
        }

        // Switch turn
        turn = (turn == 'X' ? 'O' : 'X');
    }
}
