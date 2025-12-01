#ifndef PYRAMID_TTT_CLASSES_H
#define PYRAMID_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
using namespace std;


class Pyramid_Board : public Board<char> {
public:
    Pyramid_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;

    vector<pair<int,int>> get_empty_cells() const;
    char get_cell(int r,int c) const;

private:
    vector<vector<pair<int,int>>> winning_lines;
    void build_winning_lines();
};


class Pyramid_UI : public UI<char> {
public:
    Pyramid_UI() : UI<char>(3) {}

    Move<char>* get_move(Player<char>* p) override;
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
    Player<char>** setup_players() override;
};


class Pyramid_AI_Player : public Player<char> {
public:
    Pyramid_AI_Player(string n, char s)
        : Player<char>(n, s, PlayerType::COMPUTER) {}

    Move<char>* get_move();

private:
    Move<char>* minimax_best_move(Pyramid_Board* board, char ai_symbol);
    int minimax(Pyramid_Board* board, bool maximizingPlayer, char ai_symbol, int depth, int alpha, int beta);
};

#endif
