#ifndef BOT_H
#define BOT_H

#include "Player.h"
#include "Board.h"
#include "Utils.h"
#include <stack>

class Bot : public Player {
private:
    int dx[8] = { 0, 0, 1, -1, 1, -1, -1, 1 };
    int dy[8] = { -1, 1, -1, -1, 0, 0, 1, 1 };
    int level;
    pair<int, int> easyMove();
    pair<int, int> normalMove();
    pair<int, int> hardMove();

    int calculateValue(char board[10][10], int x, int y);

public:
    Bot(const std::string& name, char mark, int level);
    pair<int, int> makeMove() override;
};

#endif // BOT_H