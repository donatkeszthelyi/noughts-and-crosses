#include <iostream>
#include <cctype>
#include <cstdlib>
#include <random>
#include "noughts_and_crosses.h"

using namespace std;

void print_board(char board[3][3]) {
    cout << endl;
    cout << "-------- NOUGTHS AND CROSSES --------\n\n";
    cout << "     1   2   3  " << endl;
    cout << "   ┌───┬───┬───┐" << endl;
    for (int row = 0; row < 2; row++) {
        cout << " " << static_cast<char>('A' + row) << " │";
        for (int col = 0; col < 3; col++) {
            cout << " " << board[row][col] << " │";
        }
        cout << "\n   ├───┼───┼───┤\n";
    }
    cout << " C │";
    for (int col = 0; col < 3; col++) {
        cout << " " << board[2][col] << " │";
    }
    cout << "\n   └───┴───┴───┘\n\n";
    return;
}

void make_move(char board[3][3], char position[2], char input) {
    int position_r = toupper(static_cast<unsigned char>(position[0])) - 'A'; 
    int position_c = toupper(static_cast<unsigned char>(position[1])) - '1'; 
    board[position_r][position_c] = input;
    return;
} 

bool is_valid_move(char board[3][3], char position[2]) {
    int position_r = toupper(static_cast<unsigned char>(position[0])) - 'A'; 
    int position_c = toupper(static_cast<unsigned char>(position[1])) - '1'; 
    if (position_r > 2 || position_r < 0) { return false; }
    if (position_c > 2 || position_c < 0) { return false; }
    if (board[position_r][position_c] != ' ') { return false; }
    return true;
}

void player_move(char board[3][3], char player) {
    char input[3];
    char position[2];
    cout << '[' << player << "] Enter a move: ";
    cin >> input;
    while (true) {
        position[0] = input[0];
        position[1] = input[1];

        if (input[2] == '\0' && is_valid_move(board, position)) {
            break;
        } 
        
        cin.clear();

        cout << '[' << player << "] Invalid move! Enter a valid move: ";
        cin >> input;
    }

    make_move(board, position, player);
}

Position computer_move(char board[3][3], char player, char difficulty) {
    random_device rd;
    mt19937 gen(rd());

    Position invalid = {'\0', '\0'};
    if (difficulty == 'r') {
        Position empty_positions[9];
        int i = 0;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (board[row][col] == ' ') {
                    empty_positions[i++] = {
                        static_cast<char>(row + 'A'),
                        static_cast<char>(col + '1')
                    };
                }
            }
        }
        if (i == 0) {
            return invalid;
        }
        uniform_int_distribution<int> dist(0, i - 1);
        Position move = empty_positions[dist(gen)];

        char position[2] = {move.row, move.col};
        make_move(board, position, player);

        return move;
    }
    return invalid;
}

char check_win(char board[3][3]) {
    for (int r = 0; r < 3; r++) {
        if (board[r][0] != ' ' && board[r][0] == board[r][1] && board[r][0] == board[r][2]) {
            return board[r][0];
        }
    }
    for (int c = 0; c < 3; c++) {
        if (board[0][c] != ' ' && board[0][c] == board[1][c] && board[0][c] == board[2][c]) {
            return board[0][c];
        }
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return board[0][2];
    }
    return '\0'; 
}
