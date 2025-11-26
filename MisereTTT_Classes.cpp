#include "MisereTTT_Classes.h"
#include <iostream>
#include <limits>

using namespace std;

// ---- Board constructor ----
MisereBoard::MisereBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

// ---- Display board ----
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

// ---- Check full ----
bool MisereBoard::is_full() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

// ---- Place mark ----
bool MisereBoard::place_mark(int r, int c, char mark) {
    if (r < 0 || r > 2 || c < 0 || c > 2) return false;
    if (board[r][c] != ' ') return false;

    board[r][c] = mark;
    return true;
}

// ---- Player loses if creates 3-in-row ----
bool MisereBoard::makes_three_in_row(char m) {
    // rows
    for (int i = 0; i < 3; i++)
        if (board[i][0] == m && board[i][1] == m && board[i][2] == m)
            return true;

    // columns
    for (int j = 0; j < 3; j++)
        if (board[0][j] == m && board[1][j] == m && board[2][j] == m)
            return true;

    // diagonals
    if (board[0][0] == m && board[1][1] == m && board[2][2] == m)
        return true;

    if (board[0][2] == m && board[1][1] == m && board[2][0] == m)
        return true;

    return false;
}

// ---- Game constructor ----
MisereGame::MisereGame(string p1, string p2) {
    this->p1 = p1;
    this->p2 = p2;
    turn = 'X';
}

// ---- Play game ----
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

        
        if (board.makes_three_in_row(turn)) {
            board.display();
            cout << current_player_name << " (" << turn << ") made three-in-a-row and loses! ";
            cout << "Winner is " << (turn == 'X' ? p2 : p1) << ".\n";
            break;
        }

        
        if (board.is_full()) {
            board.display();
            cout << "Board is full. It's a draw \n";
           
            break;
        }

        // switch turn
        turn = (turn == 'X' ? 'O' : 'X');
    }
}
