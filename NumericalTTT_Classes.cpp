#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "NumericalTTT_Classes.h"
using namespace std;

// Board Implementation 

Numerical_Board::Numerical_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Numerical_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int val = move->get_symbol();

    if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == blank_symbol) {
        board[x][y] = val;
        n_moves++;
        return true;
    }
    return false;
}

bool Numerical_Board::is_win(Player<int>* player) {
    auto sum15 = [&](int a, int b, int c) { return (a + b + c == 15); };

    for (int i = 0; i < 3; ++i) {
        if (sum15(board[i][0], board[i][1], board[i][2]) ||
            sum15(board[0][i], board[1][i], board[2][i]))
            return true;
    }
    if (sum15(board[0][0], board[1][1], board[2][2]) ||
        sum15(board[0][2], board[1][1], board[2][0]))
        return true;

    return false;
}

bool Numerical_Board::is_draw(Player<int>* player) {
  
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == 0) 
                return false;

    
    return !is_win(player);
}

bool Numerical_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

// UI Implementation 

Numerical_UI::Numerical_UI()
    : UI<int>("Hello ,Welcome to the Numerical Tic-Tac-Toe (Sum = 15)", 3) {}

Player<int>* Numerical_UI::create_player(string& name, int symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player: " << name << "\n";
    return new Player<int>(name, symbol, type);
}

Move<int>* Numerical_UI::get_move(Player<int>* player) {
    int x, y, num;
    vector<int> allowed;

    
    if (player->get_symbol() % 2 == 1)
        allowed = { 2, 4, 6, 8 };
    else
        allowed =  { 1, 3, 5, 7, 9 };

    auto matrix = player->get_board_ptr()->get_board_matrix();

    vector<int> used;
    for (auto& row : matrix)
        for (auto val : row)
            if (val != 0)
                used.push_back(val);

    for (int val : used)
        allowed.erase(remove(allowed.begin(), allowed.end(), val), allowed.end());

    if (allowed.empty()) {
        cout << "No numbers left to use!\n";
        return new Move<int>(0, 0, 0);
    }

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn (";
        if (player->get_symbol() % 2 == 1)
            cout << "Even numbers";
        else
            cout << "Odd numbers";
        cout << ")\nAvailable numbers: ";
        for (int n : allowed) cout << n << " ";
        cout << "\nEnter x y and number: ";
        cin >> x >> y >> num;

        if (find(allowed.begin(), allowed.end(), num) == allowed.end()) {
            cout << "Invalid number! Try again.\n";
            return get_move(player);
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        vector<pair<int, int>> empty_cells;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (matrix[i][j] == 0)
                    empty_cells.push_back({ i, j });

        int randIndex = rand() % empty_cells.size();
        x = empty_cells[randIndex].first;
        y = empty_cells[randIndex].second;

        num = allowed[rand() % allowed.size()];

        cout << "\nComputer (" << player->get_name() << ") played: ("
            << x << ", " << y << ") using number " << num << "\n";
    }

    return new Move<int>(x, y, num);
}
