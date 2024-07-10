#ifndef BOARD_H
#define BOARD_H
#include <iostream>
using namespace std;

class Board {
private:
    char grid[10][10];
    Board(); 
public:
    static Board* getInstance();
    void reset();
    void display() const;
    bool isFull() const;
    void placeMark(int x, int y, char mark);
    bool checkValidMove(int x, int y, char mark);
    bool checkWin(char mark) const;
    bool checkPotentialWin(char mark) const;
    friend class Bot;
};

#endif // BOARD_H


