#pragma once
#include "BoardGame_Classes.h"
#include <set>
#include <string>
#include <vector>
#include <algorithm>

class WordTTT_Board : public Board<char> { //inherte from board char
    std::set<std::string> dictionary; //dic.txt

public:
    WordTTT_Board(); //constractour
    void load_dictionary(const std::string& path);
    bool is_valid_word(const std::string& w) const;
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>*) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>*) override;
    bool game_is_over(Player<char>*) override;
    std::vector<std::pair<int, int>> get_empty_cells() const;
    const std::set<std::string>& get_dictionary() const { return dictionary; }

   
    
    char get_cell(int r, int c) const { return board[r][c]; }
    void set_cell(int r, int c, char value) { board[r][c] = value; }
};

class WordTTT_Move : public Move<char> { //inherte mn move
public:
    WordTTT_Move(int r, int c, char s) : Move<char>(r, c, s) {}
};

class WordTTT_UI : public UI<char> { //inherte mn ui
public:
    WordTTT_UI() {}

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};
