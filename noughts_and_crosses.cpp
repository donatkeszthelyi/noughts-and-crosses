#include <iostream>
#include <cctype>
#include <cstdlib>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
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
    string input;
    char position[2];

    cout << '[' << player << "] Enter a move: ";
    while (true) {
        if (!(cin >> input)) {
            return;
        }
        if (input.size() == 2) {
            position[0] = input[0];
            position[1] = input[1];
            if (is_valid_move(board, position)) {
                break;
            }
        }
        cout << '[' << player
             << "] Invalid move! Enter a valid move: ";
    }
    make_move(board, position, player);
}

Position computer_move(char board[3][3], char player, char difficulty) {
    Position invalid = {'\0', '\0'};
    if (difficulty == 'r') {
        random_device rd;
        mt19937 gen(rd());
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
    } else if (difficulty == 'h' || difficulty == 'e') {
        char original_board[3][3];
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                original_board[row][col] = board[row][col];
            }
        }
        if (difficulty == 'h') {
            minimax(board, player, 0);
        } else if (difficulty == 'e') {
            minimax(board, player, 0, true);
        }
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (board[row][col] != original_board[row][col]) {
                    return {
                        static_cast<char>(row + 'A'),
                        static_cast<char>(col + '1')
                    };
                }
            }
        }
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

int score(char board[3][3], int depth) {
    if (check_win(board) == 'O') {
        return 10 - depth;
    } else if (check_win(board) == 'X') {
        return depth - 10;
    } else {
        return 0;
    }
}

int minimax(char board[3][3], char turn, int depth, bool easy) {
    if (check_win(board)) {
        return score(board, depth);
    }
    depth++;
    vector<int> scores;
    vector<Position> moves;
    vector<Position> empty_positions;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] == ' ') {
                empty_positions.push_back({
                    static_cast<char>(row + 'A'),
                    static_cast<char>(col + '1')
                });
            }
        }
    }
    if (empty_positions.empty()) {
        return 0;
    }
    for (int i = 0; i < static_cast<int>(empty_positions.size()); i++) {
        char possible_board[3][3];
        char next_turn = (turn == 'O') ? 'X' : 'O';
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                possible_board[row][col] = board[row][col];
            }
        }
        char position[2] = {
            empty_positions[i].row,
            empty_positions[i].col
        };
        make_move(possible_board, position, turn);
        scores.push_back(minimax(possible_board, next_turn, depth, easy));
        moves.push_back(empty_positions[i]);
    }
    if (turn == 'O') {
    auto it = easy 
        ? min_element(scores.begin(), scores.end())
        : max_element(scores.begin(), scores.end());

    int index = distance(scores.begin(), it);
    char position[2] = {moves[index].row, moves[index].col};
    make_move(board, position, turn);
    return scores[index];
} else {
    auto it = easy 
        ? max_element(scores.begin(), scores.end())
        : min_element(scores.begin(), scores.end());

    int index = distance(scores.begin(), it);
    char position[2] = {moves[index].row, moves[index].col};
    make_move(board, position, turn);
    return scores[index];
}
}

