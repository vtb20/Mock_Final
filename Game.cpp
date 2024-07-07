#include "Game.h"

Game::Game(const Player& player1, const Player& player2)
    : p1(new Player(player1)), p2(new Player(player2)), turn(0) {}

void Game::playWithOtherPlayer() {
    bool gameOver = false;
    while (!gameOver) {
        board.display();
        Player* currentPlayer = (turn % 2 == 0) ? p1 : p2;
        Player* opponent = (currentPlayer == p1) ? p2 : p1;

        cout << currentPlayer->getName() << " turn (" << currentPlayer->getMark() << "): ";

         pair<int, int> move = currentPlayer->makeMove();
        while (!board.placeMark(move.first, move.second, currentPlayer->getMark())) {
            cout << "Invalid move. Try again: ";
            move = currentPlayer->makeMove();
        }

        if (board.checkWin(currentPlayer->getMark())) {
            board.display();
            cout << currentPlayer->getName() << " wins!\n";
            gameOver = true;
            currentPlayer->addWin(1);
            opponent->addLoss(1);
           
        }
        else if (board.isFull()) {
            board.display();
            cout << "The game is a draw.\n";
            gameOver = true;
            currentPlayer->addDraw(1);
            opponent->addDraw(1);
           
        }

        turn++;
    }
}

