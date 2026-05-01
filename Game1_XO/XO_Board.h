#ifndef XO_BOARD_H
#define XO_BOARD_H

#include "../BoardGame_Classes.h"
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>

// ============================================================
//                     X_O_Board Class
// ============================================================
template <typename T>
class X_O_Board : public Board<T> {
public:
    X_O_Board();
    ~X_O_Board();

    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

// ============================================================
//                     X_O_Player Class
// ============================================================
template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

// ============================================================
//                  X_O_Random_Player Class
// ============================================================
template <typename T>
class X_O_Random_Player : public RandomPlayer<T> {
public:
    X_O_Random_Player(T symbol);
    void getmove(int& x, int& y) override;
};

// ============================================================
//                      IMPLEMENTATIONS
// ============================================================

// --- X_O_Board ---
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 3;
    this->n_moves = 0;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++)
            this->board[i][j] = 0;
    }
}

template <typename T>
X_O_Board<T>::~X_O_Board() {
    for (int i = 0; i < this->rows; i++)
        delete[] this->board[i];
    delete[] this->board;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns)
        return false;
    if (mark == 0) {
        this->n_moves--;
        this->board[x][y] = 0;
        return true;
    }
    if (this->board[x][y] == 0) {
        this->n_moves++;
        this->board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

template <typename T>
void X_O_Board<T>::display_board() {
    cout << "\n";
    for (int i = 0; i < this->rows; i++) {
        cout << "  ";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0)
                cout << "(" << i << "," << j << ")";
            else
                cout << "  " << this->board[i][j] << "  ";
            if (j < this->columns - 1) cout << " | ";
        }
        cout << "\n";
        if (i < this->rows - 1)
            cout << "  ------+-------+------\n";
    }
    cout << "\n";
}

template <typename T>
bool X_O_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] && this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2])
            return true;
        if (this->board[0][i] && this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i])
            return true;
    }
    // Check diagonals
    if (this->board[0][0] && this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2])
        return true;
    if (this->board[0][2] && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0])
        return true;
    return false;
}

template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// --- X_O_Player ---
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    cout << this->name << " (" << this->symbol << "), enter row and col (0-2): ";
    string line;
    // flush leftover newline then read full line
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, line);
    // replace any non-digit (dash, comma, space, etc.) with space
    for (char& c : line) if (!isdigit(c)) c = ' ';
    istringstream ss(line);
    if (!(ss >> x >> y)) { x = -1; y = -1; }  // force invalid → retry
}

// --- X_O_Random_Player ---
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    cout << this->name << " (" << this->symbol << ") plays: (" << x << "," << y << ")\n";
}

#endif // XO_BOARD_H
