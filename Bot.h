#ifndef BOT_H
#define BOT_H

#include "Player.h"
#include "Board.h"

class Bot : public Player {
private:
    int level;
    pair<int, int> easyMove();
    pair<int, int> normalMove();
    pair<int, int> hardMove();
    Board& board;
    bool checkWinNextMove(char mark, int& x, int& y);
    bool checkBlockOpponent(char mark, int& x, int& y);

public:
    Bot(const std::string& name, char mark, int level, Board& board);
    pair<int, int> makeMove() override;
};

#endif // BOT_H
