#ifndef FOURINAROW_CLASSES_H
#define FOURINAROW_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;


class FourInARow_Board : public Board<char> {
private:
    char blank_symbol = '.'; 

public:

    FourInARow_Board();

    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* ) { return false; };
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    int get_lowest_row(int col);
    bool has_symbol_won(char sym);
};

class FourInARow_UI : public UI<char> {
private:
    FourInARow_Board* currentBoard;
    int player_difficulty[2];
    
public:
    FourInARow_UI();
    ~FourInARow_UI() {};
    void set_player_difficulty(int player_index, int difficulty) { player_difficulty[player_index] = difficulty; }

    void set_board(FourInARow_Board* b) { currentBoard = b; }
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    Player<char>** setup_players();
    virtual PlayerType get_player_type_choice(string player_label, const vector<string>& options);
    virtual Move<char>* get_move(Player<char>* player);
    void launch();
};

#endif // FOURINAROW_CLASSES_H
