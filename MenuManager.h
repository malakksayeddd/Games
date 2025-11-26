#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <string>
#include <vector>

#include "XO_Classes.h"
#include "NumericalTTT_Classes.h"
#include "SUS_Classes.h"
#include "FourInARow_Classes.h"
#include "MisereTTT_Classes.h"
#include "InfinityTTT_Classes.h"
class MenuManager {
public:
    MenuManager();
    void run();

private:

    std::vector<std::string> games;

    void display_menu();
    void run_xo_game();
    void run_numerical_ttt();
    void run_sus_game();
    void run_four_in_a_row();
    void run_misere_ttt();
    void run_infinity_ttt();
    int get_choice();
};

#endif
