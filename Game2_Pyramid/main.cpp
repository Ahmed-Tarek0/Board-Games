#include <iostream>
#include <limits>
#include "Pyramid_Board.h"
using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    Pyramidic_X_O_Board* B = new Pyramidic_X_O_Board();
    string name1, name2;

    cout << "================================\n";
    cout << "  Welcome to Pyramidic X-O!  \n";
    cout << "================================\n\n";

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
        ? (Player<char>*) new Pyramid_Human_Player(name1, 'X')
        : (Player<char>*) new Pyramid_Random_Player('X');

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
        ? (Player<char>*) new Pyramid_Human_Player(name2, 'O')
        : (Player<char>*) new Pyramid_Random_Player('O');

    // --- Run ---
    GameManager<char> game(B, players);
    game.run();

    // --- Cleanup ---
    delete B;
    delete players[0];
    delete players[1];

    return 0;
}
