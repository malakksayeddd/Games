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
#include "ObstaclesTTT_Classes.h"
#include "FourByFour_Board.h"
#include "FourByFour_UI.h"
#include "FiveByFive_Classes.h"
#include "WordTTT_Classes.h"
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
    void run_obstacles_ttt();
    void run_four_by_four();
    void run_five_by_five();
    void run_word_ttt(int mode);
};
    int get_choice();
};

#endif
