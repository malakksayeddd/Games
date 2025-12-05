/**
 * @file FourInARow_Classes.cpp
 * @brief Implementation of the Connect Four game classes.
 *
 * Contains the implementation of FourInARow_Board and FourInARow_UI,
 * including AI logic using the Minimax algorithm.
 */

#include <iostream>
#include <iomanip>
#include <cctype>
#include <climits>
#include "FourInARow_Classes.h"

using namespace std;

/**
 * @brief Constructs a 6x7 Connect Four board.
 * 
 * Initializes all cells with the blank symbol.
 */
FourInARow_Board::FourInARow_Board() : Board(6, 7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

/**
 * @brief Gets the lowest empty row in a column (gravity simulation).
 * @param col The column index to check.
 * @return The row index of the lowest empty cell, or -1 if column is full.
 */
int FourInARow_Board::get_lowest_row(int col) {
    for (int row = rows - 1; row >= 0; --row) {
        if (board[row][col] == blank_symbol) {
            return row;
        }
    }
    return -1; 
}

/**
 * @brief Updates the board with a player's move.
 * @param move Pointer to the move containing column and symbol.
 * @return true if the move is valid and applied, false otherwise.
 *
 * Simulates gravity by placing the piece in the lowest empty row.
 * Symbol 0 is used for undo operations (removes topmost piece in column).
 */
bool FourInARow_Board::update_board(Move<char>* move) {
    int col = move->get_y();
    char mark = move->get_symbol();

    if (col < 0 || col >= columns) return false;
    
    // Undo operation
    if (mark == 0) {
        for (int row = 0; row < rows; ++row) {
            if (board[row][col] != blank_symbol) {
                board[row][col] = blank_symbol;
                n_moves--;
                return true;
            }
        }
        return false;
    }
    int row = get_lowest_row(col);
    if (row == -1) {
        return false;
    }

    board[row][col] = toupper(mark);
    n_moves++;
    return true;
}

/**
 * @brief Checks if a player has won.
 * @param player Pointer to the player to check.
 * @return true if the player has 4 in a row.
 */
bool FourInARow_Board::is_win(Player<char>* player) {
    return has_symbol_won(player->get_symbol());
}

/**
 * @brief Checks if the game is a draw.
 * @param player Pointer to the player to check against.
 * @return true if board is full (42 moves) with no winner.
 */
bool FourInARow_Board::is_draw(Player<char>* player) {
    return (n_moves == 42 && !is_win(player));
}

/**
 * @brief Checks if the game is over.
 * @param player Pointer to the player to evaluate.
 * @return true if there's a winner or draw.
 */
bool FourInARow_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/**
 * @brief Checks if a symbol has won (4 consecutive in any direction).
 * @param sym The symbol to check ('X' or 'O').
 * @return true if 4 in a row found horizontally, vertically, or diagonally.
 */
bool FourInARow_Board::has_symbol_won(char sym) {
    // Horizontal win
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c <= columns - 4; ++c) {
            if (board[r][c] == sym && board[r][c + 1] == sym &&
                board[r][c + 2] == sym && board[r][c + 3] == sym)
                return true;
        }
    }
    // Vertical win
    for (int c = 0; c < columns; ++c) {
        for (int r = 0; r <= rows - 4; ++r) {
            if (board[r][c] == sym && board[r + 1][c] == sym &&
                board[r + 2][c] == sym && board[r + 3][c] == sym)
                return true;
        }
    }
    // Diagonal win (top-left to bottom-right)
    for (int r = 0; r <= rows - 4; ++r) {
        for (int c = 0; c <= columns - 4; ++c) {
            if (board[r][c] == sym && board[r + 1][c + 1] == sym &&
                board[r + 2][c + 2] == sym && board[r + 3][c + 3] == sym)
                return true;
        }
    }
    // Diagonal win (bottom-left to top-right)
    for (int r = 3; r < rows; ++r) {
        for (int c = 0; c <= columns - 4; ++c) {
            if (board[r][c] == sym && board[r - 1][c + 1] == sym &&
                board[r - 2][c + 2] == sym && board[r - 3][c + 3] == sym)
                return true;
        }
    }
    return false;
}

/**
 * @brief Helper function to check if a symbol has won.
 * @param b Pointer to the board.
 * @param sym The symbol to check.
 * @return true if the symbol has 4 in a row.
 */
static bool hasWon(FourInARow_Board* b, char sym) {
    return b->has_symbol_won(sym);
}

// ==================== AI Functions (Minimax Algorithm) ====================

/**
 * @brief Evaluates a window of 4 cells for scoring.
 * @param a First cell value.
 * @param b Second cell value.
 * @param c Third cell value.
 * @param d Fourth cell value.
 * @param ai AI player's symbol.
 * @param human Human player's symbol.
 * @return Score for this window (positive favors AI, negative favors human).
 */
static inline int eval4(char a, char b, char c, char d, char ai, char human) {
    int aiCount = 0, huCount = 0;

    if (a == ai) aiCount++; else if (a == human) huCount++;
    if (b == ai) aiCount++; else if (b == human) huCount++;
    if (c == ai) aiCount++; else if (c == human) huCount++;
    if (d == ai) aiCount++; else if (d == human) huCount++;

    // Mixed line → instantly useless
    if (aiCount > 0 && huCount > 0) return 0;

    // AI scoring
    if (aiCount == 3) return 50;
    if (aiCount == 2) return 10;
    if (aiCount == 1) return 1;

    // Human scoring
    if (huCount == 3) return -40;
    if (huCount == 2) return -8;

    return 0;
}

/**
 * @brief Evaluates the entire board position.
 * @param b Pointer to the board.
 * @param ai AI player's symbol.
 * @param human Human player's symbol.
 * @return Total score for the position.
 *
 * Evaluates all horizontal, vertical, and diagonal windows of 4.
 */
static int evaluatePosition(FourInARow_Board* b, char ai, char human) {
    int score = 0;
    const vector<vector<char>>& board = b->get_board_matrix();
    
    // Checking all horizontal lines
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 4; c++) {
            score += eval4(
                board[r][c], 
                board[r][c+1],
                board[r][c+2], 
                board[r][c+3],
                ai, human
            );
        }
    }
    
    // Checking all vertical lines
    for (int c = 0; c < 7; c++) {
        for (int r = 0; r < 3; r++) {
            score += eval4(
                board[r][c],
                board[r+1][c],
                board[r+2][c],
                board[r+3][c],
                ai, human
            );
        }
    }
    
    // Checking diagonal (top-left to bottom-right)
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 4; c++) {
            score += eval4(
                board[r][c], 
                board[r+1][c+1],
                board[r+2][c+2],
                board[r+3][c+3],
                ai, human
            );
        }
    }
    
    // Checking diagonal (bottom-left to top-right)
    for (int r = 3; r < 6; r++) {
        for (int c = 0; c < 4; c++) {
            score += eval4(
                board[r][c],
                board[r-1][c+1],
                board[r-2][c+2],
                board[r-3][c+3],
                ai, human
            );
        }
    }
    
    return score;
}

/**
 * @brief Minimax algorithm for AI decision making.
 * @param b Pointer to the board.
 * @param depth Remaining search depth.
 * @param isMax true if maximizing player's turn.
 * @param ai AI player's symbol.
 * @param human Human player's symbol.
 * @param enableEval Whether to use position evaluation at depth 0.
 * @return The evaluation score for this position.
 */
static int minimax(FourInARow_Board* b, int depth, bool isMax, char ai, char human, bool enableEval = true) {
    if (hasWon(b, ai)) return 10000 + depth;
    if (hasWon(b, human)) return -10000 - depth;
    if (depth == 0) return enableEval ? evaluatePosition(b, ai, human) : 0;
    
    bool hasMove = false;
    for (int c = 0; c < 7; c++) if (b->get_lowest_row(c) != -1) { hasMove = true; break; }
    if (!hasMove) return 0;
    
    int best = isMax ? INT_MIN : INT_MAX;
    for (int c = 0; c < 7; c++) {
        if (b->get_lowest_row(c) == -1) continue;
        
        Move<char> move(0, c, isMax ? ai : human);
        b->update_board(&move);
        int score = minimax(b, depth - 1, !isMax, ai, human);
        Move<char> undo(0, c, 0);
        b->update_board(&undo);
        
        best = isMax ? max(best, score) : min(best, score);
    }
    return best;
}

/**
 * @brief Finds the best move for the AI player.
 * @param b Pointer to the board.
 * @param ai AI player's symbol.
 * @param human Human player's symbol.
 * @param depth Search depth (default 5).
 * @return The column index for the best move.
 */
static int findBestMove(FourInARow_Board* b, char ai, char human, int depth = 5) {
    int bestCol = 3, bestScore = INT_MIN;
    for (int c = 0; c < 7; c++) {
        if (b->get_lowest_row(c) == -1) continue;
        
        Move<char> move(0, c, ai);
        b->update_board(&move);
        bool enableEval = depth > 2;
        int score = minimax(b, depth, false, ai, human, enableEval);
        Move<char> undo(0, c, 0);
        b->update_board(&undo);
        
        if (score > bestScore) { bestScore = score; bestCol = c; }
    }
    return bestCol;
}
// ==================== End of AI Functions ====================

// ==================== FourInARow_UI Implementation ====================

/**
 * @brief Constructs the Four-in-a-Row UI.
 */
FourInARow_UI::FourInARow_UI() : UI<char>("======= 4 IN A ROW =======", 3) {
    player_difficulty[0] = 0;
    player_difficulty[1] = 0;
}

/**
 * @brief Creates a player for the game.
 * @param name Reference to the player's name.
 * @param symbol The player's symbol ('X' or 'O').
 * @param type The type of player (Human or AI).
 * @return Pointer to the created Player object.
 */
Player<char>* FourInARow_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "AI")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

/**
 * @brief Sets up both players with names, types, and AI difficulty.
 * @return Array of pointers to the two Player objects.
 */
Player<char>** FourInARow_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "AI" };

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);

    if(typeX == PlayerType::AI) {
        cout << "Select difficulty for AI Player X (1-Easy, 2-Hard): ";
        int diff;
        cin >> diff;
        player_difficulty[0] = (diff == 2) ? 2 : 1;
    }

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);

    if(typeO == PlayerType::AI) {
        cout << "Select difficulty for AI Player O (1-Easy, 2-Hard): ";
        int diff;
        cin >> diff;
        player_difficulty[1] = (diff == 2) ? 2 : 1;
    }


    return players;
}

/**
 * @brief Gets the player type choice from user input.
 * @param player_label Label for the player being configured.
 * @param options List of type options to display.
 * @return The selected PlayerType.
 */
PlayerType FourInARow_UI::get_player_type_choice(string player_label, const vector<string>& options) {
    cout << "Choose " << player_label << " type:\n";
    for (size_t i = 0; i < options.size(); ++i)
        cout << i + 1 << ". " << options[i] << "\n";
    int choice;
    cin >> choice;
    
    return (choice == 2) ? PlayerType::AI : PlayerType::HUMAN;
}

/**
 * @brief Gets a move from the player.
 * @param player Pointer to the current player.
 * @return Pointer to a Move object with the selected column.
 *
 * For humans: prompts for column input (0-6).
 * For AI: uses minimax to find optimal column.
 */
Move<char>* FourInARow_UI::get_move(Player<char>* player) {
    int col;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n hey " << player->get_name() << " (" << player->get_symbol() << "), enter column (0 to 6): ";
        cin >> col;
    }
    else if (player->get_type() == PlayerType::AI) {
        FourInARow_Board* boardPtr = dynamic_cast<FourInARow_Board*>(player->get_board_ptr());
        
        char aiSymbol = player->get_symbol();
        char playerSymbol = (aiSymbol == 'X') ? 'O' : 'X';
        
        int playerIndex = (aiSymbol == 'X') ? 0 : 1;
        int depth = (player_difficulty[playerIndex] == 1) ? 2 : 5;
        cout << "AI Player " << player->get_name() << " is thinking...\n";
        col = findBestMove(boardPtr, aiSymbol, playerSymbol, depth);
        cout << "\nAI Computer plays column: " << col << endl;
    }
    if(col < 0 || col > 6) {
        cout << "Invalid column. Please choose between 0 and 6.\n";
        return get_move(player);
    }
    return new Move<char>(0, col, player->get_symbol());
}

/**
 * @brief Launches the Four-in-a-Row game.
 *
 * Creates the board, sets up players, and runs the game loop.
 */
void FourInARow_UI::launch() {
    srand(static_cast<unsigned int>(time(0)));

    FourInARow_Board* board = new FourInARow_Board();
    set_board(board);
    Player<char>** players = setup_players();

    GameManager<char> game(board, players, this);
    game.run();

    delete board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
}
