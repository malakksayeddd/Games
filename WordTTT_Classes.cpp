/**
 * @file WordTTT_Classes.cpp
 * @brief Implementation of Word Tic-Tac-Toe game classes.
 *
 * Word TTT uses a 3x3 board where players place letters from A-Z.
 * The goal is to form a valid 3-letter English word from a dictionary
 * in any row, column, or diagonal.
 */

#include "WordTTT_Classes.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

/**
 * @brief Constructs an empty 3x3 Word TTT board.
 *
 * Initializes all cells to '_' (empty) and loads the dictionary file.
 */
WordTTT_Board::WordTTT_Board() : Board<char>(3, 3) {
    for (int r = 0; r < rows; r++) 
        for (int c = 0; c < columns; c++)
            board[r][c] = '_';

    load_dictionary("dic.txt");
}

/**
 * @brief Loads valid 3-letter words from a dictionary file.
 * @param path Path to the dictionary file (e.g., "dic.txt").
 *
 * Clears any existing dictionary, reads the file, and stores
 * all 3-letter words in lowercase.
 */
void WordTTT_Board::load_dictionary(const string& path) {
    dictionary.clear();
    ifstream in(path);
    if (!in.is_open()) {
        cerr << "dic.txt not found\n";
        return;
    }
    string w;
    while (in >> w) {
        if (w.size() == 3) {
            transform(w.begin(), w.end(), w.begin(), ::tolower);
            dictionary.insert(w);
        }
    }
}

/**
 * @brief Checks if a word exists in the dictionary.
 * @param w The word to validate.
 * @return true if the word is in the dictionary, false otherwise.
 */
bool WordTTT_Board::is_valid_word(const string& w) const {
    return (dictionary.find(w) != dictionary.end());
}

/**
 * @brief Updates the board with a player's move.
 * @param move Pointer to the move containing position and letter.
 * @return true if the move is valid and applied, false otherwise.
 *
 * Validates that the position is within bounds and the cell is empty.
 * Converts the letter to lowercase before placing.
 */
bool WordTTT_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char letter = tolower(move->get_symbol());

    if (r < 0 || r >= rows || c < 0 || c >= columns) return false;
    if (board[r][c] != '_') return false;

    board[r][c] = letter;
    n_moves++;
    return true;
}

/**
 * @brief Checks if any valid word has been formed.
 * @param player Unused parameter.
 * @return true if a valid word exists in any row, column, or diagonal.
 *
 * Checks all 3 rows, 3 columns, and 2 diagonals for complete valid words.
 */
bool WordTTT_Board::is_win(Player<char>*) {

    // Check rows
    for (int r = 0; r < 3; r++) {
        string w = "";
        w += board[r][0];
        w += board[r][1];
        w += board[r][2];
        if (w.find('_') == string::npos && is_valid_word(w))
            return true;
    }

    // Check columns
    for (int c = 0; c < 3; c++) {
        string w = "";
        w += board[0][c];
        w += board[1][c];
        w += board[2][c];
        if (w.find('_') == string::npos && is_valid_word(w))
            return true;
    }

    // Check main diagonal
    string w1 = "";
    w1 += board[0][0];
    w1 += board[1][1];
    w1 += board[2][2];
    if (w1.find('_') == string::npos && is_valid_word(w1)) return true;

    // Check anti-diagonal
    string w2 = "";
    w2 += board[2][0];
    w2 += board[1][1];
    w2 += board[0][2];
    if (w2.find('_') == string::npos && is_valid_word(w2)) return true;

    return false;
}

/**
 * @brief Checks if the game is a draw.
 * @param player Unused parameter.
 * @return true if the board is full with no valid words, false otherwise.
 */
bool WordTTT_Board::is_draw(Player<char>*) {
    if (is_win(nullptr)) return false;

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == '_')
                return false;

    return true;
}

/**
 * @brief Checks if the game is over.
 * @param p Pointer to a player (unused).
 * @return true if there's a valid word or the board is full.
 */
bool WordTTT_Board::game_is_over(Player<char>* p) { 
    return is_win(p) || is_draw(p);
}

/**
 * @brief Gets all empty cell positions on the board.
 * @return Vector of (row, column) pairs for cells marked with '_'.
 */
vector<pair<int, int>> WordTTT_Board::get_empty_cells() const {
    vector<pair<int, int>> v;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == '_')
                v.push_back({ r, c });
    return v;
}



/**
 * @brief Gets a move from the player (human or AI).
 * @param player Pointer to the current player.
 * @return Pointer to a WordTTT_Move with position and letter.
 *
 * For human players: prompts for row, column, and letter input.
 * For AI players: uses a multi-level strategy:
 * 1. Try to win by completing a valid word
 * 2. Block opponent from winning
 * 3. Choose a letter that could lead to a valid word
 * 4. Random move as fallback
 */
Move<char>* WordTTT_UI::get_move(Player<char>* player) {
    WordTTT_Board* b = dynamic_cast<WordTTT_Board*>(player->get_board_ptr());
    auto empty = b->get_empty_cells();

    if (empty.empty()) return nullptr;

    if (player->get_type() == PlayerType::HUMAN) {
        int r, c;
        char letter;
        std::cout << player->get_name() << " enter row column letter: ";
        std::cin >> r >> c >> letter;
        return new WordTTT_Move(r, c, letter);
    }
    else { // AI player
        
        // Strategy 1: Try to win by placing a letter that completes a valid word
        for (size_t i = 0; i < empty.size(); i++) {
            int r = empty[i].first;
            int c = empty[i].second;

            for (char l = 'a'; l <= 'z'; l++) {
                b->set_cell(r, c, l);
                if (b->is_win(player)) {
                    b->set_cell(r, c, '_');
                    std::cout << player->get_name() << " played (" << r << "," << c << ") letter: " << l << "\n";
                    return new WordTTT_Move(r, c, l);
                }
                b->set_cell(r, c, '_');
            }
        }

        // Strategy 2: Block opponent from winning
        Player<char>* opponent = nullptr; 
        for (size_t i = 0; i < empty.size(); i++) {
            int r = empty[i].first;
            int c = empty[i].second;

            for (char l = 'a'; l <= 'z'; l++) {
                b->set_cell(r, c, l);
                if (b->is_win(opponent)) {
                    b->set_cell(r, c, '_');
                    std::cout << player->get_name() << " played (" << r << "," << c << ") letter: " << l << "\n";
                    return new WordTTT_Move(r, c, l);
                }
                b->set_cell(r, c, '_');
            }
        }

        // Strategy 3: Choose a promising move that could lead to a valid word
        for (size_t i = 0; i < empty.size(); i++) {
            int r = empty[i].first;
            int c = empty[i].second;

            for (char l = 'a'; l <= 'z'; l++) {
                b->set_cell(r, c, l);
                bool promising = false;
                for (auto& w : b->get_dictionary()) {
                    bool match = true;
                    int idx = 0;
                    for (int row = 0; row < 3; row++) {
                        for (int col = 0; col < 3; col++, idx++) {
                            char cell = b->get_cell(row, col);
                            if (cell != '_' && cell != w[idx]) {
                                match = false;
                                break;
                            }
                        }
                        if (!match) break;
                    }
                    if (match) {
                        promising = true;
                        break;
                    }
                }

                if (promising) {
                    b->set_cell(r, c, '_');
                    std::cout << player->get_name() << " played (" << r << "," << c << ") letter: " << l << "\n";
                    return new WordTTT_Move(r, c, l);
                }

                b->set_cell(r, c, '_');
            }
        }

        // Strategy 4: Random fallback - pick a random empty cell and letter
        srand(time(NULL));
        size_t choice_index = rand() % empty.size();
        int r = empty[choice_index].first;
        int c = empty[choice_index].second;
        char letter = 'a' + (rand() % 26);
        std::cout << player->get_name() << " played (" << r << "," << c << ") letter: " << letter << "\n";
        return new WordTTT_Move(r, c, letter);
    }
}

/**
 * @brief Creates a player for the Word TTT game.
 * @param name Reference to the player's name (filled via input if empty for humans).
 * @param symbol The player's symbol (not used for word game).
 * @param type The type of player (Human or AI).
 * @return Pointer to the newly created Player object.
 */
Player<char>* WordTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::HUMAN) {
        if (name.empty()) {
            cout << "Enter name: ";
            getline(cin >> ws, name);
        }
    }
    else {
        name = "AI";
    }

    return new Player<char>(name, symbol, type);
}
