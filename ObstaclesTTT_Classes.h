/**
 * @file ObstaclesTTT_Classes.h
 * @brief Defines the Obstacles Tic-Tac-Toe game classes.
 *
 * This variant uses a 6x6 board where:
 * - Players need 4 in a row to win
 * - After every round (both players move), 2 random obstacle cells are added
 * - Obstacles block cell placement
 */

#ifndef OBSTACLESTTT_CLASSES_H
#define OBSTACLESTTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
using namespace std;

/**
 * @class Obstacles_Board
 * @brief Represents the Obstacles Tic-Tac-Toe game board.
 *
 * A 6x6 board with dynamic obstacle placement that increases
 * difficulty as the game progresses.
 *
 * @see Board
 */
class Obstacles_Board : public Board<char> {
private:
    char blank_symbol = '.';      ///< Character for empty cells.
    char obstacle_symbol = '#';   ///< Character for obstacle cells.

public:
    /**
     * @brief Constructs a 6x6 board with no obstacles.
     */
    Obstacles_Board();

    /**
     * @brief Updates the board with a player's move.
     * 
     * After both players move (every round), 2 obstacles are added.
     * 
     * @param move Pointer to the move containing coordinates and symbol.
     * @return true if the move is valid, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the player has won (4 in a row).
     * @param player Pointer to the player to check.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the player has lost.
     * @param Unused parameter.
     * @return Always returns false.
     */
    bool is_lose(Player<char>*) override { return false; }

    /**
     * @brief Checks if the game is a draw.
     * @param player Pointer to the player to check.
     * @return true if no empty cells remain and no winner, false otherwise.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game is over.
     * @param player Pointer to the player to evaluate.
     * @return true if game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Checks if a symbol has 4 in a row.
     * @param sym The symbol to check ('X' or 'O').
     * @return true if 4 in a row exists, false otherwise.
     */
    bool has_symbol_won(char sym);

    /**
     * @brief Adds 2 random obstacles to empty cells.
     */
    void add_random_obstacles();

    /**
     * @brief Gets the blank symbol character.
     * @return The blank symbol ('.')
     */
    char get_blank_symbol() const { return blank_symbol; }

    /**
     * @brief Gets the obstacle symbol character.
     * @return The obstacle symbol ('#')
     */
    char get_obstacle_symbol() const { return obstacle_symbol; }

    /**
     * @brief Checks if a cell is empty.
     * @param x Row index.
     * @param y Column index.
     * @return true if cell is empty, false otherwise.
     */
    bool is_cell_empty(int x, int y) const;

    /**
     * @brief Gets a list of all empty cells.
     * @return Vector of (row, column) pairs for empty cells.
     */
    vector<pair<int, int>> get_empty_cells() const;
};

/**
 * @class Obstacles_ComputerPlayer
 * @brief Computer player that makes random moves for Obstacles TTT.
 *
 * @see Player
 */
class Obstacles_ComputerPlayer : public Player<char> {
public:
    /**
     * @brief Constructs a computer player.
     * @param name The player's name.
     * @param symbol The player's symbol ('X' or 'O').
     */
    Obstacles_ComputerPlayer(string name, char symbol);

    /**
     * @brief Gets a random valid move.
     * @return Pointer to a randomly selected Move.
     */
    Move<char>* get_random_move();
};

/**
 * @class Obstacles_UI
 * @brief User Interface class for the Obstacles Tic-Tac-Toe game.
 *
 * @see UI
 */
class Obstacles_UI : public UI<char> {
private:
    Obstacles_Board* currentBoard; ///< Pointer to the game board.

public:
    /**
     * @brief Constructs the Obstacles Tic-Tac-Toe UI.
     */
    Obstacles_UI();

    /**
     * @brief Destructor for Obstacles_UI.
     */
    ~Obstacles_UI() {}

    /**
     * @brief Sets the board pointer.
     * @param b Pointer to the Obstacles_Board.
     */
    void set_board(Obstacles_Board* b) { currentBoard = b; }

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol The player's symbol.
     * @param type The type of player (Human or Computer).
     * @return Pointer to the created Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move from the player.
     * @param player Pointer to the current player.
     * @return Pointer to the Move object.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Launches the Obstacles Tic-Tac-Toe game.
     */
    void launch();
};

#endif
