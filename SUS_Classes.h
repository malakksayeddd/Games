#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
#include <utility>
using namespace std;

class SUS_Board : public Board<char> {
private:
    int sequences;

    static bool seq(char a, char b, char c) {
        return (a == 'S' && b == 'U' && c == 'S');
    }

public:
    SUS_Board();

    
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;

   
    bool place(int r, int c, char sym);
    void undo(int r, int c);
    char getCell(int r, int c);
    int countSequences();
    int getSequences() const;
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

    pair<int, int> bestMove();

public:
    SUS_Game(string name1, string name2, bool ai);
    void play();
};
