#include "MenuManager.h"
#include <iostream>
#include <limits>
#include <ctime>
#include "NumericalTTT_Classes.h"
#include "XO_Classes.h"
#include "SUS_Classes.h"
#include "FourInARow_Classes.h"
#include "MisereTTT_Classes.h"

using namespace std;

MenuManager::MenuManager() {
    games = { "X-O (Tic-Tac-Toe)", "Numerical Tic-Tac-Toe", "SUS Game", "Four-in-a-Row", "Misère Tic-Tac-Toe (Inverse XO)",  "Exit" };
    srand(static_cast<unsigned int>(time(0)));
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
            cout << "\n Running SUS Game...\n";
            run_sus_game();
        }
        else if (choice == 4) {
            cout << "\n Running Four-in-a-Row...\n";
            run_four_in_a_row();
        }
       else if (choice == 5) {
    cout << "\n Running Misère Tic-Tac-Toe...\n";
    run_misere_ttt();
       }
else if (choice == 6) {
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

// ---------------- XO Game ----------------
void MenuManager::run_xo_game() {
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

// ---------------- Numerical Tic-Tac-Toe ----------------
void MenuManager::run_numerical_ttt() {
    cout << "\nWelcome to the Numerical Tic-Tac-Toe\n";
    cout << "How to play it:\n";
    cout << "1️: Player 1 uses ODD numbers (1, 3, 5, 7, 9)\n";
    cout << "2️: Player 2 uses EVEN numbers (2, 4, 6, 8)\n";
    cout << "To win make a line (row, column, diagonal) that sums to 15\n\n";

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

// SUS Game 
void MenuManager::run_sus_game() {
    int choice;
    cout << "\n1- Vs Human\n2- Vs AI\n";
    cin >> choice;

    string p1, p2;

    cout << "Enter Player 1 name (S): ";
    cin >> p1;

    if (choice == 1) {
        cout << "Enter Player 2 name (U): ";
        cin >> p2;

        SUS_Game g(p1, p2, false);
        g.play();
    }
    else {
        p2 = "AI";

        SUS_Game g(p1, p2, true);
        g.play();
    }
}

// ---------------- Four-in-a-Row ----------------
void MenuManager::run_four_in_a_row() {
    cout << "\nWelcome to Four-in-a-Row!\n";
    cout << "Instructions:\n";
    cout << "-> Players take turns dropping their mark into a column\n";
    cout << "-> Marks fall to the lowest available position in the column\n";
    cout << "-> First to get 4 in a row (horizontal, vertical, or diagonal) wins!\n\n";

    UI<char>* game_ui = new FourInARow_UI();
    Board<char>* board = new FourInARow_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(board, players, game_ui);
    game.run();

    delete board;
    for (int i = 0; i < 2; ++i)
        delete players[i];
    delete[] players;
    delete game_ui;
    
}


// ---------------- Misère Tic-Tac-Toe ----------------
void MenuManager::run_misere_ttt() {
    // We use the standalone MisereGame class (MisereTTT_Classes.*)
    string p1, p2;
    cout << "Enter Player 1 name (X): ";
    cin >> p1;
    cout << "Enter Player 2 name (O): ";
    cin >> p2;

    MisereGame g(p1, p2);
    g.play();
}
