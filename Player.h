#ifndef PLAYER_H
#define PLAYER_H

#include <string>


using namespace std;

class Player {
protected:
    string name;
    char mark;
    int wins;
    int losses;
    int draws;

public:
    Player(const string& name, char mark);
    string getName() const;
    char getMark() const;
    int getWins() const;
    int getLosses() const;
    int getDraws() const;
    void addWin(int num = 1);
    void addLoss(int num = 1);
    void addDraw(int num = 1);
    virtual pair<int, int> makeMove();
};

#endif // PLAYER_H
