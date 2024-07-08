#include "Bot.h"
#include <cstdlib>
#include <ctime>

Bot::Bot(const std::string& name, char mark, int level, Board& board)
    : Player(name, mark), level(level), board(board) {
    srand(static_cast<unsigned>(time(0)));  // Seed for random moves
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
    return easyMove();
}

pair<int, int> Bot::makeMove() {
    switch (level) {
    case 1: return easyMove();
    case 2: return normalMove();
    case 3: return hardMove();
    default: return easyMove();
    }
}
