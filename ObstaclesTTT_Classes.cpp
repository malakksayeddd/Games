/**
 * @file ObstaclesTTT_Classes.cpp
 * @brief Implementation of Obstacles Tic-Tac-Toe game classes.
 *
 * Obstacles TTT is played on a 6x6 board where players aim to get 4 in a row.
 * After each complete round (both players move), 2 random obstacles are added
 * to the board, making the game progressively more challenging.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "ObstaclesTTT_Classes.h"

using namespace std;

// ==================== Obstacles_Board Implementation ====================

/**
 * @brief Constructs an empty 6x6 Obstacles board.
 *
 * Initializes all cells to blank ('_').
 */
Obstacles_Board::Obstacles_Board() : Board<char>(6, 6) {
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_symbol;
        }
    }
}

/**
 * @brief Checks if a specific cell is empty.
 * @param x Row index (0-5).
 * @param y Column index (0-5).
 * @return true if the cell is blank, false otherwise.
 */
bool Obstacles_Board::is_cell_empty(int x, int y) const {
    if (x < 0 || x >= rows || y < 0 || y >= columns) return false;
    return board[x][y] == blank_symbol;
}

/**
 * @brief Gets all empty cell positions on the board.
 * @return Vector of (row, column) pairs for blank cells.
 */
vector<pair<int, int>> Obstacles_Board::get_empty_cells() const {
    vector<pair<int, int>> empty_cells;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == blank_symbol) {
                empty_cells.push_back({i, j});
            }
        }
    }
    return empty_cells;
}

/**
 * @brief Updates the board with a player's move.
 * @param move Pointer to the move containing position and symbol.
 * @return true if the move is valid and applied, false otherwise.
 *
 * After every 2 moves (one round), adds 2 random obstacles to the board.
 */
bool Obstacles_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }

    if (board[x][y] != blank_symbol) {
        return false;
    }

    board[x][y] = symbol;
    n_moves++;

    if (n_moves % 2 == 0 && n_moves > 0) {
        cout << "\n>>> Round " << (n_moves / 2) << " complete! Adding 2 random obstacles... <<<\n";
        add_random_obstacles();
    }

    return true;
}

/**
 * @brief Adds 2 random obstacles to empty cells.
 *
 * Selects up to 2 random empty cells and places obstacle symbols ('#').
 */
void Obstacles_Board::add_random_obstacles() {
    vector<pair<int, int>> empty_cells = get_empty_cells();
    
    int obstacles_to_add = min(2, static_cast<int>(empty_cells.size()));
    
    for (int i = 0; i < obstacles_to_add; ++i) {
        if (empty_cells.empty()) break;
        
        int random_index = rand() % empty_cells.size();
        int x = empty_cells[random_index].first;
        int y = empty_cells[random_index].second;
        
        board[x][y] = obstacle_symbol;
        
        empty_cells.erase(empty_cells.begin() + random_index);
    }
}

/**
 * @brief Checks if a symbol has won (4 in a row).
 * @param sym The symbol to check ('X' or 'O').
 * @return true if 4 consecutive symbols found, false otherwise.
 *
 * Checks all horizontal, vertical, and diagonal lines.
 */
bool Obstacles_Board::has_symbol_won(char sym) {
    // Check horizontal (4 in a row)
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c <= columns - 4; ++c) {
            if (board[r][c] == sym && board[r][c + 1] == sym &&
                board[r][c + 2] == sym && board[r][c + 3] == sym) {
                return true;
            }
        }
    }

    // Check vertical (4 in a column)
    for (int c = 0; c < columns; ++c) {
        for (int r = 0; r <= rows - 4; ++r) {
            if (board[r][c] == sym && board[r + 1][c] == sym &&
                board[r + 2][c] == sym && board[r + 3][c] == sym) {
                return true;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int r = 0; r <= rows - 4; ++r) {
        for (int c = 0; c <= columns - 4; ++c) {
            if (board[r][c] == sym && board[r + 1][c + 1] == sym &&
                board[r + 2][c + 2] == sym && board[r + 3][c + 3] == sym) {
                return true;
            }
        }
    }

    // Check diagonal (bottom-left to top-right)
    for (int r = 3; r < rows; ++r) {
        for (int c = 0; c <= columns - 4; ++c) {
            if (board[r][c] == sym && board[r - 1][c + 1] == sym &&
                board[r - 2][c + 2] == sym && board[r - 3][c + 3] == sym) {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Checks if a player has won.
 * @param player Pointer to the player to check.
 * @return true if the player has 4 in a row.
 */
bool Obstacles_Board::is_win(Player<char>* player) {
    return has_symbol_won(player->get_symbol());
}

/**
 * @brief Checks if the game is a draw.
 * @param player Pointer to the player to check against.
 * @return true if no empty cells and no winner.
 */
bool Obstacles_Board::is_draw(Player<char>* player) {
    vector<pair<int, int>> empty_cells = get_empty_cells();
    return empty_cells.empty() && !is_win(player);
}

/**
 * @brief Checks if the game is over.
 * @param player Pointer to the player to evaluate.
 * @return true if there's a winner or draw.
 */
bool Obstacles_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// ==================== Obstacles_ComputerPlayer Implementation ====================

/**
 * @brief Constructs a computer player for Obstacles TTT.
 * @param name The player's name.
 * @param symbol The player's symbol ('X' or 'O').
 */
Obstacles_ComputerPlayer::Obstacles_ComputerPlayer(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::COMPUTER) {}

/**
 * @brief Gets a random valid move for the computer.
 * @return Pointer to a Move object with a random empty cell position.
 */
Move<char>* Obstacles_ComputerPlayer::get_random_move() {
    Obstacles_Board* board = dynamic_cast<Obstacles_Board*>(boardPtr);
    if (!board) return nullptr;

    vector<pair<int, int>> empty_cells = board->get_empty_cells();
    if (empty_cells.empty()) return nullptr;

    int random_index = rand() % empty_cells.size();
    int x = empty_cells[random_index].first;
    int y = empty_cells[random_index].second;

    return new Move<char>(x, y, symbol);
}

// ==================== Obstacles_UI Implementation ====================

/**
 * @brief Constructs the Obstacles TTT UI.
 */
Obstacles_UI::Obstacles_UI() : UI<char>("===== OBSTACLES TIC-TAC-TOE =====", 3), currentBoard(nullptr) {}

/**
 * @brief Creates a player for the game.
 * @param name Reference to the player's name.
 * @param symbol The player's symbol.
 * @param type The type of player (Human or Computer).
 * @return Pointer to the created Player object.
 */
Player<char>* Obstacles_UI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER) {
        cout << "Creating computer player: " << name << " (" << symbol << ")\n";
        return new Obstacles_ComputerPlayer(name, symbol);
    } else {
        cout << "Creating human player: " << name << " (" << symbol << ")\n";
        return new Player<char>(name, symbol, type);
    }
}

/**
 * @brief Gets a move from the player.
 * @param player Pointer to the current player.
 * @return Pointer to the Move object.
 *
 * For computer players, generates a random move.
 * For human players, prompts for row and column input.
 */
Move<char>* Obstacles_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::COMPUTER) {
        Obstacles_ComputerPlayer* randomPlayer = dynamic_cast<Obstacles_ComputerPlayer*>(player);
        if (randomPlayer) {
            cout << player->get_name() << " (" << player->get_symbol() << ") is thinking...\n";
            Move<char>* move = randomPlayer->get_random_move();
            if (move) {
                cout << player->get_name() << " plays at (" << move->get_x() << ", " << move->get_y() << ")\n";
            }
            return move;
        }
    }

    int x, y;
    cout << "\n" << player->get_name() << " (" << player->get_symbol() << "), enter your move (row column): ";
    cin >> x >> y;

    return new Move<char>(x, y, player->get_symbol());
}

/**
 * @brief Launches the Obstacles TTT game.
 *
 * Displays instructions, creates the board and players,
 * and runs the game loop.
 */
void Obstacles_UI::launch() {
    srand(static_cast<unsigned int>(time(0)));
    cout << "\nWelcome to Obstacles Tic-Tac-Toe!\n";
    cout << "Instructions:\n";
    cout << "-> 6x6 grid where you must get 4 in a row to win\n";
    cout << "-> After each round (both players move), 2 random obstacle cells (#) are added\n";
    cout << "-> You cannot place your mark on obstacles\n\n";

    Obstacles_UI* game_ui = new Obstacles_UI();
    Obstacles_Board* board = new Obstacles_Board();
    game_ui->set_board(board);
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(board, players, game_ui);
    game.run();

    delete board;
    for (int i = 0; i < 2; ++i)
        delete players[i];
    delete[] players;
    delete game_ui;
}
