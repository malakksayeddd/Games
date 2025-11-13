#include "MenuManager.h"
#include <iostream>
#include <limits>
#include <ctime>
#include "NumericalTTT_Classes.h"
#include "XO_Classes.h"



using namespace std;

MenuManager::MenuManager() {
    games = { "X-O (Tic-Tac-Toe)", "Numerical Tic-Tac-Toe", "Exit" }; 
}

void MenuManager::run() {
    while (true) {
        display_menu();
        int choice = get_choice();

        if (choice == 1) {
            cout << "\n Running Classic X-O Game...\n";
            run_xo_game();
        }
        else if (choice == 2) {
            cout << "\n Running Numerical Tic-Tac-Toe...\n";
            run_numerical_ttt();
        }
        else if (choice == 3) {
            cout << "\n Exiting the program. Goodbye!\n";
            break;
        }
        else {
            cout << " Invalid choice. Please try again.\n";
        }
    }
}

void MenuManager::display_menu() {
    cout << "\n The Game Menu\n";
    for (size_t i = 0; i < games.size(); ++i) {
        cout << i + 1 << ". " << games[i] << "\n";
    }
    cout << "Select a game: ";
}

int MenuManager::get_choice() {
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

//  XO Game
void MenuManager::run_xo_game() {
    srand(static_cast<unsigned int>(time(0)));

    UI<char>* game_ui = new XO_UI();
    Board<char>* xo_board = new X_O_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> x_o_game(xo_board, players, game_ui);
    x_o_game.run();

    delete xo_board;
    for (int i = 0; i < 2; ++i)
        delete players[i];
    delete[] players;
}

//  Numerical Tic-Tac-Toe Game
void MenuManager::run_numerical_ttt() {
    cout << "\nWelcome to the Numerical Tic-Tac-Toe\n";
    cout << "How to play it:\n";
    cout << "1️: Player 1 uses ODD numbers (1, 3, 5, 7, 9)\n";
    cout << "2️: Player 2 uses EVEN numbers (2, 4, 6, 8)\n";
    cout << " To win make a line (row, column, diagonal) that sums to 15\n\n";

    void run_numerical_game(); {
        srand(static_cast<unsigned int>(time(0)));

        UI<int>* game_ui = new Numerical_UI();
        Board<int>* num_board = new Numerical_Board();
        Player<int>** players = game_ui->setup_players();

        GameManager<int> game(num_board, players, game_ui);
        game.run();

        delete num_board;
        for (int i = 0; i < 2; ++i)
            delete players[i];
        delete[] players;
    }







}

