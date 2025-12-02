#ifndef FOURBYFOUR_AI_H
#define FOURBYFOUR_AI_H
#include "FourByFour_Board.h"

class FourByFour_AI {
public:
    FourByFour_AI(char symbol);

    Move<char>* get_best_move(FourByFour_Board* board);

private:
    char ai_symbol;
    char human_symbol;

    int minimax(FourByFour_Board* board, int depth, bool maximizing);

};

#endif
