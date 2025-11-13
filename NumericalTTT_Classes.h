#pragma once
#ifndef NUMERICAL_TTT_CLASSES_H
#define NUMERICAL_TTT_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

// Numerical Board 
class Numerical_Board : public Board<int> {
private:
    int blank_symbol = 0; //  cell fadya
public:
    Numerical_Board();

    bool is_lose(Player<int>*) { return false; } //law 5sr
    bool is_draw(Player<int>* player); // law t3adol
    bool game_is_over(Player<int>* player); // nehayet el game
    bool update_board(Move<int>* move); // t7dees elboard kol new move
    bool is_win(Player<int>* player); // law faz
};

// Numerical UI 
class Numerical_UI : public UI<int> {
public:
    Numerical_UI();
    ~Numerical_UI() {}

    Player<int>* create_player(string& name, int symbol, PlayerType type);
    virtual Move<int>* get_move(Player<int>* player);
};

#endif 

