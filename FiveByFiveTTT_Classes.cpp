/**
 * @file FiveByFiveTTT_Classes.cpp
 * @brief Implementation of the 5x5 Tic-Tac-Toe game classes.
 *
 * Contains the implementation of FiveByFive_Board and FiveByFive_UI,
 * including AI logic using the Minimax algorithm with alpha-beta pruning.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include "FiveByFiveTTT_Classes.h"

using namespace std;

// ================== FiveByFive_Board Implementation ==================

/**
 * @brief Constructs a 5x5 board with all cells initialized to blank.
 */
FiveByFive_Board::FiveByFive_Board() : Board<char>(5, 5) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

/**
 * @brief Updates the board with a player's move.
 * @param move Pointer to the move containing coordinates and symbol.
 * @return true if the move was valid and applied, false otherwise.
 */
bool FiveByFive_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (board[x][y] != blank_symbol)
        return false;

    board[x][y] = move->get_symbol();
    n_moves++;
    return true;
}

/**
 * @brief Counts all three-in-a-row sequences for a given symbol.
 * 
 * Checks horizontal, vertical, and both diagonal directions.
 * 
 * @param sym The symbol to count sequences for ('X' or 'O').
 * @return The total number of three-in-a-row sequences.
 */
int FiveByFive_Board::count_three_in_a_row(char sym) const {
    int count = 0;

    // Horizontal
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c <= columns - 3; ++c)
            if (board[r][c] == sym && board[r][c+1] == sym && board[r][c+2] == sym)
                count++;

    // Vertical
    for (int c = 0; c < columns; ++c)
        for (int r = 0; r <= rows - 3; ++r)
            if (board[r][c] == sym && board[r+1][c] == sym && board[r+2][c] == sym)
                count++;

    // Diagonal (top-left to bottom-right)
    for (int r = 0; r <= rows - 3; ++r)
        for (int c = 0; c <= columns - 3; ++c)
            if (board[r][c] == sym && board[r+1][c+1] == sym && board[r+2][c+2] == sym)
                count++;

    // Diagonal (bottom-left to top-right)
    for (int r = 2; r < rows; ++r)
        for (int c = 0; c <= columns - 3; ++c)
            if (board[r][c] == sym && board[r-1][c+1] == sym && board[r-2][c+2] == sym)
                count++;

    return count;
}

/**
 * @brief Checks if the game is over.
 * @param player Pointer to the current player.
 * @return true if 24 moves have been made (1 cell remaining).
 */
bool FiveByFive_Board::game_is_over(Player<char>* player) {
    return n_moves >= 24;  // Game ends when only 1 square remains
}

/**
 * @brief Determines if the player has won.
 * 
 * The player wins if they have more three-in-a-row sequences than the opponent.
 * 
 * @param player Pointer to the player to check.
 * @return true if the player has more sequences, false otherwise.
 */
bool FiveByFive_Board::is_win(Player<char>* player) {
    if (!game_is_over(player)) return false;
    
    int x_score = count_three_in_a_row('X');
    int o_score = count_three_in_a_row('O');
    
    return (player->get_symbol() == 'X') ? (x_score > o_score) : (o_score > x_score);
}

/**
 * @brief Determines if the player has lost.
 * 
 * The player loses if the opponent has more three-in-a-row sequences.
 * 
 * @param player Pointer to the player to check.
 * @return true if the player has fewer sequences, false otherwise.
 */
bool FiveByFive_Board::is_lose(Player<char>* player) {
    if (!game_is_over(player)) return false;
    
    int x_score = count_three_in_a_row('X');
    int o_score = count_three_in_a_row('O');
    
    return (player->get_symbol() == 'X') ? (o_score > x_score) : (x_score > o_score);
}

/**
 * @brief Checks if the game ended in a draw.
 * @param player Pointer to the current player.
 * @return true if both players have equal sequences, false otherwise.
 */
bool FiveByFive_Board::is_draw(Player<char>* player) {
    if (!game_is_over(player)) return false;
    return count_three_in_a_row('X') == count_three_in_a_row('O');
}


// ================== FiveByFive_UI Implementation ==================

/**
 * @brief Constructs the 5x5 Tic-Tac-Toe UI.
 */
FiveByFive_UI::FiveByFive_UI() : UI<char>(3), boardPtr(nullptr) {}

// ================== AI Functions ==================

/**
 * @brief Evaluates a triplet of cells for AI scoring.
 * 
 * Used by the minimax algorithm to evaluate potential three-in-a-row sequences.
 * 
 * @param a First cell value.
 * @param b Second cell value.
 * @param c Third cell value.
 * @param ai AI player's symbol.
 * @param human Human player's symbol.
 * @param blank Empty cell symbol.
 * @return Score value for the triplet.
 */
static int eval3(char a, char b, char c, char ai, char human, char blank) {
    int aiCount = 0, huCount = 0, emptyCount = 0;
    
    if (a == ai) aiCount++; else if (a == human) huCount++; else if (a == blank) emptyCount++;
    if (b == ai) aiCount++; else if (b == human) huCount++; else if (b == blank) emptyCount++;
    if (c == ai) aiCount++; else if (c == human) huCount++; else if (c == blank) emptyCount++;
    
    // Completed 3-in-a-row
    if (aiCount == 3) return 100;
    if (huCount == 3) return -100;
    
    // Mixed line = useless
    if (aiCount > 0 && huCount > 0) return 0;
    
    // Potential (2 with 1 empty)
    if (aiCount == 2 && emptyCount == 1) return 10;
    if (huCount == 2 && emptyCount == 1) return -10;
    
    // Single with potential
    if (aiCount == 1 && emptyCount == 2) return 1;
    if (huCount == 1 && emptyCount == 2) return -1;
    
    return 0;
}

/**
 * @brief Evaluates the entire board state for the AI.
 * 
 * Sums up scores from all possible three-in-a-row positions.
 * 
 * @param b Pointer to the game board.
 * @param ai AI player's symbol.
 * @param human Human player's symbol.
 * @return Total evaluation score for the board state.
 */
static int evaluateBoard(FiveByFive_Board* b, char ai, char human) {
    int score = 0;
    const auto& board = b->get_board_matrix();
    char blank = '.';
    
    for (int r = 0; r < 5; r++)
        for (int c = 0; c <= 2; c++)
            score += eval3(board[r][c], board[r][c+1], board[r][c+2], ai, human, blank);
    
    for (int c = 0; c < 5; c++)
        for (int r = 0; r <= 2; r++)
            score += eval3(board[r][c], board[r+1][c], board[r+2][c], ai, human, blank);
    
    for (int r = 0; r <= 2; r++)
        for (int c = 0; c <= 2; c++)
            score += eval3(board[r][c], board[r+1][c+1], board[r+2][c+2], ai, human, blank);
    

    for (int r = 2; r < 5; r++)
        for (int c = 0; c <= 2; c++)
            score += eval3(board[r][c], board[r-1][c+1], board[r-2][c+2], ai, human, blank);
    
    return score;
}

/**
 * @brief Minimax algorithm with alpha-beta pruning for AI decision making.
 * 
 * Recursively evaluates all possible moves to find the optimal play.
 * 
 * @param b Pointer to the game board.
 * @param depth Current search depth.
 * @param isMax Whether this is a maximizing player's turn.
 * @param ai AI player's symbol.
 * @param human Human player's symbol.
 * @param alpha Alpha value for pruning.
 * @param beta Beta value for pruning.
 * @return The best score achievable from this position.
 */
static int minimax(FiveByFive_Board* b, int depth, bool isMax, char ai, char human, int alpha, int beta) {
    if (depth == 0 || b->get_n_moves() >= 24) {
        return evaluateBoard(b, ai, human);
    }
    
    if (isMax) {
        int best = INT_MIN;
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (b->get_cell(r, c) != '.') continue;
                
                Move<char> move(r, c, ai);
                b->update_board(&move);
                int score = minimax(b, depth - 1, false, ai, human, alpha, beta);
                b->set_cell(r, c, '.');  // Undo
                b->decrement_moves();
                
                best = max(best, score);
                alpha = max(alpha, score);
                if (beta <= alpha) break;
            }
            if (beta <= alpha) break;
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (b->get_cell(r, c) != '.') continue;
                
                Move<char> move(r, c, human);
                b->update_board(&move);
                int score = minimax(b, depth - 1, true, ai, human, alpha, beta);
                b->set_cell(r, c, '.');  // Undo
                b->decrement_moves();
                
                best = min(best, score);
                beta = min(beta, score);
                if (beta <= alpha) break;
            }
            if (beta <= alpha) break;
        }
        return best;
    }
}

/**
 * @brief Finds the best move for the AI using minimax.
 * 
 * @param b Pointer to the game board.
 * @param ai AI player's symbol.
 * @param human Human player's symbol.
 * @param depth Search depth (default: 4).
 * @return Pair of (row, column) for the best move.
 */
static pair<int, int> findBestMove(FiveByFive_Board* b, char ai, char human, int depth = 4) {
    int bestScore = INT_MIN;
    int bestR = 0, bestC = 0;
    
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (b->get_cell(r, c) != '.') continue;
            
            Move<char> move(r, c, ai);
            b->update_board(&move);
            int score = minimax(b, depth - 1, false, ai, human, INT_MIN, INT_MAX);
            b->set_cell(r, c, '.');  // Undo
            b->decrement_moves();
            
            if (score > bestScore) {
                bestScore = score;
                bestR = r;
                bestC = c;
            }
        }
    }
    return {bestR, bestC};
}

// ================== FiveByFive_UI Implementation ==================

Move<char>* FiveByFive_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::COMPUTER || player->get_type() == PlayerType::AI) {
        char aiSym = player->get_symbol();
        char humanSym = (aiSym == 'X') ? 'O' : 'X';
        
        cout << player->get_name() << " is thinking...\n";
        pair<int, int> best = findBestMove(boardPtr, aiSym, humanSym, 4);
        x = best.first;
        y = best.second;
        
        cout << player->get_name() << " plays at (" << x << ", " << y << ")\n";
    } else {
        cout << player->get_name() << " (" << player->get_symbol() << "), enter move (row col): ";
        cin >> x >> y;
    }

    return new Move<char>(x, y, player->get_symbol());
}

/**
 * @brief Displays the board matrix with current scores.
 * @param matrix The board matrix to display.
 */
void FiveByFive_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    UI<char>::display_board_matrix(matrix);
    
    if (boardPtr) {
        int x_score = boardPtr->count_three_in_a_row('X');
        int o_score = boardPtr->count_three_in_a_row('O');
        cout << "Scores -> X: " << x_score << " | O: " << o_score << "\n";
    }
}

/**
 * @brief Launches the 5x5 Tic-Tac-Toe game.
 * 
 * Sets up the game board, creates players, and runs the game loop.
 */
void FiveByFive_UI::launch() {
    cout << "\nWelcome to 5x5 Tic-Tac-Toe!\n";
    cout << "Rules:\n";
    cout << "-> Players take turns placing marks on a 5x5 grid\n";
    cout << "-> Game ends when only ONE square remains empty (24 moves)\n";
    cout << "-> The player with the MOST three-in-a-row sequences WINS!\n\n";
    FiveByFive_UI* game_ui = new FiveByFive_UI();
    FiveByFive_Board* five_board = new FiveByFive_Board();
    game_ui->set_board(five_board);
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(five_board, players, game_ui);
    game.run();

    delete five_board;
    for (int i = 0; i < 2; ++i)
        delete players[i];
    delete[] players;
    delete game_ui;
}