#include <iostream>
using namespace std;

bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);

int numMoves = 0;                     //  Keep track of moves in the game
int const TOTAL_POSSIBLE_MOVES = 9;   //  Total possible board moves
int const MAX_ROWS = 3;               //  Max rows in the board
int const MAX_COLUMNS = 3;            //  Max columns in the board
int const MIN_MOVES_FOR_WIN = 5;      /** Minimum # of moves required for
                                       *  the game to have a winner in a
                                       *  3x3 board.
                                       */

int main() {
    //
    //      PLEASE DO NOT CHANGE main()
    //
    char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    displayBoard(board);
    
    while(true) {
        // The first player makes a move
        makeAMove(board, 'X');
        displayBoard(board);
        if(isWon('X', board)) {
            cout << "X player won" << endl;
            exit(0);
        }
        else if(isDraw(board)) {
            cout << "No winner" << endl;
            exit(0);
        }
        
        // The second player makes a move
        makeAMove(board, '0');
        displayBoard(board);
        
        if(isWon('0', board)) {
            cout << "0 player won" << endl;
            exit(0);
        }
        else if (isDraw(board)) {
            cout << "No winner" << endl;
            exit(0);
        }
    }
    
    return 0;
}

/**
 * Displays the most current board state of the game.
 */
void displayBoard(char board[][3]) {
    cout << "\n";
    for(int row = 0 ; row < MAX_ROWS; row++) {
        cout << "-------------" << endl;
        for(int col = 0; col < MAX_COLUMNS; col++) {
            cout << "| " << board[row][col] << " ";
        }
        cout << "|" << endl;
    }
    cout << "-------------" << endl;
}

/**
 * Ask the player for a position on the borad to make an entry.
 * Register a player's move by updating the arrays of the board with the
 * symbol/character of the player making the move.
 */

void makeAMove(char board[][3], char c) {
    int row = 0;
    int col = 0;
    bool validInput = false;
    
    while(!validInput) {
        cout << "Enter a row (0, 1, 2) for player " << c << "    : " ;
        cin >> row;
        cout << "Enter a column (0, 1, 2) for player " << c << " : " ;  ;
        cin >> col;
        
        // Check to see if cell is available and row and column indecies are within bounds.
        if(board[row][col] == ' ' && (row >= 0 && row <= 2) && (col >= 0 && col <= 2)) {
            board[row][col] = c;
            numMoves++;
            validInput = true;
        } else if (row < 0 || row > 2 || col < 0 || col > 2)
            cout << "Invalid row/column input" << endl;
        else
            cout << "This cell is already occupied. Try a different cell" << endl;
            
    }
}

/**
 * Check to see if there is a winner by looking at the entries on the board.
 * There are 8 possible winning combinations: 3 in which a row is equivalent.
 *                                            3 in which a column is equivalent.
 *                                            2 in which a diagonal is equivalent.
 */

bool isWon(char c, char board[][3]) {
    
    // Only check after 5 moves, which are the minimum moves required for the game to have a winner.
    if (numMoves >= MIN_MOVES_FOR_WIN) {
        // Check 1: Row one
        if (board[0][0] == c && board[0][1] == c && board[0][2] == c)
            return true;
        // Check 2: Row two
        else if (board[1][0] == c && board[1][1] == c && board[1][2] == c)
            return true;
        // Check 3: Row three
        else if (board[2][0] == c && board[2][1] == c && board[2][2] == c)
            return true;
        // Check 4: Column one
        else if (board[0][0] == c && board[1][0] == c && board[2][0] == c)
            return true;
        // Check 5: Column two
        else if (board[0][1] == c && board[1][1] == c && board[2][1] == c)
            return true;
        // Check 6: Column three
        else if (board[0][2] == c && board[1][2] == c && board[2][2] == c)
            return true;
        // Check 7: Main diagonal
        else if (board[0][0] == c && board[1][1] == c && board[2][2] == c)
            return true;
        // Check 8: Other diagonal
        else if (board[2][0] == c && board[1][1] == c && board[0][2] == c)
            return true;
        }
    
    return false;
}

/**
 * Check to see if the game is a draw by checking the maximum number of moves has been reached
 * in the game. If so, and there is no winner, then the game is a draw.
 */

bool isDraw(char board[][3]) {
    // Check to see if max number of possible moves has been reached
    if (numMoves == TOTAL_POSSIBLE_MOVES)
        return true;
    
    return false;
}
