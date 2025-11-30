#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "FiveByFiveTTT_Classes.h"

using namespace std;

// ================== FiveByFive_Board Implementation ==================

FiveByFive_Board::FiveByFive_Board() : Board<char>(5, 5) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool FiveByFive_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (board[x][y] != blank_symbol)
        return false;

    board[x][y] = move->get_symbol();
    n_moves++;
    return true;
}

int FiveByFive_Board::count_three_in_a_row(char sym) const {
    int count = 0;

    // Horizontal
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c <= columns - 3; ++c)
            if (board[r][c] == sym && board[r][c+1] == sym && board[r][c+2] == sym)
                count++;

    // Vertical
    for (int c = 0; c < columns; ++c)
        for (int r = 0; r <= rows - 3; ++r)
            if (board[r][c] == sym && board[r+1][c] == sym && board[r+2][c] == sym)
                count++;

    // Diagonal (top-left to bottom-right)
    for (int r = 0; r <= rows - 3; ++r)
        for (int c = 0; c <= columns - 3; ++c)
            if (board[r][c] == sym && board[r+1][c+1] == sym && board[r+2][c+2] == sym)
                count++;

    // Diagonal (bottom-left to top-right)
    for (int r = 2; r < rows; ++r)
        for (int c = 0; c <= columns - 3; ++c)
            if (board[r][c] == sym && board[r-1][c+1] == sym && board[r-2][c+2] == sym)
                count++;

    return count;
}

bool FiveByFive_Board::game_is_over(Player<char>* player) {
    return n_moves >= 24;  // Game ends when only 1 square remains
}

bool FiveByFive_Board::is_win(Player<char>* player) {
    if (!game_is_over(player)) return false;
    
    int x_score = count_three_in_a_row('X');
    int o_score = count_three_in_a_row('O');
    
    return (player->get_symbol() == 'X') ? (x_score > o_score) : (o_score > x_score);
}

bool FiveByFive_Board::is_lose(Player<char>* player) {
    if (!game_is_over(player)) return false;
    
    int x_score = count_three_in_a_row('X');
    int o_score = count_three_in_a_row('O');
    
    return (player->get_symbol() == 'X') ? (o_score > x_score) : (x_score > o_score);
}

bool FiveByFive_Board::is_draw(Player<char>* player) {
    if (!game_is_over(player)) return false;
    return count_three_in_a_row('X') == count_three_in_a_row('O');
}


// ================== FiveByFive_UI Implementation ==================

FiveByFive_UI::FiveByFive_UI() : UI<char>(3), boardPtr(nullptr) {}

Move<char>* FiveByFive_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::COMPUTER) {
        // Random move for computer
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (boardPtr && boardPtr->get_cell(x, y) != '.');
        
        cout << player->get_name() << " plays at (" << x << ", " << y << ")\n";
    } else {
        cout << player->get_name() << " (" << player->get_symbol() << "), enter move (row col): ";
        cin >> x >> y;
    }

    return new Move<char>(x, y, player->get_symbol());
}

void FiveByFive_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    UI<char>::display_board_matrix(matrix);
    
    if (boardPtr) {
        int x_score = boardPtr->count_three_in_a_row('X');
        int o_score = boardPtr->count_three_in_a_row('O');
        cout << "Scores -> X: " << x_score << " | O: " << o_score << "\n";
    }
}

void FiveByFive_UI::launch() {
    cout << "\nWelcome to 5x5 Tic-Tac-Toe!\n";
    cout << "Rules:\n";
    cout << "-> Players take turns placing marks on a 5x5 grid\n";
    cout << "-> Game ends when only ONE square remains empty (24 moves)\n";
    cout << "-> The player with the MOST three-in-a-row sequences WINS!\n\n";
    FiveByFive_UI* game_ui = new FiveByFive_UI();
    FiveByFive_Board* five_board = new FiveByFive_Board();
    game_ui->set_board(five_board);
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(five_board, players, game_ui);
    game.run();

    delete five_board;
    for (int i = 0; i < 2; ++i)
        delete players[i];
    delete[] players;
    delete game_ui;
}