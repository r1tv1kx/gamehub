#include <iostream>
#include <vector>

void initializeBoard(std::vector<std::vector<char> >& board) {
    for (int i = 0; i < 3; i++) {
        std::vector<char> row(3, ' ');
        board.push_back(row);
    }
}

void displayBoard(const std::vector<std::vector<char> >& board) {
    std::cout << "  1 2 3" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j];
            if (j < 2) {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
        if (i < 2) {
            std::cout << "  -+-+-" << std::endl;
        }
    }
    std::cout << std::endl;
}

bool checkWin(const std::vector<std::vector<char> >& board, char player) {

    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true; // Check rows
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true; // Check columns
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true; 
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true; 
    }
    return false;
}

bool checkDraw(const std::vector<std::vector<char> >& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false; 
            }
        }
    }
    return true; 
}

bool makeMove(std::vector<std::vector<char> >& board, int row, int col, char player) {
    if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
        return false; 
    }
    board[row - 1][col - 1] = player;
    return true; 
}

int main() {
    std::vector<std::vector<char> > board;
    initializeBoard(board);

    char currentPlayer = 'X';
    bool gameWon = false;

    while (true) {
        displayBoard(board);

        int row, col;
        std::cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        std::cin >> row >> col;

        if (makeMove(board, row, col, currentPlayer)) {
            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                gameWon = true;
            } else if (checkDraw(board)) {
                displayBoard(board);
                std::cout << "It's a draw!" << std::endl;
                gameWon = true;
            }

            if (gameWon) {
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }

    return 0;
}
