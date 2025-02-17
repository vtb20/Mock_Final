﻿#include "Game.h"
#include "Utils.h"
#include <windows.h>

Game::Game() {
    p1 = nullptr;
    p2 = nullptr;
    turn = 0;
};

Game::~Game(){};

Game::Game(const Player& player1, const Player& player2 )
    : p1(make_unique<Player>(player1)), p2(make_unique<Player>(player2)), turn(0) {
        PlayerManager::getInstance().addOrUpdatePlayer(player1);
        PlayerManager::getInstance().addOrUpdatePlayer(player2); 
}

Game::Game(const Player& player1, const Bot& bot)
    : p1(make_unique<Player>(player1)), p2(make_unique<Bot>(bot)), turn(0) {
}


void Game::playVsBot() {
    Board::getInstance()->reset();
    bool gameOver = false;
    while (!gameOver) {
        Board::getInstance()->display();
        Player* currentPlayer = (turn % 2 == 0) ? p1.get() : p2.get();

        std::cout << currentPlayer->getName() << " turn (" << currentPlayer->getMark() << "): ";

        pair<int, int> move = currentPlayer->makeMove();
        while (!Board::getInstance()->checkValidMove(move.first, move.second, currentPlayer->getMark())) {
            std::cout << "Invalid move. Try again: ";
            move = currentPlayer->makeMove();
        }
        Board::getInstance()->placeMark(move.first, move.second, currentPlayer->getMark());

        replay.saveMove(move);

        if (Board::getInstance()->checkWin(currentPlayer->getMark())) {
            Board::getInstance()->display();
            std::cout << currentPlayer->getName() << " wins!\n";
            gameOver = true;
        }
        else if (Board::getInstance()->isFull()) {
            Board::getInstance()->display();
            std::cout << "The game is a draw.\n";
            gameOver = true;
        }

        turn++;
    }
}


void Game::playWithOtherPlayer() {
    bool gameOver = false;
    Board::getInstance()->reset();
    turn = 0;
    while (!gameOver) {
        Board::getInstance()->display();
        Player* currentPlayer = (turn % 2 == 0) ? p1.get() : p2.get();
        Player* opponent = (currentPlayer == p1.get()) ? p2.get() : p1.get();

        cout << currentPlayer->getName() << " turn (" << currentPlayer->getMark() << "): ";

        pair<int, int> move = currentPlayer->makeMove();

        while (!Board::getInstance()->checkValidMove(move.first, move.second, currentPlayer->getMark())) {
            cout << "Invalid move. Try again: ";
            move = currentPlayer->makeMove();
        }
        Board::getInstance()->placeMark(move.first, move.second, currentPlayer->getMark());

        replay.saveMove(move);

        if (Board::getInstance()->checkWin(currentPlayer->getMark())) {
            Board::getInstance()->display();
            cout << currentPlayer->getName() << " wins!\n";
            gameOver = true;
            currentPlayer->addWin(1);
            opponent->addLoss(1);
            PlayerManager::getInstance().addOrUpdatePlayer(*currentPlayer);
            PlayerManager::getInstance().addOrUpdatePlayer(*opponent);
            cin.ignore();
            cin.get();
        }
        else if (Board::getInstance()->isFull()) {
            Board::getInstance()->display();
            cout << "The game is a draw.\n";
            gameOver = true;
            currentPlayer->addDraw(1);
            opponent->addDraw(1);
            PlayerManager::getInstance().addOrUpdatePlayer(*currentPlayer);
            PlayerManager::getInstance().addOrUpdatePlayer(*opponent);
        }

        turn++;
    }
    replay.saveReplay(p1->getName(), p2->getName());
}


void Game::playReplay() {
    vector<string> replays = replay.getReplayList();
    if (replays.empty()) {
        cout << "No replays available.\n";
        cout << "Press enter to back!";
        cin.ignore();
        cin.get();
        return;
    }
    else {
        cout << "Choose a game to play back (or type 'exit' to go back):\n";
        for (size_t i = 0; i < replays.size(); ++i) {
            cout << i + 1 << ". " << replays[i] << "\n";
        }

        string input;
        int choice = -1;

        while (true) {
            cout << "Enter the number of the replay: ";
            cin >> input;

            if (input == "exit") {
                return; // Quay lại menu replay
            }

            if (isDigit(input)) {
                choice = stoi(input);
                if (choice >= 1 && choice <= replays.size()) {
                    break; // Đầu vào hợp lệ, thoát khỏi vòng lặp
                }
            }

            cout << "Invalid choice, please try again.\n";
        }

        string replayFile = replays[choice - 1];
        pair<string, string> name = replay.getPlayerNamesFromReplayFile(replayFile);
        Player player1(name.first, 'X');
        Player player2(name.second, 'O');
        Game game(player1, player2);
        game.playWithOtherPlayer();
    }
    cin.ignore();
    cin.get();
}



void Game::viewReplay() {
    vector<string> replays = replay.getReplayList();
    if (replays.empty()) {
        cout << "No replays available(or type 'exit' to go back).\n";
        cout << "Press enter to back!";
        cin.ignore();
        cin.get();
        return;
    }
    else {
        cout << "Available replays:\n";
        for (size_t i = 0; i < replays.size(); ++i) {
            cout << i + 1 << ". " << replays[i] << "\n";
        }

        string input;
        int choice = -1;

        while (true) {
            cout << "Enter the number of the replay to view: ";
            cin >> input;

            if (input == "exit") {
                return; // Quay lại menu replay
            }

            if (isDigit(input)) {
                choice = stoi(input);
                if (choice >= 1 && choice <= replays.size()) {
                    break; // Đầu vào hợp lệ, thoát khỏi vòng lặp
                }
            }

            cout << "Invalid choice, please try again.\n";
        }

        string replayFile = replays[choice - 1];
        pair<string, string> names = replay.getPlayerNamesFromReplayFile(replayFile);

        // Tạo các đối tượng Player tạm thời từ thông tin trong tệp replay
        Player tempPlayer1(names.first, 'X');
        Player tempPlayer2(names.second, 'O');

        Game game(tempPlayer1, tempPlayer2);
        game.loadReplay(replayFile);
    }
    cin.ignore();
    cin.get();
}


// Thực hiện chiếu lại các nước đi 
void Game::loadReplay(const string& filename) {
    replay.loadReplay(filename, p1->getName(), p2->getName());

    Board::getInstance()->reset();
    for (const pair<int,int>& move : replay.getMoves()) {
        char mark = (turn % 2 == 0) ? p1->getMark() : p2->getMark();
        Board::getInstance()->placeMark(move.first, move.second, mark);
        Board::getInstance()->display();
        cout << ((turn % 2 == 0) ? p1->getName() : p2->getName()) << " (" << mark << ") moved to (" << move.first << ", " << move.second << ")\n";
        if (Board::getInstance()->checkWin(mark)) {
            cout << ((turn % 2 == 0) ? p1->getName() : p2->getName()) << " wins!\n";
            Sleep(2000);
            break;
        }
        Sleep(2000);
        turn++;
    }
}


