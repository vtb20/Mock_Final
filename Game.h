#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Bot.h"
#include "Replay.h"
#include "PlayerManager.h"
#include "Utils.h"

class Game {
private:
    unique_ptr<Player> p1;
    unique_ptr<Player> p2;
    int turn;
    Replay replay;

public:
    Game();
    ~Game();
    Game(const Player& player1, const Player& player2);
    Game(const Player& player1, const Bot& bot);
    void playWithOtherPlayer();
    void playVsBot();
    void playReplay();
    void viewReplay();
    void loadReplay(const string& filename);
    static void gameOverDisplay();
    static void showReplayMenu();
    static void showMainMenu();
    static void showSubMenuWBot();
    static void displayGuide();
    void handleGameOver();
    void loop();
};

#endif // GAME_H
