#ifndef ULTIMATETTT_CLASSES_H
#define ULTIMATETTT_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

class Ultimate_Board : public Board<char> {
private:
    char subBoards[3][3][3][3];  // [subRow][subCol][cellRow][cellCol]
    char mainBoard[3][3];         // Tracking winners of each sub-board ('X', 'O', '#'=draw, '.'=open)
    int currentSubRow, currentSubCol;  // The Current active sub-board (-1 = none (open to choose))
    
    bool check_three(char a, char b, char c, char sym) const;
    bool check_sub_winner(int sr, int sc, char sym) const;
    bool is_sub_full(int sr, int sc) const;
    
public:
    Ultimate_Board();
    
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    
    char get_sub_cell(int sr, int sc, int cr, int cc) const { return subBoards[sr][sc][cr][cc]; }
    char get_main_cell(int r, int c) const { return mainBoard[r][c]; }
    bool is_sub_completed(int sr, int sc) const { return mainBoard[sr][sc] != '.'; }
    int get_current_sub_row() const { return currentSubRow; }
    int get_current_sub_col() const { return currentSubCol; }
    void set_current_sub(int r, int c) { currentSubRow = r; currentSubCol = c; }
};

class Ultimate_UI : public UI<char> {
private:
    Ultimate_Board* boardPtr;

public:
    Ultimate_UI();
    void set_board(Ultimate_Board* b) { boardPtr = b; }
    
    Move<char>* get_move(Player<char>* player) override;
    void display_board() const;
    // Override to prevent base class from showing 9x9 nonsense board
    void display_board_matrix(const vector<vector<char>>& matrix) const override { display_board(); }
    void launch();
};

#endif // ULTIMATETTT_CLASSES_H
