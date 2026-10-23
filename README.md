# Noughts and Crosses

A command-line implementation of Noughts and Crosses (Tic-Tac-Toe) written in C++.

## Features

- Single-player mode against a computer opponent.
- Two-player local multiplayer mode.
- Difficulty selection for single-player mode.
- Input validation for player moves.
- Win and draw detection.
- Board display using a 3 × 3 grid.

## Requirements

- A C++ compiler supporting C++11 or later.
- GNU Make.

## Build

Clone the repository and navigate to the project directory.

Build the executable using:

```bash
make
```

This compiles the source files and produces an executable named `main`.

## Run

Start the game with:

```bash
./main
```

Choose a game mode when prompted:

- `s` — Single-player mode.
- `m` — Multiplayer mode.

Choose a difficulty when prompted (in sigle-player mode):

- `e` - Easy
- `h` - Hard
- `r` - Random move (the computer chooses a randomly)

## How to Play

The game board consists of three rows (`A`–`C`) and three columns (`1`–`3`).

Enter a position using a row letter followed by a column number. For example:

- `A1` — Top-left cell.
- `B2` — Centre cell.
- `C3` — Bottom-right cell.

Player `X` takes the first turn. In multiplayer mode, players alternate between `X` and `O`. In single-player mode, the computer plays as `O`.

A player wins by placing three marks in a horizontal, vertical, or diagonal line. If the board is filled without a winner, the game ends in a draw.

Invalid or occupied positions are rejected.

## Project Structure

```text
.
├── main.cpp
├── noughts_and_crosses.cpp
├── noughts_and_crosses.h
└── Makefile
```

- `main.cpp` — Handles game initialization, mode selection, and the main game loop.
- `noughts_and_crosses.cpp` — Implements board rendering, move validation, computer moves, and win detection.
- `noughts_and_crosses.h` — Declares the `Position` structure and game functions.
- `Makefile` — Defines the build rules.

## Current Limitations

- The game does not currently provide persistent scores or match history.

## License

No license has been specified for this project.
