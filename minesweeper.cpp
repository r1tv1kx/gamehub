#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 10;
const int NUM_MINES = 10;

vector<vector<char> > board(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));
vector<vector<bool> > revealed(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));

void placeMines() {
    srand(time(0));
    int count = 0;
    while (count < NUM_MINES) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if (board[x][y] != '*') {
            board[x][y] = '*';
            count++;
        }
    }
}

bool isValid(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

int countAdjacentMines(int x, int y) {
    int count = 0;
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < 8; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (isValid(newX, newY) && board[newX][newY] == '*') {
            count++;
        }
    }
    return count;
}

void reveal(int x, int y) {
    if (!isValid(x, y) || revealed[x][y]) {
        return;
    }

    revealed[x][y] = true;

    if (board[x][y] == '*') {
        cout << "Game Over! You hit a mine." << endl;
        exit(0);
    }

    if (countAdjacentMines(x, y) == 0) {
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        for (int i = 0; i < 8; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            reveal(newX, newY);
        }
    }
}

void printBoard() {
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (revealed[i][j]) {
                cout << board[i][j] << " ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int main() {
    placeMines();
    int x, y;

    while (true) {
        printBoard();
        cout << "Enter row and column (e.g., 0 1): ";
        cin >> x >> y;
        if (!isValid(x, y)) {
            cout << "Invalid input. Try again." << endl;
            continue;
        }
        reveal(x, y);
    }

    return 0;
}