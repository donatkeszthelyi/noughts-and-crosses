#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include "noughts_and_crosses.h"

using namespace std;

void show_menu(char &game_type);

int main() {
    using namespace std::this_thread;
    using namespace std::chrono;

    random_device rd;
    mt19937 gen(rd());

    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int turn;
    char board_full = false;
    char won;
    char player;
    char game_type;
    bool play = true;
    char play_again;
    char difficulty;

    uniform_int_distribution<int> dist(0, 1);
    turn = dist(gen);

    // MAIN MENU
    show_menu(game_type);

    while (play) {
        // MULTIPLAYER LOOP
        if (game_type == 'm') {
            while (true) {
                cout << "\033[2J\033[1;1H";
                print_board(board);
                board_full = true;
                won = check_win(board);
                if (won) {
                    cout << "\033[2J\033[1;1H";
                    print_board(board);
                    cout << "PLAYER [" << player << "] WINS!\n\n";
                    cout << "Play again?\nEnter 'y' to play, 'n' to quit, and any other key to return to the menu: ";
                    cin >> play_again;
                    if (play_again == 'y') {
                        for (int r = 0; r < 3; r++) {
                            for (int c = 0; c < 3; c++) {
                                board[r][c] = ' ';
                            }
                        }
                        continue;
                    } else if (play_again == 'n') {
                        play = false;
                        break;
                    } else {
                        for (int r = 0; r < 3; r++) {
                            for (int c = 0; c < 3; c++) {
                                board[r][c] = ' ';
                            }
                        }
                        play = false;
                        show_menu(game_type);
                    }
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
                    cout << "Play again?\nEnter 'y' to play, 'n' to quit, and any other key to return to the menu: ";
                    cin >> play_again;
                    if (play_again == 'y') {
                        for (int r = 0; r < 3; r++) {
                            for (int c = 0; c < 3; c++) {
                                board[r][c] = ' ';
                            }
                        }
                        continue;
                    } else if (play_again == 'n') {
                        play = false;
                        break;
                    } else {
                        for (int r = 0; r < 3; r++) {
                            for (int c = 0; c < 3; c++) {
                                board[r][c] = ' ';
                            }
                        }
                        play = false;
                        show_menu(game_type);
                    }
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

        // SINGLEPLAYER LOOP
        if (game_type == 's') {
             while (true) {
                cout << "Choose a difficulty! easy (e), hard (h) or random move (r): ";
                cin >> difficulty;
                if (difficulty == 'e' || difficulty == 'h' || difficulty == 'r') {
                    break;
                } else {
                    cin.clear();
                    cout << "Unkown difficulty type. Please enter 'e', 'h' or 'r': ";
                    cin >> difficulty;
                }
            }
            while (true) {
                cout << "\033[2J\033[1;1H";
                print_board(board);
                board_full = true;
                won = check_win(board);
                if (won) {
                    cout << "\033[2J\033[1;1H";
                    print_board(board);
                    cout << "PLAYER [" << player << "] WINS!\n\n";
                    cout << "Play again?\nEnter 'y' to play, 'n' to quit, and any other key to return to the menu: ";
                    cin >> play_again;
                    if (play_again == 'y') {
                        for (int r = 0; r < 3; r++) {
                            for (int c = 0; c < 3; c++) {
                                board[r][c] = ' ';
                            }
                        }
                        continue;
                    } else if (play_again == 'n') {
                        play = false;
                        break;
                    } else {
                        for (int r = 0; r < 3; r++) {
                            for (int c = 0; c < 3; c++) {
                                board[r][c] = ' ';
                            }
                        }
                        play = false;
                        show_menu(game_type);
                    }
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
                    cout << "Play again?\nEnter 'y' to play, 'n' to quit, and any other key to return to the menu: ";
                    cin >> play_again;
                    if (play_again == 'y') {
                        for (int r = 0; r < 3; r++) {
                            for (int c = 0; c < 3; c++) {
                                board[r][c] = ' ';
                            }
                        }
                        continue;
                    } else if (play_again == 'n') {
                        play = false;
                        break;
                    } else {
                        for (int r = 0; r < 3; r++) {
                            for (int c = 0; c < 3; c++) {
                                board[r][c] = ' ';
                            }
                        }
                        play = false;
                        show_menu(game_type);
                    }
                    break;
                }
                if (turn % 2 == 0) {
                    player = 'O';
                    sleep_for(nanoseconds(10));
                    sleep_until(system_clock::now() + seconds(0));
                    Position position = computer_move(board, player, difficulty);
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
    }
    return 0;
}

void show_menu(char &game_type) {
    cout << "\033[2J\033[1;1H";
    cout << "\n-------- NOUGTHS AND CROSSES --------\n\n";
    while (true) {
        cout << "Choose a game type!\n Single-player ('s') or multiplayer ('m'): ";
        cin >> game_type;
        if (game_type == 's' || game_type == 'm') {
            break;
        } else {
            cin.clear();
            cout << "Unkown game type. Please enter 's' or 'm': ";
            cin >> game_type;
        }
    }
}
