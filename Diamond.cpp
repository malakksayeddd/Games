#include "DiamondTTT.h"
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

/**
 * @brief Constructor initializes the board and precalculates lines.
 */
DiamondTTT::DiamondTTT() : Board<char>(7, 7) {
    init_board();
    collect_valid_cells();
    build_all_lines();
}

/**
 * @brief Fills internal board with '.'.
 */
void DiamondTTT::init_board() {
    for (int r = 0; r < 7; r++)
        for (int c = 0; c < 7; c++)
            board_internal[r][c] = '.';
}

/**
 * @brief Checks if coordinates (r,c) lie inside the diamond shape.
 */
bool DiamondTTT::is_valid_cell(int r, int c) const {
    if (r < 0 || r >= 7 || c < 0 || c >= 7) return false;
    return (abs(r - 3) + abs(c - 3)) <= 3;
}

/**
 * @brief Generates all valid diamond cells.
 */
void DiamondTTT::collect_valid_cells() {
    valid_cells.clear();
    for (int r = 0; r < 7; r++)
        for (int c = 0; c < 7; c++)
            if (is_valid_cell(r, c))
                valid_cells.push_back({ r,c });
}

/**
 * @brief Builds all possible straight lines of length >= 3.
 */
void DiamondTTT::build_all_lines() {
    all_lines.clear();

    vector<pair<int, int>> dirs = { {0,1},{1,0},{1,1},{-1,1} };

    for (auto d : dirs) {
        int dr = d.first, dc = d.second;

        for (auto p : valid_cells) {
            int r = p.first, c = p.second;

            vector<pair<int, int>> run;
            while (is_valid_cell(r, c)) {
                run.push_back({ r,c });
                r += dr;
                c += dc;
            }

            if (run.size() >= 3) {
                for (int s = 0; s < (int)run.size(); s++) {
                    for (int e = s + 3; e <= (int)run.size(); e++) {
                        vector<pair<int, int>> seg(run.begin() + s, run.begin() + e);
                        all_lines.push_back(seg);
                    }
                }
            }
        }
    }

    // Remove duplicates
    vector<vector<pair<int, int>>> uniqueL;
    for (auto& L : all_lines) {
        bool found = false;
        for (auto& U : uniqueL) {
            if (U == L) { found = true; break; }
        }
        if (!found) uniqueL.push_back(L);
    }
    all_lines.swap(uniqueL);
}

/**
 * @brief Prints the diamond board.
 */
void DiamondTTT::print_board() const {
    cout << "\n   0 1 2 3 4 5 6 \n";
    for (int r = 0; r < 7; r++) {
        cout << r << "  ";
        for (int c = 0; c < 7; c++) {
            if (!is_valid_cell(r, c)) cout << "  ";
            else cout << board_internal[r][c] << " ";
        }
        cout << "\n";
    }
}

/**
 * @brief Prints game rules.
 */
void DiamondTTT::print_instructions() const {
    cout << "Diamond TicTacToe: need a line of 3 AND 4 in different directions.\n";
}

/**
 * @brief Places a mark if the cell is empty.
 */
bool DiamondTTT::place_mark(int r, int c, char mark) {
    if (!is_valid_cell(r, c)) return false;
    if (board_internal[r][c] != '.') return false;
    board_internal[r][c] = mark;
    return true;
}

/**
 * @brief Returns true if all cells in line L match 'mark'.
 */
bool DiamondTTT::line_filled(const vector<pair<int, int>>& L, char mark) const {
    for (auto p : L)
        if (board_internal[p.first][p.second] != mark) return false;
    return true;
}

/**
 * @brief Checks if mark has both a line of 3 and a line of 4.
 */
bool DiamondTTT::check_player_wins(char mark) const {
    vector<const vector<pair<int, int>>*> lines3;
    vector<const vector<pair<int, int>>*> lines4;

    for (auto& L : all_lines) {
        if (L.size() == 3 && line_filled(L, mark)) lines3.push_back(&L);
        else if (L.size() == 4 && line_filled(L, mark)) lines4.push_back(&L);
    }

    if (lines3.empty() || lines4.empty()) return false;

    for (auto L3 : lines3) {
        for (auto L4 : lines4) {

            auto d3 = (*L3)[1].first - (*L3)[0].first;
            auto d4 = (*L4)[1].first - (*L4)[0].first;
            auto c3 = (*L3)[1].second - (*L3)[0].second;
            auto c4 = (*L4)[1].second - (*L4)[0].second;

            if (d3 == d4 && c3 == c4) continue;

            int overlap = 0;
            for (auto a : *L3)
                for (auto b : *L4)
                    if (a == b) overlap++;

            if (overlap <= 1) return true;
        }
    }
    return false;
}

/**
 * @brief Main gameplay loop.
 */
void DiamondTTT::play() {
    print_instructions();
    print_board();

    char current = 'X';
    int moves = 0;
    int max_moves = valid_cells.size();

    while (true) {
        cout << "Player " << current << " enter (r c): ";
        int r, c;
        if (!(cin >> r >> c)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (!place_mark(r, c, current)) {
            cout << "Invalid move.\n";
            continue;
        }

        moves++;
        print_board();

        if (check_player_wins(current)) {
            cout << "Player " << current << " WINS!\n";
            return;
        }

        if (moves >= max_moves) {
            cout << "Draw!\n";
            return;
        }

        current = (current == 'X' ? 'O' : 'X');
    }
}

/**
 * @brief Board override: places symbol if valid move.
 */
bool DiamondTTT::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char s = move->get_symbol();

    if (!is_valid_cell(r, c)) return false;
    if (board_internal[r][c] != '.') return false;

    board_internal[r][c] = s;
    board[r][c] = s;
    n_moves++;

    return true;
}

/**
 * @brief Board override: checks win condition.
 */
bool DiamondTTT::is_win(Player<char>* p) {
    char mark = p->get_symbol();
    return check_player_wins(mark);
}

/**
 * @brief DiamondTTT has no lose condition.
 */
bool DiamondTTT::is_lose(Player<char>* p) {
    return false;
}

/**
 * @brief Board override: draw if moves equal valid positions.
 */
bool DiamondTTT::is_draw(Player<char>* p) {
    return n_moves >= (int)valid_cells.size();
}

/**
 * @brief Board override: ends when win or draw occurs.
 */
bool DiamondTTT::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}
