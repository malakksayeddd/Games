#include "SUS_Classes.h"

//BOARD 

SUS_Board::SUS_Board() {
    sequences = 0;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = '_';
}

bool SUS_Board::place(int r, int c, char symbol) {
    if (r < 0 || r >= 3 || c < 0 || c >= 3) return false;
    if (board[r][c] != '_') return false;
    board[r][c] = symbol;
    return true;
}

void SUS_Board::undo(int r, int c) {
    board[r][c] = '_';
}

char SUS_Board::getCell(int r, int c) {
    return board[r][c];
}

static bool seq(char a, char b, char c) {
    return (a == 'S' && b == 'U' && c == 'S');
}

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

int SUS_Board::getSequences() {
    return sequences;
}

void SUS_Board::setSequences(int s) {
    sequences = s;
}

bool SUS_Board::full() {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == '_') return false;
    return true;
}

void SUS_Board::display() {
    cout << "\n    0   1   2\n";
    cout << "  -------------\n";
    for (int r = 0; r < 3; r++) {
        cout << r << " |";
        for (int c = 0; c < 3; c++) {
            cout << " " << board[r][c] << " |";
        }
        cout << "\n  -------------\n";
    }
}

//GAME 

SUS_Game::SUS_Game(string name1, string name2, bool ai) {
    player1 = name1;
    player2 = name2;
    vsAI = ai;

    scoreP1 = 0;
    scoreP2 = 0;
    turnP1 = true;
}

int evaluateBoard(SUS_Board& b) {
    return b.countSequences();
}

int minimax(SUS_Board& b, bool isMax, int depth) {
    int score = evaluateBoard(b);

    if (depth == 0 || b.full())
        return score;

    if (isMax) { // AI turn: U
        int best = -999;
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                if (b.getCell(r, c) == '_') {
                    b.place(r, c, 'U');
                    int val = minimax(b, false, depth - 1);
                    b.undo(r, c);
                    best = max(best, val);
                }
            }
        }
        return best;
    }
    else { // player S
        int best = 999;
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                if (b.getCell(r, c) == '_') {
                    b.place(r, c, 'S');
                    int val = minimax(b, true, depth - 1);
                    b.undo(r, c);
                    best = min(best, val);
                }
            }
        }
        return best;
    }
}

pair<int, int> SUS_Game::bestMove() {
    int bestScore = -999;
    pair<int, int> best = { -1,-1 };

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board.getCell(r, c) == '_') {
                board.place(r, c, 'U');

                int val = minimax(board, false, 4);

                board.undo(r, c);

                if (val > bestScore) {
                    bestScore = val;
                    best = { r,c };
                }
            }
        }
    }
    return best;
}

void SUS_Game::play() {
    cout << "\n SUS GAME: \n";
    cout << player1 << " = S\n"
        << player2 << " = U\n\n";

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
                r = mv.first;
                c = mv.second;
                cout << "\nAI played: " << r << ", " << c << "\n";
            }
            else {
                cout << "\n" << player2 << " (U), enter row col: ";
                cin >> r >> c;
            }
        }

        if (!board.place(r, c, turnP1 ? 'S' : 'U')) {
            cout << "Invalid move try again\n";
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

    cout << "\n FINAL SCORES: \n";
    cout << player1 << " (S): " << scoreP1 << endl;
    cout << player2 << " (U): " << scoreP2 << endl;

    if (scoreP1 > scoreP2)
        cout << "Winner: " << player1 << endl;
    else if (scoreP2 > scoreP1)
        cout << "Winner: " << player2 << endl;
    else
        cout << "Draw!\n";
}
