#ifndef PYRAMID_BOARD_H
#define PYRAMID_BOARD_H

#include "../BoardGame_Classes.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <cctype>

// ============================================================
//                  Pyramidic_X_O_Board Class
//
//  Board layout (3 rows, 5 cols, 1-indexed input):
//
//      Row 1:      col 3           (1 cell)
//      Row 2:    col 2,3,4         (3 cells)
//      Row 3:  col 1,2,3,4,5       (5 cells)
//
//  Player enters 1-based (row, col). Internally 0-based.
// ============================================================
class Pyramidic_X_O_Board : public Board<char> {
private:
    int minSeqLen;

    bool inBounds(int x, int y) const {
        return x >= 0 && x < rows
            && y >= columns / 2 - x
            && y <= columns / 2 + x;
    }

public:
    Pyramidic_X_O_Board() {
        rows      = 3;
        columns   = 5;
        n_moves   = 0;
        minSeqLen = 3;
        board = new char*[rows];
        for (int i = 0; i < rows; i++)
            board[i] = new char[columns]{};   // zero-initialised
    }

    ~Pyramidic_X_O_Board() {
        for (int i = 0; i < rows; i++)
            delete[] board[i];
        delete[] board;
    }

    // Input is 1-based; convert to 0-based internally
    bool update_board(int x, int y, char symbol) override {
        x--; y--;
        if (inBounds(x, y) && board[x][y] == 0) {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << "\n";
        for (int i = 0; i < rows; i++) {
            int offset = (columns - (2 * i + 1)) / 2;
            // leading spaces for pyramid shape
            cout << string(offset * 3, ' ');
            for (int j = 0; j < 2 * i + 1; j++) {
                int col = j + offset;
                if (board[i][col])
                    cout << "  " << board[i][col] << "  ";
                else
                    cout << "(" << (i+1) << "," << (col+1) << ")";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool is_win() override {
        int dx[] = {0,  1,  1, -1};
        int dy[] = {1,  0,  1,  1};

        for (int i = 0; i < rows; i++) {
            for (int j = columns / 2 - i; j <= columns / 2 + i; j++) {
                if (!board[i][j]) continue;
                for (int d = 0; d < 4; d++) {
                    int count = 1;
                    for (int k = 1; k < minSeqLen; k++) {
                        int nx = i + k * dx[d];
                        int ny = j + k * dy[d];
                        if (inBounds(nx, ny) && board[nx][ny] == board[i][j])
                            count++;
                        else
                            break;
                    }
                    if (count >= minSeqLen) return true;
                }
            }
        }
        return false;
    }

    // Total valid cells: 1 + 3 + 5 = 9
    bool is_draw() override {
        return (n_moves == 9 && !is_win());
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

// ============================================================
//                   Pyramid_Human_Player
// ============================================================
class Pyramid_Human_Player : public Player<char> {
public:
    Pyramid_Human_Player(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->name << " (" << this->symbol
             << "), enter row and col (1-based): ";
        string line;
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, line);
        for (char& c : line) if (!isdigit(c)) c = ' ';
        istringstream ss(line);
        if (!(ss >> x >> y)) { x = -1; y = -1; }
    }
};

// ============================================================
//                   Pyramid_Random_Player
//   Generates random valid positions inside the pyramid.
// ============================================================
class Pyramid_Random_Player : public RandomPlayer<char> {
public:
    Pyramid_Random_Player(char symbol) : RandomPlayer<char>(symbol) {
        this->name = "Random Computer";
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y) override {
        // Valid 1-based positions in the pyramid:
        //   Row 1: col 3
        //   Row 2: col 2,3,4
        //   Row 3: col 1,2,3,4,5
        // Total 9 cells — pick one uniformly at random
        int cells[9][2] = {
            {1,3},
            {2,2},{2,3},{2,4},
            {3,1},{3,2},{3,3},{3,4},{3,5}
        };
        int idx = rand() % 9;
        x = cells[idx][0];
        y = cells[idx][1];
        cout << this->name << " (" << this->symbol
             << ") plays: (" << x << "," << y << ")\n";
    }
};

#endif // PYRAMID_BOARD_H
