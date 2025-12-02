#ifndef FIVEBYFIVE_CLASSES_H
#define FIVEBYFIVE_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

class FiveByFive_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    FiveByFive_Board();
    
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    int count_three_in_a_row(char sym) const;
    char get_cell(int r, int c) const { return board[r][c]; }
    void set_cell(int r, int c, char val) { board[r][c] = val; }
    void decrement_moves() { n_moves--; }
};

class FiveByFive_UI : public UI<char> {
private:
    FiveByFive_Board* boardPtr;

public:
    FiveByFive_UI();
    void launch();
    void set_board(FiveByFive_Board* b) { boardPtr = b; }
    Move<char>* get_move(Player<char>* player) override;
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};

#endif // FIVEBYFIVE_CLASSES_H
