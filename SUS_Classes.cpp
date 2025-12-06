/**
 * @file SUS_Classes.cpp
 * @brief Implementation of the SUS game classes.
 *
 * SUS is a 3x3 board game where one player places 'S' and the other places 'U'.
 * Players score points by creating "SUS" sequences in rows, columns, or diagonals.
 * The player with the most sequences when the board is full wins.
 */

#include "SUS_Classes.h"
#include <limits>
#include <algorithm>

// ==================== SUS_Board Implementation ====================

/**
 * @brief Constructs an empty 3x3 SUS board.
 *
 * Initializes all cells to '_' (empty) and sets sequence count to 0.
 */
SUS_Board::SUS_Board() : Board<char>(3, 3), sequences(0) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = '_';
}

/**
 * @brief Places a symbol (S or U) on the board.
 * @param r Row index (0-2).
 * @param c Column index (0-2).
 * @param sym The symbol to place ('S' or 'U').
 * @return true if placement successful, false if invalid or cell occupied.
 */
bool SUS_Board::place(int r, int c, char sym) {
    if (r < 0 || r >= 3 || c < 0 || c >= 3) return false;
    if (board[r][c] != '_') return false;
    board[r][c] = sym;
    return true;
}

/**
 * @brief Undoes a move by clearing a cell.
 * @param r Row index.
 * @param c Column index.
 */
void SUS_Board::undo(int r, int c) {
    board[r][c] = '_';
}

/**
 * @brief Gets the character at a cell.
 * @param r Row index.
 * @param c Column index.
 * @return The character at position (r, c).
 */
char SUS_Board::getCell(int r, int c) {
    return board[r][c];
}

/**
 * @brief Counts the total number of "SUS" sequences on the board.
 * @return The number of valid SUS sequences found.
 *
 * Checks all 3 rows, 3 columns, and 2 diagonals for "SUS" patterns.
 */
int SUS_Board::countSequences() {
    int cnt = 0;
    for (int r = 0; r < 3; r++)
        if (seq(board[r][0], board[r][1], board[r][2])) cnt++;
    for (int c = 0; c < 3; c++)
        if (seq(board[0][c], board[1][c], board[2][c])) cnt++;
    if (seq(board[0][0], board[1][1], board[2][2])) cnt++;
    if (seq(board[0][2], board[1][1], board[2][0])) cnt++;
    return cnt;
}

/**
 * @brief Gets the current sequence count.
 * @return Number of sequences tracked.
 */
int SUS_Board::getSequences() const { return sequences; }

/**
 * @brief Sets the sequence count.
 * @param s The new sequence count.
 */
void SUS_Board::setSequences(int s) { sequences = s; }

/**
 * @brief Checks if the board is completely filled.
 * @return true if all 9 cells are occupied, false otherwise.
 */
bool SUS_Board::full() {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == '_') return false;
    return true;
}

/**
 * @brief Displays the board to the console.
 *
 * Shows a formatted 3x3 grid with row/column indices.
 */
void SUS_Board::display() {
    cout << "\n    0   1   2\n";
    cout << "  -------------\n";
    for (int r = 0; r < 3; r++) {
        cout << r << " |";
        for (int c = 0; c < 3; c++)
            cout << " " << board[r][c] << " |";
        cout << "\n  -------------\n";
    }
}

/**
 * @brief Updates the board with a move (Board interface).
 * @param move Pointer to the move.
 * @return true if successful, false otherwise.
 */
bool SUS_Board::update_board(Move<char>* move) {
    return place(move->get_x(), move->get_y(), move->get_symbol());
}

/**
 * @brief Checks if there are any SUS sequences (Board interface).
 * @param p Unused parameter.
 * @return true if any sequences exist.
 */
bool SUS_Board::is_win(Player<char>* p) {
    return countSequences() > 0; 
}

/**
 * @brief Checks if the player has lost (Board interface).
 * @param p Unused parameter.
 * @return Always returns false.
 */
bool SUS_Board::is_lose(Player<char>* p) {
    return false;
}

/**
 * @brief Checks if the game is a draw (Board interface).
 * @param p Unused parameter.
 * @return true if board is full with no sequences.
 */
bool SUS_Board::is_draw(Player<char>* p) {
    return full() && countSequences() == 0;
}

/**
 * @brief Checks if the game is over (Board interface).
 * @param p Unused parameter.
 * @return true if the board is full.
 */
bool SUS_Board::game_is_over(Player<char>* p) {
    return full();
}

// ==================== SUS_Game Implementation ====================

/**
 * @brief Constructs a SUS game with two players.
 * @param name1 Name of Player 1 (plays 'S').
 * @param name2 Name of Player 2 (plays 'U').
 * @param ai true if Player 2 is AI, false for human.
 */
SUS_Game::SUS_Game(string name1, string name2, bool ai)
    : player1(name1), player2(name2), vsAI(ai),
    scoreP1(0), scoreP2(0), turnP1(true) { 
}

/**
 * @brief Evaluates the current board state.
 * @param b Reference to the board.
 * @return The number of SUS sequences.
 */
int evaluateBoard(SUS_Board& b) {
    return b.countSequences();
}

/**
 * @brief Minimax algorithm for AI move selection.
 * @param b Reference to the board.
 * @param isMax true if maximizing player's turn (AI/U).
 * @param depth Search depth limit.
 * @return The evaluation score.
 *
 * AI (U) maximizes, Player (S) minimizes.
 */
int minimax(SUS_Board& b, bool isMax, int depth) {
    int score = evaluateBoard(b);
    if (depth == 0 || b.full()) return score;

    if (isMax) { // AI turn: U
        int best = -999;
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                if (b.getCell(r, c) == '_') {
                    b.place(r, c, 'U');
                    int val = minimax(b, false, depth - 1);
                    b.undo(r, c);
                    best = max(best, val);
                }
        return best;
    }
    else { // Player S
        int best = 999;
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                if (b.getCell(r, c) == '_') {
                    b.place(r, c, 'S');
                    int val = minimax(b, true, depth - 1);
                    b.undo(r, c);
                    best = min(best, val);
                }
        return best;
    }
}

/**
 * @brief Finds the best move for the AI player.
 * @return Pair of (row, column) for the best move.
 *
 * Uses minimax with depth 4 to evaluate all possible moves.
 */
pair<int, int> SUS_Game::bestMove() {
    int bestScore = -999;
    pair<int, int> best = { -1,-1 };
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board.getCell(r, c) == '_') {
                board.place(r, c, 'U');
                int val = minimax(board, false, 4);
                board.undo(r, c);
                if (val > bestScore) {
                    bestScore = val;
                    best = { r,c };
                }
            }
    return best;
}

/**
 * @brief Main game loop for SUS.
 *
 * Alternates turns between players, tracks scores based on SUS sequences,
 * and declares the winner when the board is full.
 */
void SUS_Game::play() {
    cout << "\n SUS GAME: \n";
    cout << player1 << " = S\n" << player2 << " = U\n\n";

    while (!board.full()) {
        board.display();
        int r, c;

        if (turnP1) {
            cout << "\n" << player1 << " (S), enter row col: ";
            cin >> r >> c;
        }
        else {
            if (vsAI) {
                auto mv = bestMove();
                r = mv.first; c = mv.second;
                cout << "\nAI played: " << r << ", " << c << "\n";
            }
            else {
                cout << "\n" << player2 << " (U), enter row col: ";
                cin >> r >> c;
            }
        }

        if (!board.place(r, c, turnP1 ? 'S' : 'U')) {
            cout << "Invalid move, try again\n";
            continue;
        }

        int oldSeq = board.getSequences();
        int newSeq = board.countSequences();
        int diff = newSeq - oldSeq;

        if (diff > 0) {
            if (turnP1) scoreP1 += diff;
            else scoreP2 += diff;
        }

        board.setSequences(newSeq);
        turnP1 = !turnP1;
    }

    board.display();
    cout << "\nFINAL SCORES:\n";
    cout << player1 << " (S): " << scoreP1 << endl;
    cout << player2 << " (U): " << scoreP2 << endl;

    if (scoreP1 > scoreP2) cout << "Winner: " << player1 << endl;
    else if (scoreP2 > scoreP1) cout << "Winner: " << player2 << endl;
    else cout << "Draw!\n";
}
