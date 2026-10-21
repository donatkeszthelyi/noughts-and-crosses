#include <iostream>
#include <chrono>
#include <thread>
#include "noughts_and_crosses.h"

using namespace std;

int main() {
    using namespace std::this_thread;
    using namespace std::chrono;

    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int turn = 1;
    char board_full = false;
    char won;
    char player;
    char game_type;

    cout << "\033[2J\033[1;1H";
    cout << "\n-------- NOUGTHS AND CROSSES --------\n\n";
    while (true) {
        cout << "Choose a game type!\n Singleplayer ('s') or multiplayer ('m'): ";
        cin >> game_type;
        if (game_type == 's' || game_type == 'm') {
            break;
        } else {
            cin.clear();
            cout << "Unkown game type. Please enter 's' or 'm': ";
            cin >> game_type;
        }
    }

    if (game_type == 'm') {
        cout << "\033[2J\033[1;1H";
        print_board(board);
        while (true) {
            board_full = true;
            won = check_win(board);
            if (won) {
                cout << "\033[2J\033[1;1H";
                print_board(board);
                cout << "PLAYER [" << player << "] WINS!\n\n";
                break;
            }
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    if (board[r][c] == ' ') {
                        board_full = false;
                    }
                }
            }
            if (board_full) {
                cout << "\033[2J\033[1;1H";
                print_board(board);
                cout << "IT IS A TIE!\n\n";
                break;
            }
            if (turn % 2 == 0) {
                player = 'O';
            } else {
                player = 'X';
            }

            player_move(board, player);
            turn++;
            cout << "\033[2J\033[1;1H";
            print_board(board);
        }
    }

    if (game_type == 's') {
        cout << "\033[2J\033[1;1H";
        print_board(board);
        while (true) {
            board_full = true;
            won = check_win(board);
            if (won) {
                cout << "\033[2J\033[1;1H";
                print_board(board);
                cout << "PLAYER [" << player << "] WINS!\n\n";
                break;
            }
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    if (board[r][c] == ' ') {
                        board_full = false;
                    }
                }
            }
            if (board_full) {
                cout << "\033[2J\033[1;1H";
                print_board(board);
                cout << "IT IS A TIE!\n\n";
                break;
            }
            if (turn % 2 == 0) {
                player = 'O';
                sleep_for(nanoseconds(10));
                sleep_until(system_clock::now() + seconds(0));
                Position position = computer_move(board, player, 'r');
                cout << "\033[2J\033[1;1H";
                print_board(board);
                cout << "[O] The computer's turn: ";
                cout << position.row << position.col;
                cout << endl;
            } else {
                player = 'X';
                player_move(board, player);
                cout << "\033[2J\033[1;1H";
                print_board(board);
            }
            turn++;
        }

    }
    return 0;
}
