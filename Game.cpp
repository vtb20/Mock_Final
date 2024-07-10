#include "Game.h"
#include "Utils.h"


Game::Game() {
    p1 = nullptr;
    p2 = nullptr;
    turn = 0;
};

Game::Game(const Player& player1, const Player& player2 )
    : p1(new Player(player1)), p2(new Player(player2)), turn(0) {
   
        PlayerManager::getInstance().addOrUpdatePlayer(player1);
        PlayerManager::getInstance().addOrUpdatePlayer(player2);
    
}

Game::Game(const Player& player1, const Bot& bot)
    : board(), p1(new Player(player1)), p2(new Bot(bot)), turn(0) {
    PlayerManager::getInstance().addOrUpdatePlayer(player1);
}


void Game::playVsBot() {
    bool gameOver = false;
    while (!gameOver) {
        board.display();
        Player* currentPlayer = (turn % 2 == 0) ? p1 : p2;

        std::cout << currentPlayer->getName() << " turn (" << currentPlayer->getMark() << "): ";

        pair<int, int> move = currentPlayer->makeMove();
        while (!board.placeMark(move.first, move.second, currentPlayer->getMark())) {
            std::cout << "Invalid move. Try again: ";
            move = currentPlayer->makeMove();
        }
        
        replay.saveMove(move);

        if (board.checkWin(currentPlayer->getMark())) {
            board.display();
            std::cout << currentPlayer->getName() << " wins!\n";
            gameOver = true;
        }
        else if (board.isFull()) {
            board.display();
            std::cout << "The game is a draw.\n";
            gameOver = true;
        }

        turn++;
    }
}

void Game::PlayAgain() {
    board.reset();
    playWithOtherPlayer();
}

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

        replay.saveMove(move);

        if (board.checkWin(currentPlayer->getMark())) {
            board.display();
            cout << currentPlayer->getName() << " wins!\n";
            gameOver = true;
            currentPlayer->addWin(1);
            opponent->addLoss(1);
            PlayerManager::getInstance().addOrUpdatePlayer(*currentPlayer);
            PlayerManager::getInstance().addOrUpdatePlayer(*opponent);
        }
        else if (board.isFull()) {
            board.display();
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
        cout << "No replays available.\n";
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

    board.reset();
    for (const pair<int,int>& move : replay.getMoves()) {
        char mark = (turn % 2 == 0) ? p1->getMark() : p2->getMark();
        board.placeMark(move.first, move.second, mark);
        board.display();
        cout << ((turn % 2 == 0) ? p1->getName() : p2->getName()) << " (" << mark << ") moved to (" << move.first << ", " << move.second << ")\n";
        if (board.checkWin(mark)) {
            cout << ((turn % 2 == 0) ? p1->getName() : p2->getName()) << " wins!\n";
            cout << "Press enter to return Replay Menu";
            break;
        }
        cout << "Press enter to continue...";
        cin.get();
        turn++;
    }
}


