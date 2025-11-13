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
    void run_xo_game();
    void run_numerical_ttt();
    int get_choice();
  
};

#endif
