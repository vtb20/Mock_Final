#ifndef BOARD_H
#define BOARD_H
#include <iostream>
using namespace std;

class Board {
private:
    char grid[10][10];

public:
    Board(); 
    void reset();
    void display() const;
    bool isFull() const;
    bool placeMark(int x, int y, char mark);
    bool checkWin(char mark) const;
};

#endif // BOARD_H


