#include "Bot.h"

Bot::Bot(const std::string& name, char mark, int level)
    : Player(name, mark), level(level) {
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
    x = rand() % 10;
    y = rand() % 10;
    while (Board::getInstance()->checkValidMove(x, y, mark) == false) {
        x = rand() % 10;
        y = rand() % 10;
    }
    return make_pair(x, y);
}


pair<int, int> Bot::normalMove() {
    // Simple strategy: try to win, then block, then random move
    //return make_pair(1, 1);
    // Block opponent
    //char opponentMark = (mark == 'X') ? 'O' : 'X';
    char opponentMark = 'X';


    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            int win = 0;
            if (Board::getInstance()->checkValidMove(i, j, opponentMark)) {
                Board::getInstance()->placeMark(i, j, opponentMark);
                if (Board::getInstance()->checkWin(opponentMark)) {
                    Board::getInstance()->placeMark(i, j, ' ');
                    return make_pair(i, j);
                }
                else if (Board::getInstance()->checkPotentialWin(opponentMark)) {
                    Board::getInstance()->placeMark(i, j, ' ');
                    return make_pair(i, j);
                }
                else {
                    Board::getInstance()->placeMark(i, j, ' '); // Reset the mark
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

    char opponentMark = 'X';

    //for (int i = 0; i < 10; ++i) {
    //    for (int j = 0; j < 10; ++j) {
    //        int win = 0;
    //        if (Board::getInstance()->checkValidMove(i, j, opponentMark)) {
    //            Board::getInstance()->placeMark(i, j, opponentMark);
    //            if (Board::getInstance()->checkPotentialWin(opponentMark)) {
    //                Board::getInstance()->placeMark(i, j, ' ');
    //                return make_pair(i, j);
    //            }
    //            else if (Board::getInstance()->checkWin(opponentMark)) {
    //                Board::getInstance()->placeMark(i, j, ' ');
    //                return make_pair(i, j);
    //            }
    //            else {
    //                Board::getInstance()->placeMark(i, j, ' '); // Reset the mark
    //            }
    //        }

    //    }
    //}

    //calculate for best move
    vector<pair<int, int>> pointToCheck;
    for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardHeight; j++) {
            for (int k = 0; k < 8; k++) {
                if (Board::getInstance()->grid[i + dx[k]][j + dy[k]] == ' ' && isIn(pointToCheck, make_pair(i, j))) {
                    pointToCheck.push_back(make_pair(i, j));
                }
            }
        }
    }

    for (int i = 0; i < pointToCheck.size(); i++) {
        if (calculateValue(Board::getInstance()->grid, pointToCheck[i].first, pointToCheck[i].second) > currentValue) {
            currentValue = calculateValue(Board::getInstance()->grid, pointToCheck[i].first, pointToCheck[i].second);
            x = pointToCheck[i].first;
            y = pointToCheck[i].second;
        }
    }

    if (pointToCheck.size() == 0) {
        return normalMove();
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