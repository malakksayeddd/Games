# MiniBoards - Board Game Collection

A collection of Tic-Tac-Toe variant board games with AI opponents.

## Games Included

- **Classic X-O** - Traditional 3x3 Tic-Tac-Toe
- **Numerical TTT** - Sum numbers to 15 to win
- **SUS Game** - Place S/U to form "SUS" sequences
- **Four-in-a-Row** - Connect Four (6x7 with gravity)
- **Misère TTT** - Inverse rules (3-in-row loses)
- **Infinity TTT** - Limited to 3 marks per player
- **Obstacles TTT** - 6x6 board with random obstacles
- **4x4 TTT** - Movable pieces, align 3 to win
- **5x5 TTT** - Large board, most 3-in-a-rows wins
- **Word TTT** - Place letters to form valid words
- **Pyramid TTT** - Pyramid-shaped board
- **Ultimate TTT** - 9x9 with nested 3x3 sub-boards
- **Memory TTT** - Hidden board variant
- **Diamond TTT** - Diamond-shaped TicTacToe game

## Features

- Human vs Human gameplay
- AI opponents with intelligent strategies (Minimax, greedy algorithms)
- Multiple difficulty levels
- Interactive menu system
- Comprehensive Doxygen documentation

## Building via CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running

```bash
./MiniBoards
```

Select a game from the menu and enjoy!

## Documentation

Full API documentation available via Doxygen:
```bash
doxygen Doxyfile
```
Generated HTML documentation in `docs/` directory.