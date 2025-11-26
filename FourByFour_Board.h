#ifndef FOURBYFOUR_BOARD_H
#define FOURBYFOUR_BOARD_H

#include "../BoardGame_Classes.h"

class FourByFour_Board : public Board<char> {
public:
    FourByFour_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

private:
    bool in_bounds(int r, int c);
    bool check_three_in_line(char symbol);
};

#endif
