/**
 * @file MenuManager.cpp
 * @brief Implementation of the game menu management system.
 *
 * Provides a central menu interface for launching all available
 * board game variants in the MiniBoards collection.
 */

#include "MenuManager.h"
#include <iostream>
#include <limits>
#include <ctime>
#include "NumericalTTT_Classes.h"
#include "XO_Classes.h"
#include "SUS_Classes.h"
#include "FourInARow_Classes.h"
#include "MisereTTT_Classes.h"
#include "InfinityTTT_Classes.h"
#include "ObstaclesTTT_Classes.h"
#include "FiveByFiveTTT_Classes.h"
#include "WordTTT_Classes.h"
#include "UltimateTTT_Classes.h"
#include "DiamondTTT.h"
#include "MemoryTTT_Board.h"
#include "MemoryTTT_UI.h"
using namespace std;

/**
 * @brief Constructs the MenuManager and initializes the game list.
 *
 * Sets up the list of available games and seeds the random number generator.
 */
MenuManager::MenuManager() {
    games = { "X-O (Tic-Tac-Toe)", "Numerical Tic-Tac-Toe", "SUS Game", "Four-in-a-Row", "Misère Tic-Tac-Toe (Inverse XO)"
        , "Infinity Tic-Tac-Toe", "Obstacles Tic-Tac-Toe", "4x4 Tic-Tac-Toe", "5x5 Tic-Tac-Toe","Word  Tic-Tac-Toe", "Pyramid Tic-Tac-Toe", "Ultimate Tic-Tac-Toe",
        "Diamond Tic-Tac-Toe", "Memory Tic-Tac-Toe", "Exit" };
    srand(static_cast<unsigned int>(time(0)));
}

/**
 * @brief Main loop for the menu system.
 *
 * Displays the menu and processes user selections until exit is chosen.
 * Routes to the appropriate game launcher based on user choice.
 */
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
    cout << "\n Running Misere Tic-Tac-Toe...\n";
    run_misere_ttt();
       }
        else if (choice == 6) {
            cout << "\n Running Infinity Tic-Tac-Toe Game...\n";
            run_infinity_ttt();
        }
        else if (choice == 7) {
            cout << "\n Running Obstacles Tic-Tac-Toe...\n";
            run_obstacles_ttt();
        }
        else if (choice == 8) {
            cout << "\n Running 4x4 Tic-Tac-Toe...\n";
            run_four_by_four();
        }
        else if (choice == 9) {
            cout << "\n Running 5x5 Tic-Tac-Toe...\n";
            run_five_by_five();
        }
    else if (choice == 10) {
    cout << "\n Running Word Tic-Tac-Toe...\n";
    run_word_ttt();   
       }

      else if (choice ==11) {
            cout << "\n Running Pyramid Tic-Tac-Toe...\n";
            run_pyramid();
        }
        else if (choice == 12) {
            cout << "\n Running Ultimate Tic-Tac-Toe...\n";
            run_ultimate_ttt();
        }
            else if (choice == 13) { 
    cout << "\n Running Diamond Tic-Tac-Toe...\n";
    run_DiamondTTT() ;
    
}
            else if (choice == 14) {
            run_memory_ttt();
        }
        else if (choice == 15) {
            cout << "\n Exiting the program. Goodbye!\n";
            break;
        }
        else {
            cout << " Invalid choice. Please try again.\n";
        }
    }
}

/**
 * @brief Displays the main menu with all available games.
 *
 * Prints a numbered list of all game options.
 */
void MenuManager::display_menu() {
    cout << "\n The Game Menu\n";
    for (size_t i = 0; i < games.size(); ++i) {
        cout << i + 1 << ". " << games[i] << "\n";
    }
    cout << "Select a game: ";
}

/**
 * @brief Gets the user's menu choice.
 * @return The integer choice entered by the user.
 */
int MenuManager::get_choice() {
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

// ---------------- XO Game ----------------

/**
 * @brief Launches the classic Tic-Tac-Toe (X-O) game.
 *
 * Creates the board, UI, and players, then runs the game loop.
 */
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

/**
 * @brief Launches the Numerical Tic-Tac-Toe game.
 *
 * Player 1 uses odd numbers (1,3,5,7,9), Player 2 uses even (2,4,6,8).
 * Goal is to make a line summing to 15.
 */
void MenuManager::run_numerical_ttt() {
    cout << "\nWelcome to the Numerical Tic-Tac-Toe\n";
    cout << "How to play it:\n";
    cout << "1: Player 1 uses ODD numbers (1, 3, 5, 7, 9)\n";
    cout << "2: Player 2 uses EVEN numbers (2, 4, 6, 8)\n";
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

// ---------------- SUS Game ----------------

/**
 * @brief Launches the SUS game.
 *
 * Players take turns placing 'S' or 'U' and score points for each
 * "SUS" sequence formed. Supports human vs human or human vs AI.
 */
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

/**
 * @brief Launches the Four-in-a-Row (Connect Four) game.
 *
 * Played on a 6x7 board where pieces fall with gravity.
 * First to get 4 in a line wins.
 */
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

/**
 * @brief Launches the Misère (Inverse) Tic-Tac-Toe game.
 *
 * The player who gets 3 in a row LOSES instead of winning.
 */
void MenuManager::run_misere_ttt() {
    string p1, p2;
    cout << "Enter Player 1 name (X): ";
    cin >> p1;
    cout << "Enter Player 2 name (O): ";
    cin >> p2;

    MisereGame g(p1, p2);
    g.play();
}

// ---------------- Infinity TTT ----------------

/**
 * @brief Launches the Infinity Tic-Tac-Toe game.
 *
 * Each player can only have 3 marks on the board at a time.
 * When placing a 4th mark, the oldest mark is automatically removed.
 */
void MenuManager::run_infinity_ttt()
{
    cout << "\n=== Infinity Tic Tac Toe ===\n";
    cout << "Each player has ONLY 3 marks. Oldest mark is removed.\n";

    Infinity_UI* ui = new Infinity_UI();
    Infinity_Board* board = new Infinity_Board();

    string n1 = "Player X";
    string n2;

    int choice;
    cout << "Choose opponent:\n1) Human\n2) Computer\nYour choice: ";
    cin >> choice;

    Player<char>* p1 = ui->create_player(n1, 'X', PlayerType::HUMAN);

    Player<char>* p2;
    if (choice == 1)
    {
        n2 = "Player O";
        p2 = ui->create_player(n2, 'O', PlayerType::HUMAN);
    }
    else
    {
        n2 = "Computer";
        p2 = ui->create_player(n2, 'O', PlayerType::AI);
    }

    p1->set_board_ptr(board);
    p2->set_board_ptr(board);

    Player<char>* current = p1;

    while (true)
    {
        ui->display_board_matrix(board->get_board_matrix());

        Move<char>* move = ui->get_move(current);

        if (!board->update_board(move))
        {
            cout << "Invalid move! Try again.\n";
            delete move;
            continue;
        }
        delete move;

        if (board->is_win(current))
        {
            ui->display_board_matrix(board->get_board_matrix());
            cout << current->get_name() << " wins!\n";
            break;
        }

        current = (current == p1 ? p2 : p1);
    }

    delete board;
    delete p1; delete p2; delete ui;
}

// ---------------- Obstacles TTT ----------------

/**
 * @brief Launches the Obstacles Tic-Tac-Toe game.
 *
 * Played on a 6x6 board with random obstacles placed.
 * First to get 3 in a row wins.
 */
void MenuManager::run_obstacles_ttt() {
    Obstacles_UI* game_ui = new Obstacles_UI();
    game_ui->launch();
    delete game_ui;
}

// ---------------- 4x4 Tic Tac Toe ----------------

/**
 * @brief Launches the 4x4 Tic-Tac-Toe game.
 *
 * Each player has 4 movable tokens. Players can only move tokens
 * to adjacent empty squares (no diagonal movement or jumping).
 * First to align 3 tokens wins.
 */
void MenuManager::run_four_by_four() {
    cout << "\nWelcome to 4x4 Tic Tac Toe!\n";
    cout << "Rules:\n";
    cout << "-> Each player has 4 tokens.\n";
    cout << "-> You can only MOVE your tokens to an adjacent EMPTY square.\n";
    cout << "-> No diagonal movement, no jumping over tokens.\n";
    cout << "-> First to align 3 tokens wins (row, column, diagonal).\n\n";

    UI<char>* game_ui = new FourByFour_UI();
    Board<char>* board = new FourByFour_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(board, players, game_ui);
    game.run();

    delete board;
    for (int i = 0; i < 2; ++i)
        delete players[i];
    delete[] players;
    delete game_ui;
}

// ---------------- 5x5 Tic Tac Toe ----------------

/**
 * @brief Launches the 5x5 Tic-Tac-Toe game.
 *
 * Played on a 5x5 board. The winner is determined by who has the
 * most three-in-a-row sequences when the board is full.
 */
void MenuManager::run_five_by_five() {
    FiveByFive_UI* game_ui = new FiveByFive_UI();
    game_ui->launch();
    delete game_ui;
}

// ---------------- Word Tic Tac Toe ----------------

/**
 * @brief Launches the Word Tic-Tac-Toe game.
 *
 * Players place letters from A-Z on a 3x3 board.
 * Win by forming a valid 3-letter English word in any row, column, or diagonal.
 */
void MenuManager::run_word_ttt() {
    WordTTT_Board board;
    WordTTT_UI ui;

    Player<char>* players[2];
    string p1, p2;
    int mode;

    cout << "WORD TIC TAC TEO GAME\n";
    cout << "Choose mode:\n1) Human vs Human\n2) Human vs AI\nYour choice: ";
    cin >> mode;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Player 1 name: ";
    getline(cin, p1);

    if (mode == 1) {
        cout << "Enter Player 2 name: ";
        getline(cin, p2);
        players[0] = ui.create_player(p1, 'A', PlayerType::HUMAN);
        players[1] = ui.create_player(p2, 'B', PlayerType::HUMAN);
    }
    else if (mode == 2) {
        p2 = "AI";
        players[0] = ui.create_player(p1, 'A', PlayerType::HUMAN);
        players[1] = ui.create_player(p2, 'B', PlayerType::AI);
    }
    else {
        cout << "Invalid mode! Exiting.\n";
        return;
    }

    GameManager<char> game(&board, players, &ui);
    game.run();

    delete players[0];
    delete players[1];
}

// ---------------- Pyramid Tic-Tac-Toe ----------------

/**
 * @brief Launches the Pyramid Tic-Tac-Toe game.
 *
 * Played on a pyramid-shaped board (1 cell top row, 3 middle, 5 bottom).
 * First to get 3 in a row wins.
 */
void MenuManager::run_pyramid() {
    UI<char>* ui = new Pyramid_UI();
    Board<char>* b = new Pyramid_Board();
    Player<char>** p = ui->setup_players();

    GameManager<char> game(b, p, ui);
    game.run();

    delete b;
    delete p[0];
    delete p[1];
    delete[] p;
    delete ui;
}

// ---------------- Ultimate Tic-Tac-Toe ----------------

/**
 * @brief Launches the Ultimate Tic-Tac-Toe game.
 *
 * Played on a 9x9 board divided into nine 3x3 sub-boards.
 * Win sub-boards to claim them, then get 3 sub-boards in a row to win.
 */
void MenuManager::run_ultimate_ttt() {
    Ultimate_UI* game_ui = new Ultimate_UI();
    game_ui->launch();
    delete game_ui;
}
    //----------------Diamond----------------
void MenuManager::run_DiamondTTT()
{ string x, p2;
    cout << "Enter Player 1 name (X): ";
    cin >> x;
    cout << "Enter Player 2 name (O): ";
    cin >> p2;

    DiamondTTT g;
    g.play();
}

//-----------------------MEMORY Tic Tac Toe-------------------------
void MenuManager::run_memory_ttt() {
    UI<char>* ui = new MemoryTTT_UI();
    Board<char>* b = new MemoryTTT_Board();
    Player<char>** p = ui->setup_players();

    GameManager<char> game(b, p, ui);
    game.run();

    delete b;
    delete p[0];
    delete p[1];
    delete[] p;
    delete ui;
}

