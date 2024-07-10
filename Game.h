#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Bot.h"
#include "Replay.h"
#include "PlayerManager.h"

using namespace std;

class Game {
private:
    Board board;
    Player* p1;
    Player* p2;
    int turn;
    Replay replay;

public:
    Game();
    Game(const Player& player1, const Player& player2);
    Game(const Player& player1, const Bot& bot);
    void playWithOtherPlayer();
    void playVsBot();
    void PlayAgain();
    void playReplay();
    void viewReplay();
    void loadReplay(const string& filename);
};

#endif // GAME_H
