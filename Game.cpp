#include "Game.h"

Game::Game(const Player& player1, const Player& player2)
    : p1(new Player(player1)), p2(new Player(player2)), turn(0) {
}

Game::Game(const Player& player1, const Bot& bot)
    : p1(new Player(player1)), p2(new Bot(bot)), turn(0) {
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
            currentPlayer->addWin(1);
        }
        else if (board.isFull()) {
            board.display();
            std::cout << "The game is a draw.\n";
            gameOver = true;
            currentPlayer->addDraw(1);
        }

        turn++;
    }
    saveReplay();
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
    saveReplay();
}

vector<string> Game::getReplayList() {
    vector<string> replayFiles;
    ifstream replayList("replay_list.txt");
    if (replayList.is_open()) {
        string line;
        while (getline(replayList, line)) {
            replayFiles.push_back(line);
        }
        replayList.close();
    }
    return replayFiles;
}

void Game::playReplay() {
    vector<string> replays = getReplayList();
    if (replays.empty()) {
        cout << "No replays available.\n";
    }
    else {
        cout << "Choose a game to play back:\n";
        for (size_t i = 0; i < replays.size(); ++i) {
            cout << i + 1 << ". " << replays[i] << "\n";
        }
        cout << "Enter the number of the replay: ";
        int choice;
        cin >> choice;
        while (choice < 1 || choice > replays.size()) {
            cout << "Invalid choice, please try again: ";
            cin >> choice;
        }
        string replayFile = replays[choice - 1];
        pair<string, string> name = getPlayerNamesFromReplayFile(replayFile);
        Player player1(name.first, 'X');
        Player player2(name.second, 'O');
        Game game(player1, player2);
        game.playWithOtherPlayer();
    }
    
}


void Game::viewReplay() {
    vector<string> replays = getReplayList();
    if (replays.empty()) {
        cout << "No replays available.\n";
    }
    else {
        cout << "Available replays:\n";
        for (size_t i = 0; i < replays.size(); ++i) {
            cout << i + 1 << ". " << replays[i] << "\n";
        }
        cout << "Enter the number of the replay to view: ";
        int choice;
        cin >> choice;
        while (choice < 1 || choice > replays.size()) {
            cout << "Invalid choice, please try again: ";
            cin >> choice;
        }
        string replayFile = replays[choice - 1];
        Player player1("Player1", 'X');
        Player player2("Player2", 'O');
        Game game(player1, player2);
        game.loadReplay(replayFile);
    }
    cin.get();
}

void Game::saveReplay()  {
    replay.saveReplay(p1->getName(), p2->getName());
}

void Game::loadReplay(const string& filename) {
    replay.loadReplay(filename, p1->getName(), p2->getName());

    board.reset();
    for (const auto& move : replay.getMoves()) {
        char mark = (turn % 2 == 0) ? p1->getMark() : p2->getMark();
        board.placeMark(move.first, move.second, mark);
        board.display();
        cout << ((turn % 2 == 0) ? p1->getName() : p2->getName()) << " (" << mark << ") moved to (" << move.first << ", " << move.second << ")\n";
        if (board.checkWin(mark)) {
            cout << ((turn % 2 == 0) ? p1->getName() : p2->getName()) << " wins!\n";
            break;
        }
        cout << "Press enter to continue...";
        cin.get();
        turn++;
    }
}

pair<string, string> Game::getPlayerNamesFromReplayFile(const string& filename) {
    return Replay::getPlayerNamesFromReplayFile(filename);
}
