/**
 * @file MenuManager.h
 * @brief Defines the main menu manager for the board games collection.
 *
 * Provides a central menu system to navigate and launch different
 * Tic-Tac-Toe variants available in the game collection.
 */

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
#include "FiveByFiveTTT_Classes.h"
#include "WordTTT_Classes.h"
#include "PyramidTTT_Classes.h"
#include "UltimateTTT_Classes.h"

/**
 * @class MenuManager
 * @brief Manages the main game selection menu.
 *
 * Displays available games and handles user selection to launch
 * the appropriate game variant.
 */
class MenuManager {
public:
    /**
     * @brief Constructs the MenuManager with available games.
     */
    MenuManager();

    /**
     * @brief Runs the main menu loop.
     * 
     * Displays the game menu repeatedly until the user chooses to exit.
     */
    void run();

private:
    std::vector<std::string> games; ///< List of available game names.

    /**
     * @brief Displays the game selection menu.
     */
    void display_menu();

    /**
     * @brief Launches the classic X-O (Tic-Tac-Toe) game.
     */
    void run_xo_game();

    /**
     * @brief Launches the Numerical Tic-Tac-Toe game.
     */
    void run_numerical_ttt();

    /**
     * @brief Launches the SUS game.
     */
    void run_sus_game();

    /**
     * @brief Launches the Four-in-a-Row (Connect Four) game.
     */
    void run_four_in_a_row();

    /**
     * @brief Launches the Misère Tic-Tac-Toe game.
     */
    void run_misere_ttt();

    /**
     * @brief Launches the Infinity Tic-Tac-Toe game.
     */
    void run_infinity_ttt();

    /**
     * @brief Launches the Obstacles Tic-Tac-Toe game.
     */
    void run_obstacles_ttt();

    /**
     * @brief Launches the 4x4 Tic-Tac-Toe game.
     */
    void run_four_by_four();

    /**
     * @brief Launches the 5x5 Tic-Tac-Toe game.
     */
    void run_five_by_five();

    /**
     * @brief Launches the Word Tic-Tac-Toe game.
     */
    void run_word_ttt();

    /**
     * @brief Launches the Pyramid Tic-Tac-Toe game.
     */
    void run_pyramid();

    /**
     * @brief Launches the Ultimate Tic-Tac-Toe game.
     */
    void run_ultimate_ttt();

    /**
     * @brief Gets the user's menu choice.
     * @return The selected menu option number.
     */
    int get_choice();
};

#endif
