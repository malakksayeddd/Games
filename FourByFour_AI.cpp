#include "FourByFour_AI.h"
#include <limits>

FourByFour_AI::FourByFour_AI(char symbol) {
    ai_symbol = symbol;
    human_symbol = (symbol == 'X' ? 'O' : 'X');
}

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

                    Move<char>* m = new Move<char>(x, y, nx, ny, ai_symbol);

                    if (board->update_board(m)) {

                        int score = minimax(board, 0, false);

                        // el backtracking
                        auto& bb = board->get_board();
                        bb[x][y] = ai_symbol;
                        bb[nx][ny] = '.';

                        if (score > bestScore) {
                            bestScore = score;
                            bestMove = new Move<char>(x, y, nx, ny, ai_symbol);
                        }}

                    delete m;
                }}}}
    return bestMove;}

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

                        Move<char>* m = new Move<char>(x, y, nx, ny, ai_symbol);

                        if (board->update_board(m)) {

                            int score = minimax(board, depth + 1, false);

                          //el backtracking
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

                        Move<char>* m = new Move<char>(x, y, nx, ny, human_symbol);

                        if (board->update_board(m)) {

                            int score = minimax(board, depth + 1, true);

                            //el backtracking
                            b[x][y] = human_symbol;
                            b[nx][ny] = '.';

                            best = std::min(best, score);
                        }

                        delete m;
                    }}}}

        return best;
    }
}
