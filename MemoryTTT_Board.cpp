#include "MemoryTTT_Board.h"
#include <iostream>
using namespace std;

MemoryTTT_Board::MemoryTTT_Board()
    : Board<char>(N, N)
{
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            board[i][j] = '.';
    n_moves = 0;
}

bool MemoryTTT_Board::update_board(Move<char>* move) {
    if (!move) return false;
    int r = move->get_x();
    int c = move->get_y();
    if (!in_range(r,c)) return false;
    if (board[r][c] != '.') return false;

    board[r][c] = move->get_symbol();
    n_moves++;
    return true;
}

bool MemoryTTT_Board::symbol_has_triplet(char s) const {

    for (int r=0;r<N;r++) {
        bool ok=true;
        for (int c=0;c<N;c++)
            if (board[r][c] != s) ok=false;
        if (ok) return true;
    }


    for (int c=0;c<N;c++) {
        bool ok=true;
        for (int r=0;r<N;r++)
            if (board[r][c] != s) ok=false;
        if (ok) return true;
    }


    bool ok=true;
    for (int i=0;i<N;i++)
        if (board[i][i] != s) ok=false;
    if (ok) return true;


    ok=true;
    for (int i=0;i<N;i++)
        if (board[i][N-1-i] != s) ok=false;
    if (ok) return true;

    return false;
}

bool MemoryTTT_Board::is_win(Player<char>* p) {
    return symbol_has_triplet(p->get_symbol());
}

bool MemoryTTT_Board::is_lose(Player<char>* p) {
    char s = p->get_symbol();
    char o = (s=='X' ? 'O' : 'X');
    return symbol_has_triplet(o);
}

bool MemoryTTT_Board::is_draw(Player<char>*) {
    if (n_moves < N*N) return false;
    if (symbol_has_triplet('X') || symbol_has_triplet('O')) return false;
    return true;
}

bool MemoryTTT_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}

vector<pair<int,int>> MemoryTTT_Board::empty_cells() const {
    vector<pair<int,int>> v;
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            if (board[i][j] == '.') v.push_back({i,j});
    return v;
}

void MemoryTTT_Board::display_hidden() const {
    cout << "\n    0   1   2\n";
    cout << "  -------------\n";
    for (int r=0;r<N;r++) {
        cout << r << " | ";
        for (int c=0;c<N;c++)
            cout << ". | ";
        cout << "\n  -------------\n";
    }
}

void MemoryTTT_Board::debug_print_memory() const {
    cout << "\nActual board:\n";
    for (int r=0;r<N;r++) {
        for (int c=0;c<N;c++)
            cout << board[r][c] << " ";
        cout << "\n";
    }
}
