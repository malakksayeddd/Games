/**
 * @file InfinityTTT_Classes.cpp
 * @brief Implementation of the Infinity Tic-Tac-Toe game classes.
 *
 * Contains the implementation of Infinity_Board and Infinity_UI,
 * including the move history management logic.
 */

#include "InfinityTTT_Classes.h"
#include <iostream>
using namespace std;

/**
 * @brief Constructs a 3x3 Infinity board with all cells empty.
 */
Infinity_Board::Infinity_Board() : Board<char>(3, 3)
{
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = blanksymbol;
}

/**
 * @brief Updates the board with a player's move.
 * 
 * Validates the move, places the symbol, adds to history,
 * and removes oldest move if player has more than 3 marks.
 * 
 * @param move Pointer to the move containing coordinates and symbol.
 * @return true if move was valid and applied, false otherwise.
 */
bool Infinity_Board::update_board(Move<char>* move)
{
    int r = move->get_x();
    int c = move->get_y();
    char s = move->get_symbol();

    if (r < 0 || r >= 3 || c < 0 || c >= 3) return false;
    if (board[r][c] != blanksymbol) return false;

    
    board[r][c] = s;

   
    if (s == 'X') historyX.push({ r,c });
    else          historyO.push({ r,c });

    if (is_win_symbol(s)) return true;

   
    process_player_history(s);

    return true;
}

/**
 * @brief Processes player history and removes oldest move if needed.
 * 
 * If a player has more than 3 marks on the board, removes the oldest one.
 * 
 * @param s The player's symbol ('X' or 'O').
 */
void Infinity_Board::process_player_history(char s)
{
    queue<pair<int, int>>& Q = (s == 'X' ? historyX : historyO);

    if (Q.size() > 3)
    {
        auto old = Q.front();
        Q.pop();
        board[old.first][old.second] = blanksymbol;
    }
}

/**
 * @brief Checks if the player has won.
 * @param player Pointer to the player to check.
 * @return true if the player has 3 in a row, false otherwise.
 */
bool Infinity_Board::is_win(Player<char>* player)
{
    return is_win_symbol(player->get_symbol());
}

/**
 * @brief Checks if the game is over.
 * @param player Pointer to the player to evaluate.
 * @return true if any player has won, false otherwise.
 */
bool Infinity_Board::game_is_over(Player<char>* player)
{
    return is_win(player);
}

/**
 * @brief Checks if a symbol has 3 in a row anywhere on the board.
 * 
 * Checks rows, columns, and both diagonals.
 * 
 * @param s The symbol to check ('X' or 'O').
 * @return true if 3 in a row exists, false otherwise.
 */
bool Infinity_Board::is_win_symbol(char s)
{
    // rows
    for (int r = 0; r < 3; r++)
        if (board[r][0] == s && board[r][1] == s && board[r][2] == s)
            return true;

    // columns
    for (int c = 0; c < 3; c++)
        if (board[0][c] == s && board[1][c] == s && board[2][c] == s)
            return true;

    // diagonals
    if (board[0][0] == s && board[1][1] == s && board[2][2] == s) return true;
    if (board[0][2] == s && board[1][1] == s && board[2][0] == s) return true;

    return false;
}

// ================== Infinity_UI Implementation ==================

/**
 * @brief Constructs the Infinity Tic-Tac-Toe UI.
 */
Infinity_UI::Infinity_UI() : UI<char>("", 3) {}

/**
 * @brief Creates a player with the specified name, symbol, and type.
 * @param name Name of the player.
 * @param symbol The player's symbol.
 * @param type The type of player (Human or Computer).
 * @return Pointer to the newly created Player object.
 */
Player<char>* Infinity_UI::create_player(string& name, char symbol, PlayerType type)
{
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets a move from the player.
 * 
 * For human players, prompts for row and column input.
 * For computer players, selects the first available empty cell.
 * 
 * @param player Pointer to the current player.
 * @return Pointer to the Move object.
 */
Move<char>* Infinity_UI::get_move(Player<char>* player)
{
    int r, c;

    if (player->get_type() == PlayerType::HUMAN)
    {
        cout << player->get_name() << " enter row and column (0-2): ";
        cin >> r >> c;
    }
    else
    {
        // Computer finds first empty cell
        auto grid = player->get_board_ptr()->get_board_matrix();
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i][j] == blanksymbol)
                {
                    r = i; c = j; goto done;
                }
    }

done:
    return new Move<char>(r, c, player->get_symbol());
}
