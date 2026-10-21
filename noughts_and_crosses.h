#ifndef NOUGHTS_AND_CROSSES_H
#define NOUGHTS_AND_CROSSES_H

/* Struct for the position */
struct Position {
    char row;
    char col;
};

/* Function to display the state of the board.
 *  
 * @param board The 2D board array to be displayed.
 */
void print_board(char board[3][3]);

/* Function to insert an input in a cell on the board.
 *  
 * @param board The 2D board array to insert into.
 * @param position The position to insert the input in the form of "A2",
 * where the first character should be A-C for the row, the second
 * 1-3 for the column.
 * @param input The chacarter to input to the position. 'X' or 'O'.
 */
void make_move(char board[3][3], char position[2], char input);

/* Function to whether a move is valid or not.
 *  
 * @param board The 2D board array to insert into.
 * @param position The position to insert the input in the form of "A2",
 * where the first character should be A-C for the row, the second
 * 1-3 for the column.
 * @return true if the move is valid, false otherwise.
 */
bool is_valid_move(char board[3][3], char position[2]);

/* Function to get user input and make a move with it.
 *  
 * @param board The 2D board array.
 * @param player Either 'O' or 'X' depending on the current turn.
 */
void player_move(char board[3][3], char player);

/* Function to make the computer move.
 *  
 * @param board The 2D board array.
 * @param player Either 'O' or 'X' depending on the current turn.
 * @param difficulty Sets the type of the move. ('r' - random, 
 * 'e' - easy (bad move), 'h' - hard (good move))
 * @return The the Position, the computer chose.
 */
Position computer_move(char board[3][3], char player, char difficulty);

/* Function to check whether a player (or the computer) won the game.
 *  
 * @param board The 2D board array.
 * @return '\0' if the game is not won, 'X' if player X won, 'O' if player O won.
 */
char check_win(char board[3][3]);

#endif
