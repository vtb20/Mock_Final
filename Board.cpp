#include "Board.h"

Board::Board() {
    reset();// khởi tạo một bảng không có ký tự 
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
    // In ra các chỉ số cột từ 0 đến 9
    for (int i = 0; i < 10; ++i) {
        cout << " " << i;

    }
    cout << endl;
    cout << "  +-+-+-+-+-+-+-+-+-+-+";
    cout << "\n";
   
    for (int i = 0; i < 10; ++i) {
        cout << i << " " << "|";
        for (int j = 0; j < 10; ++j) {
           cout << grid[i][j] << "|";;
        }
        cout << "\n";
        if (i < 10) {
            cout << "  ";
            for (int j = 0; j < 10; ++j) {
                if (j == 0)
                {
                    cout << "+";
                } 
                cout << "-+";
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