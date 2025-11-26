#ifndef MISERE_TTT_CLASSES_H
#define MISERE_TTT_CLASSES_H

#include <iostream>
#include <string>
using namespace std;

class MisereBoard {
private:
    char board[3][3];

public:
    MisereBoard();
    void display();
    bool is_full();
    bool place_mark(int r, int c, char mark);
    bool makes_three_in_row(char mark); // player y5sr
};

class MisereGame {
private:
    MisereBoard board;
    string p1, p2;
    char turn;   // X aw O

public:
    MisereGame(string p1, string p2);
    void play();
};

#endif
