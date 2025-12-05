#ifndef MEMORY_TTT_UI_H
#define MEMORY_TTT_UI_H

#include "BoardGame_Classes.h"
#include "MemoryTTT_Board.h"

class MemoryTTT_UI : public UI<char> {
public:
    MemoryTTT_UI();
    virtual ~MemoryTTT_UI() = default;

    virtual Move<char>* get_move(Player<char>* player) override;
    virtual Player<char>** setup_players() override;

    virtual void display_board_matrix(const vector<vector<char>>& matrix) const override;

};



#endif
