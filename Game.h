// Game.h
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Board.h"
#include "Player.h"
using namespace std;

class Game {
private:
    Board board;
    Player* p1;
    Player* p2;
    int turn;

public:
    Game();
    Game(const Player& player1, const Player& player2);
    void playWithOtherPlayer();
    void showGuide() const;
    void showInfoPlayer(const string& name) const;
    //void processMove(int x, int y);
    //bool checkWin();
    //void showBoard();
    //void loadReplay(const std::string& filename);
    //void saveReplay(const std::string& filename);
};

#endif // GAME_H
