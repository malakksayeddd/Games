#include "SUS_Classes.h"
#include <limits>
#include <algorithm>

//board
SUS_Board::SUS_Board() : Board<char>(3, 3), sequences(0) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = '_';
}
//thot S aw U lw el cell fadya
bool SUS_Board::place(int r, int c, char sym) {
    if (r < 0 || r >= 3 || c < 0 || c >= 3) return false;
    if (board[r][c] != '_') return false;
    board[r][c] = sym;
    return true;
}
//yerg3 elcell fadya
void SUS_Board::undo(int r, int c) {
    board[r][c] = '_';
}
//read elcell
char SUS_Board::getCell(int r, int c) {
    return board[r][c];
}

int SUS_Board::countSequences() {
    int cnt = 0;
    for (int r = 0; r < 3; r++)
        if (seq(board[r][0], board[r][1], board[r][2])) cnt++; //ye3d kol el seqs
    for (int c = 0; c < 3; c++)
        if (seq(board[0][c], board[1][c], board[2][c])) cnt++; //check lw fe seq sah
    if (seq(board[0][0], board[1][1], board[2][2])) cnt++;
    if (seq(board[0][2], board[1][1], board[2][0])) cnt++;
    return cnt;
}

int SUS_Board::getSequences() const { return sequences; }
void SUS_Board::setSequences(int s) { sequences = s; }

bool SUS_Board::full() { //check lw kol el cells full
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == '_') return false;
    return true;
}
//shakl el board
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
bool SUS_Board::update_board(Move<char>* move) {
    return place(move->get_x(), move->get_y(), move->get_symbol());
}

bool SUS_Board::is_win(Player<char>* p) {
    return countSequences() > 0; 
}

bool SUS_Board::is_lose(Player<char>* p) {
    return false;
}

bool SUS_Board::is_draw(Player<char>* p) { //le mafesh ai seq
    return full() && countSequences() == 0;
}

bool SUS_Board::game_is_over(Player<char>* p) {
    return full();
}
SUS_Game::SUS_Game(string name1, string name2, bool ai)
    : player1(name1), player2(name2), vsAI(ai),
    scoreP1(0), scoreP2(0), turnP1(true) { 
} //score l seq kol player

int evaluateBoard(SUS_Board& b) {
    return b.countSequences();
}

int minimax(SUS_Board& b, bool isMax, int depth) {
    int score = evaluateBoard(b);
    if (depth == 0 || b.full()) return score;

    if (isMax) { //ai turn: U
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
    else { //player S
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
