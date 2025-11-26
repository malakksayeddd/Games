#ifndef FOURBYFOUR_UI_H
#define FOURBYFOUR_UI_H

#include "../BoardGame_Classes.h"

class FourByFour_UI : public UI<char> {
public:
    FourByFour_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType t) override;
};

#endif
