/**
 * @file main.cpp
 * @brief Entry point for the MiniBoards game collection.
 *
 * This program provides a menu-driven interface to play various
 * Tic-Tac-Toe variants including Classic XO, Pyramid TTT, Four-in-a-Row,
 * 5x5 TTT, Word TTT, Numerical TTT, Misere TTT, 4x4 TTT, Ultimate TTT,
 * SUS Game, Memory TTT, Infinity TTT, and Obstacles TTT.
 *
 * @author MiniBoards Team
 * @version 1.0
 */

#include "MenuManager.h"

/**
 * @brief Main entry point of the application.
 *
 * Creates a MenuManager instance and runs the main game selection menu.
 * The menu allows users to choose from various board game variants.
 *
 * @return 0 on successful execution.
 */
int main() {
    MenuManager menu;
    menu.run();
    return 0;
}
