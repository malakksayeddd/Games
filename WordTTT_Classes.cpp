#include "WordTTT_Classes.h"
#include <iostream>
#include <fstream> //3shan t2ra el dic.txt
#include <ctime>
using namespace std;

WordTTT_Board::WordTTT_Board() : Board<char>(3, 3) { //constractour WordTTT_Board w bakhod mn el parent constractour board 3*3
    for (int r = 0; r < rows; r++) 
        for (int c = 0; c < columns; c++)
            board[r][c] = '_'; //ay cell fadya _

    load_dictionary("dic.txt"); //load dic.txt
}

void WordTTT_Board::load_dictionary(const string& path) {
    dictionary.clear(); //clear ai words 2bl kda
    ifstream in(path); //open file to read 
    if (!in.is_open()) { //check lw elfile mawgod 
        cerr << "dic.txt not found\n"; //lw ml2thsh
        return;
    }
    string w;
    while (in >> w) { //to read all words fel file
        if (w.size() == 3) { //bakhod kol el words el 3 herof 
            transform(w.begin(), w.end(), w.begin(), ::tolower); //ahwelhom l lowercase
            dictionary.insert(w); //edakh el klma fel set
        }
    }
}

bool WordTTT_Board::is_valid_word(const string& w) const { //check el klma fel file lw ah true lw la false
    return (dictionary.find(w) != dictionary.end());
}

bool WordTTT_Board::update_board(Move<char>* move) {
    int r = move->get_x(); //row
    int c = move->get_y(); //colunm
    char letter = tolower(move->get_symbol()); //check eno lowercase

    if (r < 0 || r >= rows || c < 0 || c >= columns) return false; //check mafesh input bara el board
    if (board[r][c] != '_') return false; //check cell empty

    board[r][c] = letter; //put el harf
    n_moves++; //azawed moves
    return true; //done
}

bool WordTTT_Board::is_win(Player<char>*) {

    //rows
    for (int r = 0; r < 3; r++) {
        string w = "";
        w += board[r][0];
        w += board[r][1];
        w += board[r][2];
        if (w.find('_') == string::npos && is_valid_word(w))
            return true;
    }

    //columns
    for (int c = 0; c < 3; c++) {
        string w = "";
        w += board[0][c];
        w += board[1][c];
        w += board[2][c];
        if (w.find('_') == string::npos && is_valid_word(w))
            return true;
    }

    //diagonal 1
    string w1 = "";
    w1 += board[0][0];
    w1 += board[1][1];
    w1 += board[2][2];
    if (w1.find('_') == string::npos && is_valid_word(w1)) return true;

    //diagonal 2
    string w2 = "";
    w2 += board[2][0];
    w2 += board[1][1];
    w2 += board[0][2];
    if (w2.find('_') == string::npos && is_valid_word(w2)) return true;

    return false;
}

bool WordTTT_Board::is_draw(Player<char>*) { // lw el board full w mafesh winner
    if (is_win(nullptr)) return false;

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == '_')
                return false;

    return true;
}

bool WordTTT_Board::game_is_over(Player<char>* p) { 
    return is_win(p) || is_draw(p);
}

vector<pair<int, int>> WordTTT_Board::get_empty_cells() const { //tegma3 kol empty cells 3shan ai
    vector<pair<int, int>> v;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == '_')
                v.push_back({ r, c });
    return v;
}



//function l tahded harka el ai w player
Move<char>* WordTTT_UI::get_move(Player<char>* player) {
    WordTTT_Board* b = dynamic_cast<WordTTT_Board*>(player->get_board_ptr());
    auto empty = b->get_empty_cells(); //ashof elempty cells

    if (empty.empty()) return nullptr; //lw mafesh cells empty 

    if (player->get_type() == PlayerType::HUMAN) { // lw human hatlob row w colunm
        int r, c;
        char letter;
        std::cout << player->get_name() << " enter row column letter: ";
        std::cin >> r >> c >> letter;
        return new WordTTT_Move(r, c, letter);
    }
    else { //ai
        
        for (size_t i = 0; i < empty.size(); i++) { //put letter to win
            int r = empty[i].first;
            int c = empty[i].second;

            for (char l = 'a'; l <= 'z'; l++) { //bygrab mn a-z fe kol cells lw f harka tkseb
                b->set_cell(r, c, l); //yehot el harf m2akat
                if (b->is_win(player)) { //check lw htkaseb
                    b->set_cell(r, c, '_'); //lw msh hyksb yrga3ha empty
                    std::cout << player->get_name() << " played (" << r << "," << c << ") letter: " << l << "\n";
                    return new WordTTT_Move(r, c, l);
                }
                b->set_cell(r, c, '_');
            }
        }

        
        Player<char>* opponent = nullptr; 
        for (size_t i = 0; i < empty.size(); i++) { //lw el player hyksab yehawel ymna3o
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

        //lw mafesh harka smart yb2a ai cell fadya
        srand(time(NULL));
        size_t choice_index = rand() % empty.size();
        int r = empty[choice_index].first;
        int c = empty[choice_index].second;
        char letter = 'a' + (rand() % 26);
        std::cout << player->get_name() << " played (" << r << "," << c << ") letter: " << letter << "\n";
        return new WordTTT_Move(r, c, letter);
    }
}

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
