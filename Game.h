#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Bot.h"
#include "Replay.h"
using namespace std;

class Game {
private:
    Board board;
    Player* p1;
    Player* p2;
    int turn;
    Replay replay;

public:
    Game(const Player& player1, const Player& player2);
    Game(const Player& player1, const Bot& bot);
    void playWithOtherPlayer();
    void playVsBot();
    static void playReplay();
    static void viewReplay();
    void saveReplay() ;
    void loadReplay(const string& filename);
    static vector<string> getReplayList();
    static pair<string, string> getPlayerNamesFromReplayFile(const string& filename);

};

#endif // GAME_H
