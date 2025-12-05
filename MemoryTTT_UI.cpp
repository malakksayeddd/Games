#include "MemoryTTT_UI.h"
#include "MemoryTTT_Classes.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

MemoryTTT_UI::MemoryTTT_UI()
    : UI<char>("Memory TicTacToe", 3)
{
    srand(time(NULL));
}


Player<char>** MemoryTTT_UI::setup_players() {
    Player<char>** p = new Player<char>*[2];

    cout << "1) Human vs Human\n2) Human vs Computer\n3) Computer vs Computer\nChoose: ";
    int m;
    cin >> m;

    if (m == 1) {
        string a,b;
        cout << "Player 1 name (X): ";
        cin >> a;
        cout << "Player 2 name (O): ";
        cin >> b;
        p[0] = create_memory_human(a,'X');
        p[1] = create_memory_human(b,'O');
    }
    else if (m == 2) {
        string a;
        cout << "Your name (X): ";
        cin >> a;
        p[0] = create_memory_human(a,'X');
        p[1] = create_memory_computer("Computer",'O');
    }
    else {
        p[0] = create_memory_computer("Comp1",'X');
        p[1] = create_memory_computer("Comp2",'O');
    }

    return p;
}

Move<char>* MemoryTTT_UI::get_move(Player<char>* player) {
    MemoryTTT_Board* mb = dynamic_cast<MemoryTTT_Board*>(player->get_board_ptr());

    // computer
    if (player->get_type() == PlayerType::COMPUTER) {
        auto e = mb->empty_cells();
        int k = rand() % e.size();
        int r = e[k].first;
        int c = e[k].second;
        cout << player->get_name() << " chooses: " << r << " " << c << "\n";
        return new Move<char>(r, c, player->get_symbol());
    }

    // human
    while (true) {
        cout << player->get_name() << " (" << player->get_symbol()
             << ") enter row & col (0-2): ";

        int r,c;
        if (!(cin >> r >> c)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid.\n"; continue;
        }

        if (r<0 || r>2 || c<0 || c>2) {
            cout << "Out of range.\n"; continue;
        }

        if (mb->get_board_matrix()[r][c] != '.') {
            cout << "Cell taken.\n"; continue;
        }

        return new Move<char>(r, c, player->get_symbol());
    }
}
void MemoryTTT_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    cout << "    0   1   2\n";
    cout << "  -------------\n";

    for (int i = 0; i < 3; i++) {
        cout << i << " |";
        for (int j = 0; j < 3; j++) {
            cout << " . |";
        }
        cout << "\n  -------------\n";
    }
}
