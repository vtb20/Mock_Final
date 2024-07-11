#include "Board.h"

Board::Board() {
    reset();
}

Board* Board::getInstance(){
    static Board instance;
    return &instance;
}

void Board::reset() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            grid[i][j] = ' ';
        }
    }
}


void Board::display() const {
    system("cls"); 

    cout << "=> Player 1 = X, Player 2 = O:\n";
    cout << "  ";

    for (int i = 0; i < 10; ++i) {
        cout << " " << i;
    }
    cout << endl;
    cout << "  +-+-+-+-+-+-+-+-+-+-+\n";

    for (int i = 0; i < 10; ++i) {
        cout << i << " |";
        for (int j = 0; j < 10; ++j) {
            if (grid[i][j] == ' ') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  
                cout << grid[i][j] << "|";
            }
            else if (grid[i][j] == 'X') {

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  // Màu đỏ
                cout << grid[i][j];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  // Màu đỏ
                cout << "|";
            }
            else {
                // In ra nước đi của người chơi O mặc định
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);  
                cout << grid[i][j];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  
                cout << "|";
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  // Thiết lập màu sắc mặc định trở lại
        cout << "\n  ";
        for (int j = 0; j < 10; ++j) {
            cout << "+-";
        }
        cout << "+\n";
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

bool Board::checkValidMove(int x, int y, char mark) {
    if (x >= 0 && x < 10 && y >= 0 && y < 10 && grid[x][y] == ' ') {
        return true;
    }
    return false;
}

void Board::placeMark(int x, int y, char mark) {
    grid[x][y] = mark;
}

bool Board::checkWin(char mark) const {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j <= 10 - 5; ++j) {
            if (grid[i][j] == mark && grid[i][j + 1] == mark && grid[i][j + 2] == mark &&
                grid[i][j + 3] == mark && grid[i][j + 4] == mark) {
                return true;
            }
        }
    }

    // Kiểm tra cột
    for (int j = 0; j < 10; ++j) {
        for (int i = 0; i <= 10 - 5; ++i) {
            if (grid[i][j] == mark && grid[i + 1][j] == mark && grid[i + 2][j] == mark &&
                grid[i + 3][j] == mark && grid[i + 4][j] == mark) {
                return true;
            }
        }
    }

    // Kiểm tra đường chéo từ trái trên đến phải dưới
    for (int i = 0; i <= 10 - 5; ++i) {
        for (int j = 0; j <= 10 - 5; ++j) {
            if (grid[i][j] == mark && grid[i + 1][j + 1] == mark && grid[i + 2][j + 2] == mark &&
                grid[i + 3][j + 3] == mark && grid[i + 4][j + 4] == mark) {
                return true;
            }
        }
    }

    // Kiểm tra đường chéo từ phải trên đến trái dưới
    for (int i = 0; i <= 10 - 5; ++i) {
        for (int j = 4; j < 10; ++j) {
            if (grid[i][j] == mark && grid[i + 1][j - 1] == mark && grid[i + 2][j - 2] == mark &&
                grid[i + 3][j - 3] == mark && grid[i + 4][j - 4] == mark) {
                return true;
            }
        }
    }

    return false;
}

bool Board::checkPotentialWin(char mark) const {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j <= 10 - 5; ++j) {
            if (grid[i][j] == mark && grid[i][j + 1] == mark && grid[i][j + 2] == mark &&
                grid[i][j + 3] == mark && grid[i][j + 4] == ' ' && grid[i][j - 1] == ' ') {
                return true;
            }
        }
    }

    // Kiểm tra cột
    for (int j = 0; j < 10; ++j) {
        for (int i = 0; i <= 10 - 5; ++i) {
            if (grid[i][j] == mark && grid[i + 1][j] == mark && grid[i + 2][j] == mark &&
                grid[i + 3][j] == mark && grid[i - 1][j] == ' ' && grid[i + 4][j] == ' ') {
                return true;
            }
        }
    }

    // Kiểm tra đường chéo từ trái trên đến phải dưới
    for (int i = 0; i <= 10 - 5; ++i) {
        for (int j = 0; j <= 10 - 5; ++j) {
            if (grid[i][j] == mark && grid[i + 1][j + 1] == mark && grid[i + 2][j + 2] == mark &&
                grid[i + 3][j + 3] == mark && grid[i + 4][j + 4] == ' ' && grid[i - 1][j - 1] == ' ') {
                return true;
            }
        }
    }

    // Kiểm tra đường chéo từ phải trên đến trái dưới
    for (int i = 0; i <= 10 - 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (grid[i][j] == mark && grid[i + 1][j - 1] == mark && grid[i + 2][j - 2] == mark &&
                grid[i + 3][j - 3] == mark && grid[i - 1][j + 1] == ' ' && grid[i + 4][j - 4] == ' ') {
                return true;
            }
        }
    }

    return false;
}