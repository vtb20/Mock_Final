#include "Player.h"
#include <iostream>

// Constructor
Player::Player(const string& name, char mark)
    : name(name), mark(mark), wins(0), losses(0), draws(0) {}

string Player::getName() const {
    return name;
}

char Player::getMark() const {
    return mark;
}

int Player::getWins() const {
    return wins;
}

int Player::getLosses() const {
    return losses;
}

int Player::getDraws() const {
    return draws;
}


void Player::addWin(int num) {
    wins += num;
}

void Player::addLoss(int num) {
    losses += num;
}

void Player::addDraw(int num) {
    draws += num;
}

// Make move (for human players, this function should be overridden for bots)
pair<int, int> Player::makeMove() {
    int x, y;
    while (true) {
        cout << "Enter your move (row and column): ";
        if (cin >> x >> y && x >= 0 && x < 10 && y >= 0 && y < 10) {
            break;
        }
        else {
            cout << "Invalid input. Please enter numbers between 0 and 9." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return make_pair(x, y);
}
