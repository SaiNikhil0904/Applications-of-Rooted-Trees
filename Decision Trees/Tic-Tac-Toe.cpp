#include <bits/stdc++.h>
using namespace std;

// The size of the Tic-Tac-Toe board
const int boardSize = 3;

// Function to print the Tic-Tac-Toe board
void printBoard(char board[boardSize][boardSize]) {
    cout << "Tic-Tac-Toe Board:\n";
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            cout << " " << board[i][j] << " ";
            if (j < boardSize - 1)
                cout << "|";
        }
        cout << endl;
        if (i < boardSize - 1)
            cout << "-----------\n";
    }
    cout << endl;
}

// Function to check if the game is over (win or draw)
bool isGameOver(char board[boardSize][boardSize]) {
    for (int i = 0; i < boardSize; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return true;
    }

    for (int j = 0; j < boardSize; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ')
            return true;
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return true;

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return true;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }

    return true;
}

// Evaluation function (heuristic)
int evaluate(char board[boardSize][boardSize]) {
    for (int i = 0; i < boardSize; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == 'X') return 10;
            else if (board[i][0] == 'O') return -10;
        }
    }

    for (int j = 0; j < boardSize; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            if (board[0][j] == 'X') return 10;
            else if (board[0][j] == 'O') return -10;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'X') return 10;
        else if (board[0][0] == 'O') return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'X') return 10;
        else if (board[0][2] == 'O') return -10;
    }

    return 0; // If no one wins
}

// Minimax algorithm with alpha-beta pruning
int minimax(char board[boardSize][boardSize], int depth, bool isMax, int alpha, int beta) {
    if (isGameOver(board)) {
        int score = evaluate(board);
        return score;
    }

    if (isMax) {
        int bestScore = INT_MIN;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    bestScore = max(bestScore, minimax(board, depth + 1, !isMax, alpha, beta));
                    board[i][j] = ' ';
                    alpha = max(alpha, bestScore);
                    if (beta <= alpha)
                        break; // Prune the branch
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    bestScore = min(bestScore, minimax(board, depth + 1, !isMax, alpha, beta));
                    board[i][j] = ' ';
                    beta = min(beta, bestScore);
                    if (beta <= alpha)
                        break; // Prune the branch
                }
            }
        }
        return bestScore;
    }
}

// Find the best move for the player 'X'
pair<int, int> findBestMove(char board[boardSize][boardSize]) {
    int bestScore = INT_MIN;
    pair<int, int> bestMove;
    bestMove.first = -1;
    bestMove.second = -1;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                int moveScore = minimax(board, 0, false, INT_MIN, INT_MAX);
                board[i][j] = ' ';

                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove.first = i;
                    bestMove.second = j;
                }
            }
        }
    }

    return bestMove;
}

int main() {
    char board[boardSize][boardSize] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    cout << "Tic-Tac-Toe Game\n";

    while (!isGameOver(board)) {
        printBoard(board);

        // Player 'X' (Max) makes a move
        pair<int, int> move = findBestMove(board);
        board[move.first][move.second] = 'X';
        cout << "Player 'X' (Max) makes a move:\n";
        
        if (isGameOver(board)) {
            printBoard(board);
            break;
        }

        printBoard(board);

        // Player 'O' (Min) makes a move
        int row, col;
        cout << "Enter the row and column for Player 'O' (Min): ";
        cin >> row >> col;
        
        if (row >= 0 && row < boardSize && col >= 0 && col < boardSize && board[row][col] == ' ') {
            board[row][col] = 'O';
            cout << "Player 'O' (Min) makes a move:\n";
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }

    printBoard(board);

    if (evaluate(board) == 10)
        cout << "Player 'X' (Max) wins!\n";
    else if (evaluate(board) == -10)
        cout << "Player 'O' (Min) wins!\n";
    else
        cout << "It's a draw!\n";

    return 0;
}
