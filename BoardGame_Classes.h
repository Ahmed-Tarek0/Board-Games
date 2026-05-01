#ifndef _BOARDGAME_CLASSES_H
#define _BOARDGAME_CLASSES_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// ============================================================
//                        Board Class
// ============================================================
template <typename T>
class Board {
protected:
    int rows, columns;
    T** board;
    int n_moves = 0;

public:
    // Return true if move is valid and placed on board; false otherwise
    virtual bool update_board(int x, int y, T symbol) = 0;

    // Display the board and its pieces
    virtual void display_board() = 0;

    // Returns true if there is a winner
    virtual bool is_win() = 0;

    // Returns true if all moves are done and there is no winner
    virtual bool is_draw() = 0;

    // Returns true if the game is over (win or draw)
    virtual bool game_is_over() = 0;

    virtual ~Board() {}
};

// ============================================================
//                        Player Class
// ============================================================
template <typename T>
class Player {
protected:
    string name;
    T symbol;
    Board<T>* boardPtr;

public:
    Player(string n, T symbol);
    Player(T symbol); // For computer players (name defaults to "Computer")

    virtual void getmove(int& x, int& y) = 0;

    T      getsymbol();
    string getname();
    void   setBoard(Board<T>* b);

    virtual ~Player() {}
};

// ============================================================
//                    RandomPlayer Class
// ============================================================
template <typename T>
class RandomPlayer : public Player<T> {
protected:
    int dimension;
public:
    RandomPlayer(T symbol);
    virtual void getmove(int& x, int& y) = 0;
};

// ============================================================
//                    GameManager Class
// ============================================================
template <typename T>
class GameManager {
private:
    Board<T>*   boardPtr;
    Player<T>*  players[2];

public:
    GameManager(Board<T>* bPtr, Player<T>* playerPtr[2]);
    void run();
};

// ============================================================
//                     IMPLEMENTATIONS
// ============================================================

// --- Player ---
template <typename T>
Player<T>::Player(string n, T symbol) : name(n), symbol(symbol), boardPtr(nullptr) {}

template <typename T>
Player<T>::Player(T symbol) : name("Computer"), symbol(symbol), boardPtr(nullptr) {}

template <typename T>
string Player<T>::getname() { return name; }

template <typename T>
T Player<T>::getsymbol() { return symbol; }

template <typename T>
void Player<T>::setBoard(Board<T>* b) { boardPtr = b; }

// --- RandomPlayer ---
template <typename T>
RandomPlayer<T>::RandomPlayer(T symbol) : Player<T>(symbol) {}

// --- GameManager ---
template <typename T>
GameManager<T>::GameManager(Board<T>* bPtr, Player<T>* playerPtr[2]) {
    boardPtr   = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

template <typename T>
void GameManager<T>::run() {
    int x, y;
    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {
        for (int i : {0, 1}) {
            players[i]->getmove(x, y);
            while (!boardPtr->update_board(x, y, players[i]->getsymbol())) {
                cout << "Invalid move! Try again.\n";
                players[i]->getmove(x, y);
            }
            boardPtr->display_board();

            if (boardPtr->is_win()) {
                cout << players[i]->getname() << " wins!\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "It's a draw!\n";
                return;
            }
        }
    }
}

#endif // _BOARDGAME_CLASSES_H
