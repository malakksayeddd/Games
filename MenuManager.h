/**
 * @file MenuManager.h
 * @brief Header for the menu manager system.
 */

#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <string>
#include <vector>
#include "XO_Classes.h"

class MenuManager {
public:
    MenuManager();
    void run();

private:
    std::vector<std::string> games;
    void display_menu();
    int get_choice();
    void run_xo_game();
};

#endif // MENU_MANAGER_H