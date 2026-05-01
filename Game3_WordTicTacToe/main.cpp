#include <iostream>
#include <limits>
#include <string>
#include "WordTicTacToe.h"
#include "Word_Players.h"
using namespace std;

void runWordGame(WordTicTacToe* board, Player<char>* players[2]) {
    board->display_board();

    while (!board->game_is_over()) {
        for (int i = 0; i < 2; i++) {
            int x, y;
            players[i]->getmove(x, y);

            while (!board->update_board(x, y, players[i]->getsymbol())) {
                cout << "Invalid move (cell occupied or out of range)! Try again.\n";
                players[i]->getmove(x, y);
            }

            board->display_board();

            if (board->is_win()) { cout << players[i]->getname() << " wins!\n"; return; }
            if (board->is_draw()) { cout << "It's a draw!\n"; return; }
        }
    }
}

int main() {
    int choice;
    Player<char>* players[2];
    string name1, name2;

    WordTicTacToe* B = new WordTicTacToe();   // no file needed

    cout << "=====================================\n";
    cout << "   Welcome to Word Tic-Tac-Toe!\n";
    cout << "=====================================\n";
    cout << "  Each turn you place a letter (A-Z).\n";
    cout << "  Win by making any row, column, or\n";
    cout << "  diagonal form a valid 3-letter word!\n";
    cout << "=====================================\n\n";

    // --- Player 1 ---
    cout << "Enter Player 1 name: ";
    cin >> name1;
    cout << "Choose Player 1 type:\n  1. Human\n  2. Random Computer\nChoice: ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid input. Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    players[0] = (choice == 1)
        ? (Player<char>*) new Word_Human_Player(name1, 'A')
        : (Player<char>*) new Word_Random_Player('A');

    // --- Player 2 ---
    cout << "\nEnter Player 2 name: ";
    cin >> name2;
    cout << "Choose Player 2 type:\n  1. Human\n  2. Random Computer\nChoice: ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid input. Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    players[1] = (choice == 1)
        ? (Player<char>*) new Word_Human_Player(name2, 'B')
        : (Player<char>*) new Word_Random_Player('B');

    // --- Run ---
    runWordGame(B, players);

    // --- Cleanup ---
    delete B;
    delete players[0];
    delete players[1];

    return 0;
}
