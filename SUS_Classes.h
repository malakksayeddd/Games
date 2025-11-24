#pragma once
#include <iostream>
#include <utility>
#include <string>
using namespace std;

class SUS_Board {
private:
    char board[3][3];
    int sequences;

public:
    SUS_Board();

    bool place(int r, int c, char symbol);
    void undo(int r, int c);
    char getCell(int r, int c);

    int countSequences();
    int getSequences();
    void setSequences(int s);

    bool full();
    void display();
};

class SUS_Game {
private:
    SUS_Board board;
    int scoreP1;
    int scoreP2;
    bool turnP1;
    bool vsAI;

    string player1;
    string player2;

    pair<int, int> bestMove();   // AI logic

public:
    SUS_Game(string name1, string name2, bool ai);
    void play();
};
