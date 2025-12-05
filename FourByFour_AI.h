/**
 * @file FourByFour_AI.h
 * @brief Defines the AI player for 4x4 Tic-Tac-Toe.
 *
 * Provides an AI implementation using the Minimax algorithm
 * for optimal move selection in the 4x4 variant.
 */

#ifndef FOURBYFOUR_AI_H
#define FOURBYFOUR_AI_H
#include "FourByFour_Board.h"

/**
 * @class FourByFour_AI
 * @brief AI player for the 4x4 Tic-Tac-Toe game.
 *
 * Uses the Minimax algorithm to determine the best move
 * by evaluating all possible game states.
 */
class FourByFour_AI {
public:
    /**
     * @brief Constructs an AI player with the given symbol.
     * @param symbol The AI's playing symbol ('X' or 'O').
     */
    FourByFour_AI(char symbol);

    /**
     * @brief Calculates and returns the best move for the AI.
     * @param board Pointer to the current game board.
     * @return Pointer to the optimal Move object.
     */
    Move<char>* get_best_move(FourByFour_Board* board);

private:
    char ai_symbol;    ///< The AI's playing symbol.
    char human_symbol; ///< The opponent's symbol.

    /**
     * @brief Minimax algorithm for evaluating board positions.
     * @param board Pointer to the game board.
     * @param depth Current search depth.
     * @param maximizing Whether the AI is maximizing or minimizing.
     * @return Score value for the board position.
     */
    int minimax(FourByFour_Board* board, int depth, bool maximizing);

};

#endif
