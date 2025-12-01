#include "PyramidTTT_Classes.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <chrono>
using namespace std;


Pyramid_Board::Pyramid_Board() : Board<char>(3, 5) {

    board = {
        {'#','#','-','#','#'},
        {'#', '-', '-', '-','#'},
        {'-', '-', '-', '-', '-'}
    };
    n_moves = 0;
    build_winning_lines();
}


void Pyramid_Board::build_winning_lines() {
    winning_lines.clear();

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c + 2 < 5; ++c) {
            if (board[r][c] == '#' || board[r][c+1] == '#' || board[r][c+2] == '#') continue;
            winning_lines.push_back({{r,c},{r,c+1},{r,c+2}});
        }
    }


    if (board[0][2] != '#' && board[1][2] != '#' && board[2][2] != '#')
        winning_lines.push_back({{0,2},{1,2},{2,2}});

    // two main diagonals from top-center
    if (board[0][2] != '#' && board[1][1] != '#' && board[2][0] != '#')
        winning_lines.push_back({{0,2},{1,1},{2,0}});
    if (board[0][2] != '#' && board[1][3] != '#' && board[2][4] != '#')
        winning_lines.push_back({{0,2},{1,3},{2,4}});
}

vector<pair<int,int>> Pyramid_Board::get_empty_cells() const {
    vector<pair<int,int>> v;
    for (int r = 0; r < (int)board.size(); ++r)
        for (int c = 0; c < (int)board[r].size(); ++c)
            if (board[r][c] == '-') v.push_back({r,c});
    return v;
}

char Pyramid_Board::get_cell(int r, int c) const {
    if (r < 0 || r >= (int)board.size() || c < 0 || c >= (int)board[r].size()) return '#';
    return board[r][c];
}

bool Pyramid_Board::update_board(Move<char>* m) {
    int r = m->get_x();
    int c = m->get_y();
    char s = m->get_symbol();

    if (r < 0 || r >= (int)board.size() || c < 0 || c >= (int)board[r].size()) return false;
    if (board[r][c] == '#') return false;

    // undo
    if (s == '-') {
        if (board[r][c] != '-') {
            board[r][c] = '-';
            n_moves--;
            return true;
        }
        return false;
    }

    // normal move
    if (board[r][c] != '-') return false;
    board[r][c] = s;
    n_moves++;
    return true;
}

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

bool Pyramid_Board::is_lose(Player<char>* p) {
    char opp = (p->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> tmp("opp", opp, PlayerType::HUMAN);
    return is_win(&tmp);
}

bool Pyramid_Board::is_draw(Player<char>* p) {

    if (!get_empty_cells().empty()) return false;
    return !is_win(p) && !is_lose(p);
}

bool Pyramid_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}

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

Move<char>* Pyramid_AI_Player::get_move() {
    Pyramid_Board* b = dynamic_cast<Pyramid_Board*>(get_board_ptr());
    return minimax_best_move(b, symbol);
}

Move<char>* Pyramid_AI_Player::minimax_best_move(Pyramid_Board* board, char ai_symbol) {
    auto empt = board->get_empty_cells();
    if (empt.empty()) return nullptr;

    int bestScore = std::numeric_limits<int>::min();
    pair<int,int> bestMove = empt[0];

    for (auto cell : empt) {
        Move<char>* m = new Move<char>(cell.first, cell.second, ai_symbol);
        board->update_board(m);

        int score = minimax(board, false, ai_symbol, 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

        // undo
        board->update_board(new Move<char>(cell.first, cell.second, '-'));
        delete m;

        if (score > bestScore) {
            bestScore = score;
            bestMove = cell;
        }
    }

    return new Move<char>(bestMove.first, bestMove.second, ai_symbol);
}

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

            // undo
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

            // undo
            board->update_board(new Move<char>(cell.first, cell.second, '-'));
            delete m;

            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}
