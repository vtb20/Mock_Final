#include "Board.h"

Board::Board() {
    reset();// khởi tạo một bảng không có ký tự 
}

void Board::reset() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            grid[i][j] = ' ';
        }
    }
}

void Board::display() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "=> Player 1 = X, Player 2 = O:\n";
    cout << "  ";
    for (int i = 0; i < 10; ++i) {
        cout << i << " ";
    }
    cout << "\n";

    for (int i = 0; i < 10; ++i) {
        cout << i << " ";
        for (int j = 0; j < 10; ++j) {
           cout << grid[i][j];
            if (j < 9) cout << "|";
        }
        cout << "\n";
        if (i < 9) {
            cout << "  ";
            for (int j = 0; j < 10; ++j) {
                cout << "-";
                if (j < 9) cout << "+";
            }
            cout << "\n";
        }
    }
}

bool Board::isFull() const {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (grid[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool Board::placeMark(int x, int y, char mark) {
    if (x >= 0 && x < 10 && y >= 0 && y < 10 && grid[x][y] == ' ') {
        grid[x][y] = mark;
        return true;
    }
    return false;
}

bool Board::checkWin(char mark) const {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (grid[i][j] == mark) {
                if (j <= 6 && grid[i][j + 1] == mark && grid[i][j + 2] == mark && grid[i][j + 3] == mark) {
                    return true; // check ngang 
                }
                if (i <= 6 && grid[i + 1][j] == mark && grid[i + 2][j] == mark && grid[i + 3][j] == mark) {
                    return true; // check dọc
                }
                if (i <= 6 && j <= 6 && grid[i + 1][j + 1] == mark && grid[i + 2][j + 2] == mark && grid[i + 3][j + 3] == mark) {
                    return true; //check chéo
                }
                if (i >= 3 && j <= 6 && grid[i - 1][j + 1] == mark && grid[i - 2][j + 2] == mark && grid[i - 3][j + 3] == mark) {
                    return true;// 
                }
            }
        }
    }
    return false;
}

