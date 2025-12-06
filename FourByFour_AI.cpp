/**
 * @file FourByFour_AI.cpp
 * @brief Implementation of the AI player for 4x4 Tic-Tac-Toe.
 *
 * Contains the Minimax algorithm implementation for finding optimal moves.
 */

#include "FourByFour_AI.h"
#include <limits>

/**
 * @brief Constructs an AI player with the given symbol.
 * @param symbol The AI's playing symbol ('X' or 'O').
 */
FourByFour_AI::FourByFour_AI(char symbol) {
    ai_symbol = symbol;
    human_symbol = (symbol == 'X' ? 'O' : 'X');
}

/**
 * @brief Finds and returns the best move for the AI.
 * 
 * Evaluates all possible moves using minimax and selects
 * the one with the highest score.
 * 
 * @param board Pointer to the current game board.
 * @return Pointer to the optimal Move object.
 */
Move<char>* FourByFour_AI::get_best_move(FourByFour_Board* board) {
    int bestScore = std::numeric_limits<int>::min();
    Move<char>* bestMove = nullptr;

    auto& b = board->get_board();

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {

            if (b[x][y] == ai_symbol) {

                int dx[4] = {1, -1, 0, 0};
                int dy[4] = {0, 0, 1, -1};

                for (int d = 0; d < 4; d++) {

                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    FourByFour_Move* m = new FourByFour_Move(x, y, nx, ny, ai_symbol);

                    if (board->update_board(m)) {

                        int score = minimax(board, 0, false);

                        // Backtracking - restore original position
                        auto& bb = board->get_board();
                        bb[x][y] = ai_symbol;
                        bb[nx][ny] = '.';

                        if (score > bestScore) {
                            bestScore = score;
                            bestMove = new FourByFour_Move(x, y, nx, ny, ai_symbol);
                        }}

                    delete m;
                }}}}
    return bestMove;}

/**
 * @brief Minimax algorithm for evaluating board positions.
 * 
 * Recursively evaluates game states to find the optimal score.
 * Uses a depth limit of 4 to prevent excessive computation.
 * 
 * @param board Pointer to the game board.
 * @param depth Current search depth.
 * @param maximizing True if AI's turn (maximizing), false otherwise.
 * @return Score value: positive favors AI, negative favors human.
 */
int FourByFour_AI::minimax(FourByFour_Board* board, int depth, bool maximizing) {


    if (board->check_three_in_line(ai_symbol)) return 100 - depth;
    if (board->check_three_in_line(human_symbol)) return -100 + depth;

    if (depth >= 4) return 0;

    auto& b = board->get_board();

    if (maximizing) {
        int best = std::numeric_limits<int>::min();

        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {

                if (b[x][y] == ai_symbol) {

                    int dx[4] = {1, -1, 0, 0};
                    int dy[4] = {0, 0, 1, -1};

                    for (int d = 0; d < 4; d++) {

                        int nx = x + dx[d];
                        int ny = y + dy[d];

                        FourByFour_Move* m = new FourByFour_Move(x, y, nx, ny, ai_symbol);

                        if (board->update_board(m)) {

                            int score = minimax(board, depth + 1, false);

                          // Backtracking - restore position
                            b[x][y] = ai_symbol;
                            b[nx][ny] = '.';

                            best = std::max(best, score);
                        }

                        delete m;}}}}
        return best;}

    else {
        int best = std::numeric_limits<int>::max();

        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {

                if (b[x][y] == human_symbol) {

                    int dx[4] = {1, -1, 0, 0};
                    int dy[4] = {0, 0, 1, -1};

                    for (int d = 0; d < 4; d++) {

                        int nx = x + dx[d];
                        int ny = y + dy[d];

                        FourByFour_Move* m = new FourByFour_Move(x, y, nx, ny, human_symbol);

                        if (board->update_board(m)) {

                            int score = minimax(board, depth + 1, true);

                            // Backtracking - restore position
                            b[x][y] = human_symbol;
                            b[nx][ny] = '.';

                            best = std::min(best, score);
                        }

                        delete m;
                    }}}}

        return best;
    }
}
