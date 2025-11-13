#include "MenuManager.h"
#include <iostream>
#include <limits>

MenuManager::MenuManager() {
    games = {"X-O (Tic-Tac-Toe)", "Exit"};
}

void MenuManager::run() {
    while (true) {
        display_menu();
        int choice = get_choice();
        if (choice == 1) {
            std::cout << "Running X-O Game...\n";
            XO_UI xo_ui;
            xo_ui.launch();
        } else if (choice == 2) {
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void MenuManager::display_menu() {
    std::cout << "\n=== Mini Boards Game Menu ===\n";
    for (size_t i = 0; i < games.size(); ++i) {
        std::cout << i + 1 << ". " << games[i] << "\n";
    }
    std::cout << "Choose a game: ";
}

int MenuManager::get_choice() {
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
    return choice;
}