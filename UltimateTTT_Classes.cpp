/**
 * @file UltimateTTT_Classes.cpp
 * @brief Implementation of Ultimate Tic-Tac-Toe game classes.
 *
 * Ultimate TTT uses a 9x9 board divided into nine 3x3 sub-boards.
 * Players compete to win sub-boards and then win 3 in a row on the main board.
 * A unique mechanic: after a move, both players stay on the same sub-board until
 * it's decided (won or drawn).
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "UltimateTTT_Classes.h"

using namespace std;

// ==================== Ultimate_Board Implementation ====================

/**
 * @brief Constructs an empty Ultimate board.
 *
 * Initializes the 9x9 grid (3x3 sub-boards, each 3x3 cells) to empty,
 * and the main board tracking sub-board winners to open.
 */
Ultimate_Board::Ultimate_Board() : Board(9, 9), currentSubRow(-1), currentSubCol(-1) {
    for (int sr = 0; sr < 3; sr++)
        for (int sc = 0; sc < 3; sc++)
            for (int cr = 0; cr < 3; cr++)
                for (int cc = 0; cc < 3; cc++)
                    subBoards[sr][sc][cr][cc] = '.';
    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            mainBoard[i][j] = '.';
}

/**
 * @brief Checks if three values match a symbol.
 * @param a First value.
 * @param b Second value.
 * @param c Third value.
 * @param sym Symbol to match.
 * @return true if all three match the symbol, false otherwise.
 */
bool Ultimate_Board::check_three(char a, char b, char c, char sym) const {
    return (a == sym && b == sym && c == sym);
}

/**
 * @brief Checks if a player has won a sub-board.
 * @param sr Sub-board row index (0-2).
 * @param sc Sub-board column index (0-2).
 * @param sym The player's symbol ('X' or 'O').
 * @return true if the player has three in a row in the sub-board, false otherwise.
 *
 * Checks all rows, columns, and both diagonals of the specified sub-board.
 */
bool Ultimate_Board::check_sub_winner(int sr, int sc, char sym) const {
    // Check rows
    for (int r = 0; r < 3; r++)
        if (check_three(subBoards[sr][sc][r][0], subBoards[sr][sc][r][1], subBoards[sr][sc][r][2], sym))
            return true;
    // Check columns
    for (int c = 0; c < 3; c++)
        if (check_three(subBoards[sr][sc][0][c], subBoards[sr][sc][1][c], subBoards[sr][sc][2][c], sym))
            return true;
    // Check diagonals
    if (check_three(subBoards[sr][sc][0][0], subBoards[sr][sc][1][1], subBoards[sr][sc][2][2], sym))
        return true;
    if (check_three(subBoards[sr][sc][0][2], subBoards[sr][sc][1][1], subBoards[sr][sc][2][0], sym))
        return true;
    return false;
}

/**
 * @brief Checks if a sub-board is completely filled.
 * @param sr Sub-board row index.
 * @param sc Sub-board column index.
 * @return true if all 9 cells are occupied, false otherwise.
 */
bool Ultimate_Board::is_sub_full(int sr, int sc) const {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (subBoards[sr][sc][r][c] == '.')
                return false;
    return true;
}

/**
 * @brief Updates the board with a player's move.
 * @param move Pointer to the move (9x9 coordinates mapped to sub-board/cell).
 * @return true if the move is valid and applied, false otherwise.
 *
 * Validates:
 * - Coordinates are within bounds
 * - Move is in the current active sub-board (or any open if free choice)
 * - Sub-board is not already won/drawn
 * - Cell is empty
 *
 * After a successful move, checks if the sub-board is won or drawn,
 * and updates the main board accordingly.
 */
bool Ultimate_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();
    
    int sr = x / 3, cr = x % 3;
    int sc = y / 3, cc = y % 3;
    
    if (sr < 0 || sr >= 3 || sc < 0 || sc >= 3) return false;
    if (cr < 0 || cr >= 3 || cc < 0 || cc >= 3) return false;
    
    if (currentSubRow != -1 && (sr != currentSubRow || sc != currentSubCol)) return false;
    
    if (mainBoard[sr][sc] != '.') return false;  
    if (subBoards[sr][sc][cr][cc] != '.') return false; 
    
    subBoards[sr][sc][cr][cc] = sym;
    n_moves++;
    
    if (check_sub_winner(sr, sc, sym)) {
        mainBoard[sr][sc] = sym;
        currentSubRow = -1; 
        currentSubCol = -1;
    } else if (is_sub_full(sr, sc)) {
        mainBoard[sr][sc] = '#'; 
        currentSubRow = -1;
        currentSubCol = -1;
    } else {
        currentSubRow = sr;
        currentSubCol = sc;
    }
    
    return true;
}

/**
 * @brief Checks if the player has won the main game.
 * @param player Pointer to the player to check.
 * @return true if the player has 3 sub-boards in a row, false otherwise.
 *
 * Checks rows, columns, and diagonals on the main 3x3 meta-board.
 */
bool Ultimate_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();
    // Check main board for 3 in a row
    for (int r = 0; r < 3; r++)
        if (check_three(mainBoard[r][0], mainBoard[r][1], mainBoard[r][2], sym))
            return true;
    for (int c = 0; c < 3; c++)
        if (check_three(mainBoard[0][c], mainBoard[1][c], mainBoard[2][c], sym))
            return true;
    if (check_three(mainBoard[0][0], mainBoard[1][1], mainBoard[2][2], sym))
        return true;
    if (check_three(mainBoard[0][2], mainBoard[1][1], mainBoard[2][0], sym))
        return true;
    return false;
}

/**
 * @brief Checks if the game is a draw.
 * @param player Pointer to the player to check against.
 * @return true if all sub-boards completed with no winner, false otherwise.
 */
bool Ultimate_Board::is_draw(Player<char>* player) {
    // Draw if all sub-boards are completed and no winner
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (mainBoard[r][c] == '.')
                return false;
    return !is_win(player);
}

/**
 * @brief Checks if the game is over.
 * @param player Pointer to the player to evaluate.
 * @return true if there's a winner or draw, false otherwise.
 */
bool Ultimate_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// ==================== Ultimate_UI Implementation ====================

/**
 * @brief Constructs the Ultimate Tic-Tac-Toe UI.
 *
 * Initializes the title and sets up the display.
 */
Ultimate_UI::Ultimate_UI() : UI<char>("=== ULTIMATE TIC-TAC-TOE ===", 1), boardPtr(nullptr) {}

/**
 * @brief Displays the main board and current sub-board side by side.
 *
 * Shows:
 * - The 3x3 main board showing sub-board winners ('X', 'O', '-' for draw, empty if open)
 * - The current active sub-board (if one is selected)
 * - Instructions for where the player can move
 */
void Ultimate_UI::display_board() const {
    if (!boardPtr) return;
    
    cout << "\n";
    
    int csr = boardPtr->get_current_sub_row();
    int csc = boardPtr->get_current_sub_col();
    if (csr == -1) {
        cout << "  >> Choose any sub-board to play in <<\n";
    } else {
        cout << "  >> Playing in sub-board (" << csr << "," << csc << ") <<\n";
    }
    
    cout << "\n  Main Board:         Current Sub-board:";
    if (csr != -1) {
        cout << " (" << csr << "," << csc << ")";
    }
    cout << "\n";
    
    // main board and current sub-board side by side
    cout << "    0   1   2";
    if (csr != -1) cout << "           0   1   2";
    cout << "\n";
    
    cout << "  +---+---+---+";
    if (csr != -1) cout << "       +---+---+---+";
    cout << "\n";
    
    for (int r = 0; r < 3; r++) {
        // Main board row
        cout << r << " |";
        for (int c = 0; c < 3; c++) {
            char ch = boardPtr->get_main_cell(r, c);
            if (ch == '.') cout << "   |";
            else if (ch == '#') cout << " - |";
            else cout << " " << ch << " |";
        }
        
        // sub-board on the right
        if (csr != -1) {
            cout << "     " << r << " |";
            for (int c = 0; c < 3; c++) {
                char ch = boardPtr->get_sub_cell(csr, csc, r, c);
                cout << " " << ch << " |";
            }
        }
        cout << "\n  +---+---+---+";
        if (csr != -1) cout << "       +---+---+---+";
        cout << "\n";
    }
    cout << "\n";
}

/**
 * @brief Gets a move from the player.
 * @param player Pointer to the current player.
 * @return Pointer to a Move object with 9x9 coordinates.
 *
 * For computer players: randomly selects a valid sub-board and cell.
 * For human players: prompts for sub-board selection (if free choice)
 * and then cell selection within the active sub-board.
 */
Move<char>* Ultimate_UI::get_move(Player<char>* player) {
    display_board();
    
    int sr = boardPtr->get_current_sub_row();
    int sc = boardPtr->get_current_sub_col();
    int cr, cc;
    
    if (player->get_type() == PlayerType::COMPUTER || player->get_type() == PlayerType::AI) {
        if (sr == -1) { // randomly select a sub-board
            do {
                sr = rand() % 3;
                sc = rand() % 3;
            } while (boardPtr->is_sub_completed(sr, sc));
        }
        do {
            cr = rand() % 3;
            cc = rand() % 3;
        } while (boardPtr->get_sub_cell(sr, sc, cr, cc) != '.');
        
        cout << player->get_name() << " plays: Sub(" << sr << "," << sc 
             << ") Cell(" << cr << "," << cc << ")\n";
    } else {
        cout << player->get_name() << " (" << player->get_symbol() << ")\n";
        
        if (sr == -1) {
            cout << "  Choose sub-board (row col): ";
            cin >> sr >> sc;
            
            boardPtr->set_current_sub(sr, sc);
            cout << "\n";
            display_board();  // Show the selected sub-board
            
            cout << "  Enter cell (row col): ";
            cin >> cr >> cc;
        } else {
            cout << "  Playing in sub-board (" << sr << "," << sc << ")\n";
            cout << "  Enter cell (row col): ";
            cin >> cr >> cc;
        }
    }
    
    return new Move<char>(sr * 3 + cr, sc * 3 + cc, player->get_symbol());
}

/**
 * @brief Launches the Ultimate Tic-Tac-Toe game.
 *
 * Displays the rules, creates the board, sets up players,
 * and runs the game loop until completion.
 */
void Ultimate_UI::launch() {
    srand(static_cast<unsigned int>(time(0)));
    
    cout << "\nRules:\n";
    cout << "- Both players stay on the same sub-board until it's won/drawn\n";
    cout << "- Win a sub-board to claim it on the main board\n";
    cout << "- Win 3 sub-boards in a row to win the game!\n\n";
    
    Ultimate_Board* board = new Ultimate_Board();
    boardPtr = board;
    
    Player<char>** players = setup_players();
    players[0]->set_board_ptr(board);
    players[1]->set_board_ptr(board);
    
    GameManager<char> game(board, players, this);
    game.run();
    
    delete board;
    delete players[0];
    delete players[1];
    delete[] players;
}
