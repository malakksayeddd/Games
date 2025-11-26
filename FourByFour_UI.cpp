#include "FourByFour_UI.h"
#include <iostream>

using namespace std;

FourByFour_UI::FourByFour_UI()
    : UI("Welcome to 4x4 Tic-Tac-Toe!", 3)
{}

Player<char>* FourByFour_UI::create_player(string& name, char symbol, PlayerType t) {
    cout << "Creating player " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, t);
}

Move<char>* FourByFour_UI::get_move(Player<char>* player) {
    int x, y, nx, ny;

    cout << player->get_name() << " (" << player->get_symbol() << ") move\n";

    cout << "From (row col): ";
    cin >> x >> y;

    cout << "To (row col): ";
    cin >> nx >> ny;

    return new Move<char>(x, y, nx, ny, player->get_symbol());
}
