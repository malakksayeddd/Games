#include "DiamondTTT.h"
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

DiamondTTT::DiamondTTT() {
    init_board();
    collect_valid_cells();
    build_all_lines();
}

void DiamondTTT::init_board() {
    for (int r = 0; r < 5; ++r)
        for (int c = 0; c < 5; ++c)
            board[r][c] = EMPTY;
}

bool DiamondTTT::is_valid_cell(int r, int c) const {
    if (r < 0 || r > 4 || c < 0 || c > 4) return false;
    return (abs(r - 2) + abs(c - 2)) <= 2;
}

void DiamondTTT::collect_valid_cells() {
    valid_cells.clear();
    for (int r = 0; r < 5; ++r)
        for (int c = 0; c < 5; ++c)
            if (is_valid_cell(r, c)) valid_cells.emplace_back(r, c);
}

void DiamondTTT::build_all_lines() {
    all_lines.clear();

    const vector<pair<int, int>> dirs = { {0,1}, {1,0}, {1,1}, {-1,1} }; // horiz, vert, diag down-right, diag up-right
    for (int dirId = 0; dirId < (int)dirs.size(); ++dirId) {
        int dr = dirs[dirId].first;
        int dc = dirs[dirId].second;

        for (auto& p : valid_cells) {
            int r0 = p.first;
            int c0 = p.second;

            vector<pair<int, int>> run;
            int r = r0, c = c0;
            while (is_valid_cell(r, c)) {
                run.emplace_back(r, c);
                r += dr; c += dc;
            }

           
            if ((int)run.size() >= 3) {
                
                for (size_t s = 0; s < run.size(); ++s) {
                    for (size_t e = s + 3; e <= run.size(); ++e) { 
                        vector<pair<int, int>> seg;
                        for (size_t k = s; k < e; ++k) seg.push_back(run[k]);
                        
                        all_lines.push_back(Line{ seg, dirId });
                    }
                }
            }
        }
    }

  
    auto same_line = [](const Line& a, const Line& b)->bool {
        if (a.direction != b.direction) return false;
        if (a.coords.size() != b.coords.size()) return false;
        for (size_t i = 0; i < a.coords.size(); ++i)
            if (a.coords[i] != b.coords[i]) return false;
        return true;
        };

    vector<Line> unique_lines;
    for (auto& L : all_lines) {
        bool found = false;
        for (auto& U : unique_lines) if (same_line(L, U)) { found = true; break; }
        if (!found) unique_lines.push_back(L);
    }
    all_lines.swap(unique_lines);
}

void DiamondTTT::print_board() const {
    cout << "\nDiamond board (rows 0..4, cols 0..4). Invalid cells shown as space.\n\n";
    cout << "   0 1 2 3 4\n";
    for (int r = 0; r < 5; ++r) {
        cout << r << "  ";
        for (int c = 0; c < 5; ++c) {
            if (!is_valid_cell(r, c)) cout << "  ";
            else cout << static_cast<char>(board[r][c]) << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void DiamondTTT::print_instructions() const {
    cout << "Welcome to Diamond Tic-Tac-Toe!\n";
    cout << "Players alternate placing X and O.\n";
    cout << "Winning condition: the player must simultaneously have a complete line of length 3 AND a complete line of length 4\n";
    cout << "The two lines must be in different directions (horizontal/vertical/diag) and they may share at most one common cell.\n\n";
    cout << "To play: enter row and column separated by space (e.g. `2 1`).\n";
}

bool DiamondTTT::place_mark(int r, int c, Cell mark) {
    if (!is_valid_cell(r, c)) return false;
    if (board[r][c] != EMPTY) return false;
    board[r][c] = mark;
    return true;
}

int DiamondTTT::coord_to_index(int r, int c) const {
    for (size_t i = 0; i < valid_cells.size(); ++i) {
        if (valid_cells[i].first == r && valid_cells[i].second == c) return (int)i;
    }
    return -1;
}

bool DiamondTTT::line_filled_by_player(const Line& L, Cell mark) const {
    for (auto& p : L.coords) {
        if (board[p.first][p.second] != mark) return false;
    }
    return true;
}

bool DiamondTTT::check_player_wins(Cell mark) const {
    vector<const Line*> len3;
    vector<const Line*> len4;

    for (const auto& L : all_lines) {
        if ((int)L.coords.size() == 3) {
            if (line_filled_by_player(L, mark)) len3.push_back(&L);
        }
        else if ((int)L.coords.size() == 4) {
            if (line_filled_by_player(L, mark)) len4.push_back(&L);
        }
    }

    
    if (len3.empty() || len4.empty()) return false;

    
    for (const Line* L3 : len3) {
        for (const Line* L4 : len4) {
            if (L3->direction == L4->direction) continue;
            int overlap = 0;
            for (auto& a : L3->coords) {
                for (auto& b : L4->coords) {
                    if (a == b) ++overlap;
                }
            }
            if (overlap <= 1) return true;
        }
    }
    return false;
}

bool DiamondTTT::parse_position_input(int input, int& out_r, int& out_c) const {
    // المش مستخدمين
    (void)input;
    return false;
}

void DiamondTTT::play() {
    print_instructions();
    print_board();

    Cell current = X;
    int moves = 0;
    const int max_moves = (int)valid_cells.size();

    while (true) {
        cout << "Player " << static_cast<char>(current) << " turn. Enter row and column: ";
        int r, c;
        if (!(cin >> r >> c)) {
           
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter two integers row and column.\n";
            continue;
        }

        if (!is_valid_cell(r, c)) {
            cout << "Invalid cell (not in diamond). Try again.\n";
            continue;
        }
        if (board[r][c] != EMPTY) {
            cout << "Cell already occupied. Try again.\n";
            continue;
        }

        place_mark(r, c, current);
        ++moves;

        print_board();

        if (check_player_wins(current)) {
            cout << "Player " << static_cast<char>(current) << " WINS by completing a length-3 and a length-4 line in different directions!\n";
            break;
        }

        if (moves >= max_moves) {
            cout << "Board full. It's a draw.\n";
            break;
        }

        // switch player
        current = (current == X ? O : X);
    }

    cout << "Game over.\n";
}
