#include "Bot.h"
#include <cstdlib>
#include <ctime>

Bot::Bot(const std::string& name, char mark, int level, Board& board)
    : Player(name, mark), level(level), board(board) {
    srand(static_cast<unsigned>(time(0)));  // Seed for random moves
}


int Bot::calculateValue(char board[10][10], int x, int y) {
    int value = 0;
    int oposite;
    int boardSize = 10;
    stack<pair<int, int>> position;
    for (int i = 0; i < 8; i++) {
        if (i % 2 == 1) oposite = i - 1;
        else oposite = i + 1;
        if (board[x + dx[oposite]][y + dy[oposite]] == ' ') {
            value += 1;
        }
        int newx = x + dx[i];
        int newy = y + dy[i];
        if (board[newx][newy] == mark && (newx >= 0 && newx < boardSize) && (newy >= 0 && newy < boardSize)) {
            position.push(make_pair(newx, newy));
            value += 1;
            while (!position.empty()) {
                int nx = position.top().first + dx[i];
                int ny = position.top().second + dy[i];
                if (board[nx][ny] == mark && (nx >= 0 && nx < boardSize) && (ny >= 0 && ny < boardSize)) {
                    position.pop();
                    position.push(make_pair(nx, ny));
                    value += 1;
                }
                else {
                    position.pop();
                }
            }
        }
    }
    return value;
}


pair<int, int> Bot::easyMove() {
    int x, y;
    do {
        x = rand() % 10;
        y = rand() % 10;
    } while (board.placeMark(x, y, mark) == false); // Ensure the move is valid
    return make_pair(x, y);
}


pair<int, int> Bot::normalMove() {
    // Simple strategy: try to win, then block, then random move
    // Try to win
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (board.placeMark(i, j, mark)) {
                if (board.checkWin(mark)) {
                    return make_pair(i, j);
                }
                else {
                    board.placeMark(i, j, ' '); // Reset the mark
                }
            }
        }
    }

    // Block opponent
    char opponentMark = (mark == 'X') ? 'O' : 'X';
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (board.placeMark(i, j, opponentMark)) {
                if (board.checkWin(opponentMark)) {
                    board.placeMark(i, j, mark);
                    return make_pair(i, j);
                }
                else {
                    board.placeMark(i, j, ' '); // Reset the mark
                }
            }
        }
    }

    // Random move
    return easyMove();
}

pair<int, int> Bot::hardMove() {
    // Implement an advanced strategy
    // For now, let's use the same as easyMove for simplicity
    int boardWidth = 10;
    int boardHeight = 10;
    /*int dx[8] = { 0, 0, 1, -1, 1, -1, 1, -1 };
    int dy[8] = { -1, 1, -1, -1, 0, 0, 1, 1 };*/
    int currentValue = 0;
    int x, y;

    // Block opponent
    char opponentMark = (mark == 'X') ? 'O' : 'X';
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (board.placeMark(i, j, opponentMark)) {
                if (board.checkWin(opponentMark)) {
                    board.placeMark(i, j, mark);
                    return make_pair(i, j);
                }
                else {
                    board.placeMark(i, j, ' '); // Reset the mark
                }
            }
        }
    }

    //calculate for best move
    vector<pair<int, int>> pointToCheck;
    for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardHeight; j++) {
            for (int k = 0; k < 8; k++) {
                if (board.grid[i + dx[k]][j + dy[k]] == ' ') {
                    pointToCheck.push_back(make_pair(i, j));
                }
            }
        }
    }

    for (int i = 0; i < pointToCheck.size(); i++) {
        if (calculateValue(board.grid, pointToCheck[i].first, pointToCheck[i].second) > currentValue) {
            currentValue = calculateValue(board.grid, pointToCheck[i].first, pointToCheck[i].second);
            x = pointToCheck[i].first;
            y = pointToCheck[i].second;
        }
    }

    return make_pair(x, y);
}

pair<int, int> Bot::makeMove() {
    switch (level) {
    case 1: return easyMove();
    case 2: return normalMove();
    case 3: return hardMove();
    default: return easyMove();
    }
}