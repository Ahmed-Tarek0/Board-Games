# 🎮 Board Games Collection — C++ OOP

A collection of three board games built with **C++17** using an **Object-Oriented** design.  
All games share a common framework defined in `BoardGame_Classes.h`.

---

## 📁 Project Structure

```
BoardGames/
├── BoardGame_Classes.h          ← Shared base framework (Board, Player, RandomPlayer, GameManager)
│
├── Game1_XO/
│   ├── XO_Board.h               ← X_O_Board, X_O_Player, X_O_Random_Player
│   └── main.cpp
│
├── Game2_Pyramid/
│   ├── Pyramid_Board.h          ← Pyramidic_X_O_Board, Pyramid_Human_Player, Pyramid_Random_Player
│   └── main.cpp
│
└── Game3_WordTicTacToe/
    ├── WordTicTacToe.h          ← WordTicTacToe board declaration
    ├── WordTicTacToe.cpp        ← Board implementation
    ├── Word_Players.h           ← Word_Human_Player, Word_Random_Player
    ├── main.cpp
    └── dic.txt                  ← Dictionary of valid 3-letter words
```

---

## 🎯 Games

### 1. Classic X-O (3×3)

Standard Tic-Tac-Toe on a 3×3 grid.  
Players alternate placing **X** or **O**. First to get 3 in a row wins.

**Compile & Run:**

```bash
cd Game1_XO
g++ -std=c++17 main.cpp -o xo_game
./xo_game
```

**Player types:** Human · Random Computer

---

### 2. Pyramidic X-O

A Tic-Tac-Toe variant played on a **pyramid-shaped board**:

```
        .          ← Row 1 (1 cell)
      . . .        ← Row 2 (3 cells)
    . . . . .      ← Row 3 (5 cells)
```

First player to get **3 in a row** (horizontal, vertical, or diagonal) wins.  
Input uses **1-based (row, col)** coordinates.

**Compile & Run:**

```bash
cd Game2_Pyramid
g++ -std=c++17 main.cpp -o pyramid_game
./pyramid_game
```

**Player types:** Human · Random Computer

---

### 3. Word Tic-Tac-Toe

A 3×3 board where each cell holds a **letter (A–Z)**.  
A player wins when any row, column, or diagonal forms a valid **3-letter English word** from `Dictionary.h`.  
Both players can place any letter on any empty cell each turn.

**Compile & Run:**

```bash
cd Game3_WordTicTacToe
g++ -std=c++17 main.cpp WordTicTacToe.cpp -o word_game
./word_game
```

**Player types:** Human · Random Computer

---

## 🏗️ Framework Design

```
Board<T>          ← Abstract: update_board, display_board, is_win, is_draw, game_is_over
Player<T>         ← Abstract: getmove, getsymbol, getname, setBoard
RandomPlayer<T>   ← Extends Player<T> for computer players
GameManager<T>    ← Runs the game loop, alternates turns, checks win/draw
```

All three games inherit from this framework, making it easy to add new game types.

---

## ⚙️ Requirements

- C++17 or later
- `g++` compiler

---

CS251 — Object-Oriented Programming Assignment
