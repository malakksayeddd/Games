/**
 * @file PyramidTTT_Classes.cpp
 * @brief Implementation of Pyramid Tic-Tac-Toe game classes.
 *
 * Pyramid TTT is played on a pyramid-shaped board:
 * - Row 0: 1 cell (center)
 * - Row 1: 3 cells
 * - Row 2: 5 cells
 * Players win by getting 3 in a row on valid lines.
 */

#include "PyramidTTT_Classes.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <chrono>
using namespace std;

// ==================== Pyramid_Board Implementation ====================

/**
 * @brief Constructs a pyramid-shaped board.
 *
 * Creates a 3x5 grid where '#' marks invalid positions
 * and '-' marks playable empty cells.
 */
Pyramid_Board::Pyramid_Board() : Board<char>(3, 5) {

    board = {
        {'#','#','-','#','#'},
        {'#', '-', '-', '-','#'},
        {'-', '-', '-', '-', '-'}
    };
    n_moves = 0;
    build_winning_lines();
}

/**
 * @brief Builds all valid winning line combinations.
 *
 * Includes horizontal lines, the vertical center column,
 * and diagonal lines from the top center.
 */
void Pyramid_Board::build_winning_lines() {
    winning_lines.clear();

    // Horizontal lines (3 consecutive valid cells)
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c + 2 < 5; ++c) {
            if (board[r][c] == '#' || board[r][c+1] == '#' || board[r][c+2] == '#') continue;
            winning_lines.push_back({{r,c},{r,c+1},{r,c+2}});
        }
    }

    // Vertical center column
    if (board[0][2] != '#' && board[1][2] != '#' && board[2][2] != '#')
        winning_lines.push_back({{0,2},{1,2},{2,2}});

    // Two main diagonals from top-center
    if (board[0][2] != '#' && board[1][1] != '#' && board[2][0] != '#')
        winning_lines.push_back({{0,2},{1,1},{2,0}});
    if (board[0][2] != '#' && board[1][3] != '#' && board[2][4] != '#')
        winning_lines.push_back({{0,2},{1,3},{2,4}});
}

/**
 * @brief Gets all empty playable cell positions.
 * @return Vector of (row, column) pairs for cells marked with '-'.
 */
vector<pair<int,int>> Pyramid_Board::get_empty_cells() const {
    vector<pair<int,int>> v;
    for (int r = 0; r < (int)board.size(); ++r)
        for (int c = 0; c < (int)board[r].size(); ++c)
            if (board[r][c] == '-') v.push_back({r,c});
    return v;
}

/**
 * @brief Gets the character at a cell.
 * @param r Row index.
 * @param c Column index.
 * @return The character at (r, c), or '#' if out of bounds.
 */
char Pyramid_Board::get_cell(int r, int c) const {
    if (r < 0 || r >= (int)board.size() || c < 0 || c >= (int)board[r].size()) return '#';
    return board[r][c];
}

/**
 * @brief Updates the board with a move.
 * @param m Pointer to the move.
 * @return true if successful, false if invalid position.
 *
 * Special handling: symbol '-' is used for undo operations.
 */
bool Pyramid_Board::update_board(Move<char>* m) {
    int r = m->get_x();
    int c = m->get_y();
    char s = m->get_symbol();

    if (r < 0 || r >= (int)board.size() || c < 0 || c >= (int)board[r].size()) return false;
    if (board[r][c] == '#') return false;

    // Undo operation
    if (s == '-') {
        if (board[r][c] != '-') {
            board[r][c] = '-';
            n_moves--;
            return true;
        }
        return false;
    }

    // Normal move
    if (board[r][c] != '-') return false;
    board[r][c] = s;
    n_moves++;
    return true;
}

/**
 * @brief Checks if a player has won.
 * @param p Pointer to the player.
 * @return true if any winning line is complete with player's symbol.
 */
bool Pyramid_Board::is_win(Player<char>* p) {
    char s = p->get_symbol();
    for (auto &line : winning_lines) {
        bool ok = true;
        for (auto &cell : line) {
            int r = cell.first, c = cell.second;
            if (get_cell(r,c) != s) { ok = false; break; }
        }
        if (ok) return true;
    }
    return false;
}

/**
 * @brief Checks if a player has lost (opponent won).
 * @param p Pointer to the player.
 * @return true if the opponent has 3 in a row.
 */
bool Pyramid_Board::is_lose(Player<char>* p) {
    char opp = (p->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> tmp("opp", opp, PlayerType::HUMAN);
    return is_win(&tmp);
}

/**
 * @brief Checks if the game is a draw.
 * @param p Pointer to the player.
 * @return true if no empty cells and no winner.
 */
bool Pyramid_Board::is_draw(Player<char>* p) {

    if (!get_empty_cells().empty()) return false;
    return !is_win(p) && !is_lose(p);
}

/**
 * @brief Checks if the game is over.
 * @param p Pointer to the player.
 * @return true if there's a winner, loser, or draw.
 */
bool Pyramid_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}

// ==================== Pyramid_UI Implementation ====================

/**
 * @brief Gets a move from the player.
 * @param p Pointer to the current player.
 * @return Pointer to a Move object.
 *
 * For AI players, delegates to the minimax algorithm.
 * For human players, prompts for row and column input.
 */
Move<char>* Pyramid_UI::get_move(Player<char>* p) {
    if (p->get_type() == PlayerType::COMPUTER) {
        Pyramid_AI_Player* ai = dynamic_cast<Pyramid_AI_Player*>(p);
        return ai->get_move();
    }

    int r, c;
    cout << p->get_name() << " enter row and col : ";
    cin >> r >> c;
    return new Move<char>(r, c, p->get_symbol());
}

/**
 * @brief Displays the pyramid-shaped board.
 * @param b The board matrix to display.
 *
 * Formats the output with appropriate spacing for the pyramid shape.
 */
void Pyramid_UI::display_board_matrix(const vector<vector<char>>& b) const {
    cout << "\nPyramid Board:\n";
    for (int r = 0; r < (int)b.size(); ++r) {

        cout << string(2 - r, ' ');
        for (int c = 0; c < (int)b[r].size(); ++c) {
            if (b[r][c] == '#') cout << "  ";
            else cout << b[r][c] << ' ';
        }
        cout << '\n';
    }
    cout << endl;
}

/**
 * @brief Sets up the two players.
 * @return Array of pointers to the two Player objects.
 *
 * Prompts for player names and type (Human or Computer).
 */
Player<char>** Pyramid_UI::setup_players() {
    Player<char>** arr = new Player<char>*[2];
    for (int i = 0; i < 2; ++i) {
        string name;
        int choice = 0;
        char sym = (i==0) ? 'X' : 'O';
        cout << "Enter player " << sym << " name: ";
        cin >> name;

        while (choice != 1 && choice != 2) {
            cout << "Choose type for " << name << ":\n1. Human\n2. Computer (Smart)\nChoice: ";
            cin >> choice;
        }

        if (choice == 1) arr[i] = new Player<char>(name, sym, PlayerType::HUMAN);
        else arr[i] = new Pyramid_AI_Player(name, sym);
    }
    return arr;
}

// ==================== Pyramid_AI_Player Implementation ====================

/**
 * @brief Gets the best move using minimax algorithm.
 * @return Pointer to the optimal Move object.
 */
Move<char>* Pyramid_AI_Player::get_move() {
    Pyramid_Board* b = dynamic_cast<Pyramid_Board*>(get_board_ptr());
    return minimax_best_move(b, symbol);
}

/**
 * @brief Finds the best move using minimax search.
 * @param board Pointer to the game board.
 * @param ai_symbol The AI player's symbol.
 * @return Pointer to the best Move object found.
 *
 * Evaluates all possible moves and returns the one with highest score.
 */
Move<char>* Pyramid_AI_Player::minimax_best_move(Pyramid_Board* board, char ai_symbol) {
    auto empt = board->get_empty_cells();
    if (empt.empty()) return nullptr;

    int bestScore = std::numeric_limits<int>::min();
    pair<int,int> bestMove = empt[0];

    for (auto cell : empt) {
        Move<char>* m = new Move<char>(cell.first, cell.second, ai_symbol);
        board->update_board(m);

        int score = minimax(board, false, ai_symbol, 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

        // Undo the move
        board->update_board(new Move<char>(cell.first, cell.second, '-'));
        delete m;

        if (score > bestScore) {
            bestScore = score;
            bestMove = cell;
        }
    }

    return new Move<char>(bestMove.first, bestMove.second, ai_symbol);
}

/**
 * @brief Minimax algorithm with alpha-beta pruning.
 * @param board Pointer to the game board.
 * @param maximizingPlayer true if it's the AI's turn.
 * @param ai_symbol The AI player's symbol.
 * @param depth Current search depth.
 * @param alpha Alpha value for pruning.
 * @param beta Beta value for pruning.
 * @return The evaluation score for the position.
 *
 * Returns positive scores for AI wins, negative for losses,
 * with depth adjustment to prefer quicker wins.
 */
int Pyramid_AI_Player::minimax(Pyramid_Board* board, bool maximizingPlayer, char ai_symbol, int depth, int alpha, int beta) {

    Player<char> aiTmp("AI", ai_symbol, PlayerType::COMPUTER);
    char human_symbol = (ai_symbol == 'X') ? 'O' : 'X';
    Player<char> huTmp("H", human_symbol, PlayerType::HUMAN);

    if (board->is_win(&aiTmp)) return 100 - depth;
    if (board->is_win(&huTmp)) return -100 + depth;
    if (board->get_empty_cells().empty()) return 0;

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        auto empt = board->get_empty_cells();
        for (auto cell : empt) {
            Move<char>* m = new Move<char>(cell.first, cell.second, ai_symbol);
            board->update_board(m);

            int eval = minimax(board, false, ai_symbol, depth+1, alpha, beta);

            // Undo the move
            board->update_board(new Move<char>(cell.first, cell.second, '-'));
            delete m;

            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) break;
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        auto empt = board->get_empty_cells();
        for (auto cell : empt) {
            Move<char>* m = new Move<char>(cell.first, cell.second, human_symbol);
            board->update_board(m);

            int eval = minimax(board, true, ai_symbol, depth+1, alpha, beta);

            // Undo the move
            board->update_board(new Move<char>(cell.first, cell.second, '-'));
            delete m;

            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}
