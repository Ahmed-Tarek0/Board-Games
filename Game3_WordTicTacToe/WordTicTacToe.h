#ifndef WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_H

#include "../BoardGame_Classes.h"
#include "Dictionary.h"
#include <unordered_set>
#include <cctype>
#include <iostream>
using namespace std;

// ============================================================
//                   WordTicTacToe Board
//
//  3x3 board where each cell holds a letter (A-Z).
//  A player wins when any row, column, or diagonal forms
//  a valid 3-letter English word.
//  Dictionary is embedded at compile time — no external file needed.
// ============================================================
class WordTicTacToe : public Board<char> {
private:
    unordered_set<string> valid_words;

    bool check_rows() {
        for (int i = 0; i < rows; i++) {
            string word = "";
            for (int j = 0; j < columns; j++) word += board[i][j];
            if (valid_words.count(word)) return true;
        }
        return false;
    }

    bool check_columns() {
        for (int j = 0; j < columns; j++) {
            string word = "";
            for (int i = 0; i < rows; i++) word += board[i][j];
            if (valid_words.count(word)) return true;
        }
        return false;
    }

    bool check_diagonals() {
        string d1 = "", d2 = "";
        for (int i = 0; i < rows; i++) {
            d1 += board[i][i];
            d2 += board[i][columns - 1 - i];
        }
        return valid_words.count(d1) || valid_words.count(d2);
    }

public:
    WordTicTacToe() {
        rows = columns = 3;
        n_moves = 0;
        valid_words = getBuiltinDictionary();
        board = new char*[rows];
        for (int i = 0; i < rows; i++) {
            board[i] = new char[columns];
            for (int j = 0; j < columns; j++)
                board[i][j] = '.';
        }
    }

    ~WordTicTacToe() {
        for (int i = 0; i < rows; i++) delete[] board[i];
        delete[] board;
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= rows || y < 0 || y >= columns) return false;
        if (board[x][y] != '.') return false;
        board[x][y] = toupper(symbol);
        n_moves++;
        return true;
    }

    void display_board() override {
        cout << "\n    ";
        for (int j = 0; j < columns; j++) cout << "  " << j << "  ";
        cout << "\n   +";
        for (int j = 0; j < columns; j++) cout << "-----+";
        cout << "\n";
        for (int i = 0; i < rows; i++) {
            cout << " " << i << " |";
            for (int j = 0; j < columns; j++)
                cout << "  " << board[i][j] << "  |";
            cout << "\n   +";
            for (int j = 0; j < columns; j++) cout << "-----+";
            cout << "\n";
        }
        cout << "\n";
    }

    bool is_win()       override { return check_rows() || check_columns() || check_diagonals(); }
    bool is_draw()      override { return (n_moves == rows * columns && !is_win()); }
    bool game_is_over() override { return is_win() || is_draw(); }
};

#endif // WORD_TIC_TAC_TOE_H
