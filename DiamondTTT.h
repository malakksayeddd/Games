#ifndef DIAMOND_TTT_H
#define DIAMOND_TTT_H

#include <vector>
#include <utility>
#include <string>

class DiamondTTT {
public:
    DiamondTTT();
    void play();

private:
 
    enum Cell { EMPTY = '.', X = 'X', O = 'O' };
    Cell board[5][5];

    
    std::vector<std::pair<int, int>> valid_cells;

    struct Line { std::vector<std::pair<int, int>> coords; int direction; };
    std::vector<Line> all_lines;

    void init_board();
    void collect_valid_cells();
    void build_all_lines();
    void print_board() const;
    void print_instructions() const;
    int coord_to_index(int r, int c) const;
    bool is_valid_cell(int r, int c) const;
    bool place_mark(int r, int c, Cell mark);
    bool check_player_wins(Cell mark) const;
    bool line_filled_by_player(const Line& L, Cell mark) const;
    bool parse_position_input(int input, int& out_r, int& out_c) const;
};

#endif // DIAMOND_TTT_H
