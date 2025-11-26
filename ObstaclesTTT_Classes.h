#ifndef OBSTACLESTTT_CLASSES_H
#define OBSTACLESTTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
using namespace std;

class Obstacles_Board : public Board<char> {
private:
    char blank_symbol = '.';      // empty cells
    char obstacle_symbol = '#';   // for obstacle cells

public:

    Obstacles_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool has_symbol_won(char sym);
    void add_random_obstacles();
    char get_blank_symbol() const { return blank_symbol; }
    char get_obstacle_symbol() const { return obstacle_symbol; }
    bool is_cell_empty(int x, int y) const;

    vector<pair<int, int>> get_empty_cells() const;
};

class Obstacles_ComputerPlayer : public Player<char> {
public:
    Obstacles_ComputerPlayer(string name, char symbol);
    Move<char>* get_random_move();
};

class Obstacles_UI : public UI<char> {
private:
    Obstacles_Board* currentBoard;

public:

    Obstacles_UI();
    ~Obstacles_UI() {}

    void set_board(Obstacles_Board* b) { currentBoard = b; }

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;

    void launch();
};

#endif
