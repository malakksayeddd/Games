/**
 * @file WordTTT_Classes.h
 * @brief Defines Word Tic-Tac-Toe game classes.
 *
 * Word TTT is played on a 3x3 board where players place letters.
 * A player wins by forming a valid English word (from dictionary)
 * in any row, column, or diagonal.
 */

#pragma once
#include "BoardGame_Classes.h"
#include <set>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @class WordTTT_Board
 * @brief Represents the Word Tic-Tac-Toe game board.
 *
 * Manages a 3x3 letter grid and validates moves against a dictionary
 * to determine if words are formed.
 *
 * @see Board
 */
class WordTTT_Board : public Board<char> {
    std::set<std::string> dictionary; ///< Set of valid words from dic.txt

public:
    /**
     * @brief Constructs an empty 3x3 Word TTT board.
     */
    WordTTT_Board();

    /**
     * @brief Loads the dictionary from a file.
     * @param path Path to the dictionary file.
     */
    void load_dictionary(const std::string& path);

    /**
     * @brief Checks if a word is in the dictionary.
     * @param w The word to check.
     * @return true if the word is valid, false otherwise.
     */
    bool is_valid_word(const std::string& w) const;

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the move containing position and letter.
     * @return true if the move is valid, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if a player has won by forming a valid word.
     * @param player Unused parameter.
     * @return true if any valid word exists, false otherwise.
     */
    bool is_win(Player<char>*) override;

    /**
     * @brief Checks if a player has lost.
     * @param player Unused parameter.
     * @return Always returns false (no lose condition).
     */
    bool is_lose(Player<char>*) override { return false; }

    /**
     * @brief Checks if the game is a draw.
     * @param player Unused parameter.
     * @return true if board is full with no valid words, false otherwise.
     */
    bool is_draw(Player<char>*) override;

    /**
     * @brief Checks if the game is over.
     * @param player Unused parameter.
     * @return true if won or drawn, false otherwise.
     */
    bool game_is_over(Player<char>*) override;

    /**
     * @brief Gets all empty cell positions.
     * @return Vector of (row, column) pairs for empty cells.
     */
    std::vector<std::pair<int, int>> get_empty_cells() const;

    /**
     * @brief Gets a reference to the dictionary.
     * @return Const reference to the set of valid words.
     */
    const std::set<std::string>& get_dictionary() const { return dictionary; }

    /**
     * @brief Gets the character at a cell.
     * @param r Row index.
     * @param c Column index.
     * @return The character at position (r, c).
     */
    char get_cell(int r, int c) const { return board[r][c]; }

    /**
     * @brief Sets a character at a cell.
     * @param r Row index.
     * @param c Column index.
     * @param value The character to place.
     */
    void set_cell(int r, int c, char value) { board[r][c] = value; }
};

/**
 * @class WordTTT_Move
 * @brief Represents a move in Word Tic-Tac-Toe.
 *
 * Stores the position and letter for a player's move.
 *
 * @see Move
 */
class WordTTT_Move : public Move<char> {
public:
    /**
     * @brief Constructs a Word TTT move.
     * @param r Row position (0-2).
     * @param c Column position (0-2).
     * @param s The letter to place.
     */
    WordTTT_Move(int r, int c, char s) : Move<char>(r, c, s) {}
};

/**
 * @class WordTTT_UI
 * @brief User Interface class for Word Tic-Tac-Toe.
 *
 * Handles input for letter selection and cell placement.
 *
 * @see UI
 */
class WordTTT_UI : public UI<char> {
public:
    /**
     * @brief Default constructor.
     */
    WordTTT_UI() {}

    /**
     * @brief Gets a move from the player.
     * @param player Pointer to the current player.
     * @return Pointer to the Move object with position and letter.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Creates a player for the game.
     * @param name Reference to the player's name.
     * @param symbol The player's symbol (not used for letters).
     * @param type The type of player (Human, Computer, AI).
     * @return Pointer to the created Player object.
     */
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};
