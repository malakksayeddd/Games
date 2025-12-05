#ifndef MEMORY_TTT_BOARD_H
#define MEMORY_TTT_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>

class MemoryTTT_Board : public Board<char> {
public:
    static const int N = 3;

    MemoryTTT_Board();
    virtual ~MemoryTTT_Board() = default;

    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>*) override;
    virtual bool is_lose(Player<char>*) override;
    virtual bool is_draw(Player<char>*) override;
    virtual bool game_is_over(Player<char>*) override;

    std::vector<std::pair<int,int>> empty_cells() const;

    void display_hidden() const;
    void debug_print_memory() const;

private:
    bool symbol_has_triplet(char symbol) const;
    bool in_range(int r, int c) const { return r>=0 && r<N && c>=0 && c<N; }
};

#endif
