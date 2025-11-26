#pragma once
#ifndef INFINITY_TTT_CLASSES_H
#define INFINITY_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <queue>
#include <utility>

const char blanksymbol = '_';

//Board 
class Infinity_Board : public Board<char> {
private:
    std::queue<std::pair<int, int>> historyX;
    std::queue<std::pair<int, int>> historyO;

public:
    Infinity_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override { return false; }
    bool game_is_over(Player<char>* player);
    bool is_win_symbol(char s);

    void process_player_history(char s);
};

//UI 
class Infinity_UI : public UI<char> {
public:
    Infinity_UI();
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif
