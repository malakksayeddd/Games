/**
 * @file FourInARow_Classes.h
 * @brief Defines the Connect Four (Four-in-a-Row) game classes.
 *
 * This file provides:
 * - `FourInARow_Board`: A 6x7 board where pieces drop to the bottom.
 * - `FourInARow_UI`: User interface for the Connect Four game.
 *
 * Players win by getting four of their pieces in a row
 * (horizontally, vertically, or diagonally).
 */

#ifndef FOURINAROW_CLASSES_H
#define FOURINAROW_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class FourInARow_Board
 * @brief Represents a Connect Four (6x7) game board.
 *
 * Implements gravity-based piece placement where pieces fall to the
 * lowest available position in the selected column.
 *
 * @see Board
 */
class FourInARow_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character representing an empty cell.

public:
    /**
     * @brief Constructs a 6x7 Connect Four board.
     */
    FourInARow_Board();

    /**
     * @brief Places a piece in the specified column.
     * @param move Pointer to the move (column selection).
     * @return true if the move is valid, false if column is full.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the player has four in a row.
     * @param player Pointer to the player to check.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the player has lost.
     * @param Unused parameter.
     * @return Always returns false.
     */
    bool is_lose(Player<char>* ) { return false; };

    /**
     * @brief Checks if the game is a draw.
     * @param player Pointer to the player to check.
     * @return true if board is full with no winner, false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Checks if the game is over.
     * @param player Pointer to the player to evaluate.
     * @return true if game has ended (win or draw), false otherwise.
     */
    bool game_is_over(Player<char>* player);

    /**
     * @brief Gets the lowest available row in a column.
     * @param col The column index (0-6).
     * @return Row index of lowest empty cell, or -1 if column is full.
     */
    int get_lowest_row(int col);

    /**
     * @brief Checks if a symbol has four in a row.
     * @param sym The symbol to check ('X' or 'O').
     * @return true if four in a row exists, false otherwise.
     */
    bool has_symbol_won(char sym);
};

/**
 * @class FourInARow_UI
 * @brief User Interface class for the Connect Four game.
 *
 * Handles player interaction and AI difficulty settings.
 *
 * @see UI
 */
class FourInARow_UI : public UI<char> {
private:
    FourInARow_Board* currentBoard;     ///< Pointer to the game board.
    int player_difficulty[2];            ///< AI difficulty levels for each player.
    
public:
    /**
     * @brief Constructs the Connect Four UI.
     */
    FourInARow_UI();

    /**
     * @brief Destructor for FourInARow_UI.
     */
    ~FourInARow_UI() {};

    /**
     * @brief Sets the AI difficulty for a player.
     * @param player_index Index of the player (0 or 1).
     * @param difficulty The difficulty level.
     */
    void set_player_difficulty(int player_index, int difficulty) { player_difficulty[player_index] = difficulty; }

    /**
     * @brief Sets the board pointer.
     * @param b Pointer to the FourInARow_Board.
     */
    void set_board(FourInARow_Board* b) { currentBoard = b; }

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol The player's symbol.
     * @param type The type of player (Human or Computer).
     * @return Pointer to the created Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Sets up both players for the game.
     * @return Array of two Player pointers.
     */
    Player<char>** setup_players();

    /**
     * @brief Gets player type choice from user.
     * @param player_label Label for the player.
     * @param options Available player type options.
     * @return The selected PlayerType.
     */
    virtual PlayerType get_player_type_choice(string player_label, const vector<string>& options);

    /**
     * @brief Gets a move from the player (column selection).
     * @param player Pointer to the current player.
     * @return Pointer to the Move object.
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Launches the Connect Four game.
     */
    void launch();
};

#endif // FOURINAROW_CLASSES_H
