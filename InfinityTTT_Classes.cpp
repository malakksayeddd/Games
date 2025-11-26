#include "InfinityTTT_Classes.h"
#include <iostream>
using namespace std;

Infinity_Board::Infinity_Board() : Board<char>(3, 3)
{
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = blanksymbol;
}

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

bool Infinity_Board::is_win(Player<char>* player)
{
    return is_win_symbol(player->get_symbol());
}

bool Infinity_Board::game_is_over(Player<char>* player)
{
    return is_win(player);
}

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

// UI 
Infinity_UI::Infinity_UI() : UI<char>("", 3) {}

Player<char>* Infinity_UI::create_player(string& name, char symbol, PlayerType type)
{
    return new Player<char>(name, symbol, type);
}

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
