#ifndef WORD_PLAYERS_H
#define WORD_PLAYERS_H

#include "WordTicTacToe.h"
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <sstream>
#include <iostream>
using namespace std;

// ============================================================
//                   Word_Human_Player
//
//  Human enters: row col letter  (0-based row/col)
// ============================================================
class Word_Human_Player : public Player<char> {
public:
    Word_Human_Player(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->name << ", enter row col letter (e.g. 0 1 A): ";
        string line;
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, line);

        // Replace any non-alphanumeric separator with space
        for (char& c : line)
            if (!isdigit(c) && !isalpha(c)) c = ' ';

        istringstream ss(line);
        char letter = 0;
        if (!(ss >> x >> y >> letter)) { x = -1; y = -1; letter = 0; }

        if (letter) this->symbol = toupper(letter);
        else        this->symbol = 0;  // will cause retry
    }

    // Override getsymbol so GameManager gets the letter typed this turn
    char getsymbol() {
        return this->symbol;
    }
};

// ============================================================
//                   Word_Random_Player
//
//  Picks a random empty cell and a random uppercase letter.
// ============================================================
class Word_Random_Player : public RandomPlayer<char> {
public:
    Word_Random_Player(char symbol) : RandomPlayer<char>(symbol) {
        this->dimension = 3;
        this->name = "Random Computer";
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y) override {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
        this->symbol = 'A' + rand() % 26;
        cout << this->name << " plays (" << x << "," << y
             << ") with letter '" << this->symbol << "'\n";
    }

    char getsymbol() {
        return this->symbol;
    }
};

#endif // WORD_PLAYERS_H
