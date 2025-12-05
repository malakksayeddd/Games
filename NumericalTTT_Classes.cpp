/**
 * @file NumericalTTT_Classes.cpp
 * @brief Implementation of the Numerical Tic-Tac-Toe game classes.
 *
 * Contains the implementation of Numerical_Board and Numerical_UI,
 * including the sum-to-15 win condition logic.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "NumericalTTT_Classes.h"
using namespace std;

// ==================== Numerical_Board Implementation ====================

/**
 * @brief Constructs a 3x3 Numerical board with all cells empty (0).
 */
Numerical_Board::Numerical_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

/**
 * @brief Places a number on the board.
 * @param move Pointer to the move containing position and number.
 * @return true if the move was valid, false otherwise.
 */
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

/**
 * @brief Checks if any line sums to exactly 15.
 * 
 * Checks all rows, columns, and diagonals for the sum-to-15 win condition.
 * 
 * @param player Pointer to the player (unused in this check).
 * @return true if any line sums to 15, false otherwise.
 */
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

/**
 * @brief Checks if the game is a draw.
 * @param player Pointer to the player to check.
 * @return true if board is full with no sum-to-15 line, false otherwise.
 */
bool Numerical_Board::is_draw(Player<int>* player) {
    // Check if board has empty cells
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == 0) 
                return false;

    // Board is full - check if there's a winner
    return !is_win(player);
}

/**
 * @brief Checks if the game is over.
 * @param player Pointer to the player to evaluate.
 * @return true if game has ended (win or draw), false otherwise.
 */
bool Numerical_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

// ==================== Numerical_UI Implementation ====================

/**
 * @brief Constructs the Numerical TTT UI.
 *
 * Sets up the title and board size configuration.
 */
Numerical_UI::Numerical_UI()
    : UI<int>("Hello ,Welcome to the Numerical Tic-Tac-Toe (Sum = 15)", 3) {}

/**
 * @brief Creates a player for the Numerical TTT game.
 * @param name Reference to the player's name.
 * @param symbol The player's symbol (determines odd/even numbers).
 * @param type The type of player (Human or Computer).
 * @return Pointer to the created Player object.
 */
Player<int>* Numerical_UI::create_player(string& name, int symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player: " << name << "\n";
    return new Player<int>(name, symbol, type);
}

/**
 * @brief Gets a move from the player.
 * @param player Pointer to the current player.
 * @return Pointer to a Move object with position and number.
 *
 * Player 1 (odd symbol) uses even numbers {2,4,6,8}.
 * Player 2 (even symbol) uses odd numbers {1,3,5,7,9}.
 * For humans: prompts for position and number selection.
 * For computers: randomly selects from available moves.
 */
Move<int>* Numerical_UI::get_move(Player<int>* player) {
    int x, y, num;
    vector<int> allowed;

    // Determine which numbers this player can use
    if (player->get_symbol() % 2 == 1)
        allowed = { 2, 4, 6, 8 };
    else
        allowed =  { 1, 3, 5, 7, 9 };

    auto matrix = player->get_board_ptr()->get_board_matrix();

    // Find which numbers have already been used
    vector<int> used;
    for (auto& row : matrix)
        for (auto val : row)
            if (val != 0)
                used.push_back(val);

    // Remove used numbers from allowed list
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
        // Find empty cells
        vector<pair<int, int>> empty_cells;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (matrix[i][j] == 0)
                    empty_cells.push_back({ i, j });

        // Random cell selection
        int randIndex = rand() % empty_cells.size();
        x = empty_cells[randIndex].first;
        y = empty_cells[randIndex].second;

        // Random number selection
        num = allowed[rand() % allowed.size()];

        cout << "\nComputer (" << player->get_name() << ") played: ("
            << x << ", " << y << ") using number " << num << "\n";
    }

    return new Move<int>(x, y, num);
}
