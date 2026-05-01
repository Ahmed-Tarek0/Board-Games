#include <iostream>
#include <limits>
#include "XO_Board.h"
using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    X_O_Board<char>* B = new X_O_Board<char>();
    string name1, name2;

    cout << "=============================\n";
    cout << "   Welcome to X-O Game!  \n";
    cout << "=============================\n\n";

    // --- Player 1 setup ---
    cout << "Enter Player X name: ";
    cin >> name1;

    cout << "Choose Player X type:\n";
    cout << "  1. Human\n";
    cout << "  2. Random Computer\n";
    cout << "Choice: ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid input. Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    players[0] = (choice == 1)
        ? (Player<char>*) new X_O_Player<char>(name1, 'X')
        : (Player<char>*) new X_O_Random_Player<char>('X');

    // --- Player 2 setup ---
    cout << "\nEnter Player O name: ";
    cin >> name2;

    cout << "Choose Player O type:\n";
    cout << "  1. Human\n";
    cout << "  2. Random Computer\n";
    cout << "Choice: ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid input. Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    players[1] = (choice == 1)
        ? (Player<char>*) new X_O_Player<char>(name2, 'O')
        : (Player<char>*) new X_O_Random_Player<char>('O');

    // --- Run ---
    GameManager<char> game(B, players);
    game.run();

    // --- Cleanup ---
    delete B;
    delete players[0];
    delete players[1];

    return 0;
}
