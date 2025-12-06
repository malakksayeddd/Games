/**
 * @file FourByFour_UI.cpp
 * @brief Implementation of the User Interface for 4x4 Tic-Tac-Toe.
 */

#include "FourByFour_UI.h"
#include "FourByFour_AI.h"
#include "FourByFour_Board.h"
#include <iostream>

using namespace std;

/**
 * @brief Constructs the 4x4 Tic-Tac-Toe UI.
 */
FourByFour_UI::FourByFour_UI()
    : UI("Welcome to 4x4 Tic-Tac-Toe!", 3)
{}

/**
 * @brief Creates a player with the specified name, symbol, and type.
 * @param name Name of the player.
 * @param symbol The player's symbol ('X' or 'O').
 * @param t The type of player (Human or Computer).
 * @return Pointer to the newly created Player object.
 */
Player<char>* FourByFour_UI::create_player(string& name, char symbol, PlayerType t) {
    cout << "Creating player " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, t);
}

/**
 * @brief Gets a move from the player.
 * 
 * For computer players, uses the AI to find the optimal move.
 * For human players, prompts for source and destination coordinates.
 * 
 * @param player Pointer to the current player.
 * @return Pointer to the Move object containing move information.
 */
Move<char>* FourByFour_UI::get_move(Player<char>* player) {

    cout << player->get_name() << " (" << player->get_symbol() << ") move\n";


    if (player->get_type() == PlayerType::COMPUTER) {
        FourByFour_AI ai(player->get_symbol());
        return ai.get_best_move((FourByFour_Board*)player->get_board_ptr());
    }

    int x, y, nx, ny;

    cout << "From (row col): ";
    cin >> x >> y;

    cout << "To (row col): ";
    cin >> nx >> ny;

    return new FourByFour_Move(x, y, nx, ny, player->get_symbol());
}

