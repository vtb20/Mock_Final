#include "Game.h"

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

void Game::gameOverDisplay() {
    cout << "GAME OVER! " << endl;
    cout << "1.PLAY AGAIN." << endl;
    cout << "2.BACK TO MAIN MENU. \n";
}

void Game::showReplayMenu() {
    cout << "*--------REPLAY MENU--------*\n";
    cout << "Press number to choice:\n";
    cout << "1. Play back an old game\n";
    cout << "2. View an old game\n";
    cout << "3. Back to MAIN MENU\n";
}
void Game::showMainMenu() {
    cout << "*-----------MAIN MENU-----------*\n";
    cout << "Press number to choice:\n";
    cout << "1. Play with Other Player\n";
    cout << "2. Play with BOT\n";
    cout << "3. Replay\n";
    cout << "4. Player's Information\n";
    cout << "5. Guide\n";
    cout << "6. Exit\n";
}

void Game::showSubMenuWBot() {
    cout << "*--------Play with BOT--------*\n";
    cout << "Press number to choice:\n";
    cout << "1. Easy Mode\n";
    cout << "2. Normal Mode\n";
    cout << "3. Hard Mode\n";
    cout << "4. Back to MAIN MENU\n";
}

void Game::displayGuide() {
    cout << "Welcome to the Caro Game Guide!\n\n";
    cout << "Rules of the Game:\n";
    cout << "1. Caro is played on a board of 15x15 cells.\n";
    cout << "2. Two players take turns to place their marks (X or O) on the board.\n";
    cout << "3. The objective is to align 5 of your marks in a row horizontally, vertically, or diagonally before your opponent does.\n";
    cout << "4. The game ends when one player aligns 5 marks in a row or when the board is full, resulting in a draw.\n\n";
    cout << "Game Controls:\n";
    cout << "1. At the start, each player will be prompted to enter their name.\n";
    cout << "2. Players will take turns to enter the coordinates of their move (row and column).\n";
    cout << "3. The game will indicate invalid moves, such as placing a mark outside the board or on an occupied cell.\n";
    cout << "4. To make a move, enter the row and column numbers separated by a space (e.g., '3 4' to place a mark on the cell at row 3, column 4).\n";
    cout << "5. Players can quit the game at any time by entering 'quit'.\n\n";
    cout << "Enjoy the game and good luck!\n";
    cout << "Press enter to back main menu.";
}


void Game::handleGameOver() {
    bool gameOV = false;
    while (!gameOV) {
        system("cls");
        gameOverDisplay();
        string choiceGV;
        cin >> choiceGV;

        while (!isDigit(choiceGV) || stoi(choiceGV) < 1 || stoi(choiceGV) > 2) {
            cout << "Wrong input! please try again: " << endl;
            cin >> choiceGV;
        }

        switch (stoi(choiceGV)) {
        case 1:
            playWithOtherPlayer();
            break;
        case 2:
            gameOV = true;
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
}

void Game::loop() {
    bool exit = false;
    string input1;
    Game game;

    while (!exit) {
        system("cls");
        showMainMenu();
        bool backToMain = false;
        cin >> input1;
        while (!isDigit(input1) || stoi(input1) < 1 || stoi(input1) > 6) {
            cout << "Wrong input! please try again: " << endl;
            cin >> input1;
        }

        switch (stoi(input1)) {
        case 1: {
            system("cls");
            cout << "Your choice is play with other player!\n";
            cout << "Or You can enter exit in the name input to back \n";
            string name1, name2;
            cout << "Enter name for Player 1 (X): ";
            cin.ignore();
            getline(cin, name1);
            if (name1 == "exit")
            {
                break;
            }
            cout << "Enter name for Player 2 (O): ";
            getline(cin, name2);
            if (name2 == "exit")
            {
                break;
            }
            Player player1(name1, 'X');
            Player player2(name2, 'O');

            Game game(player1, player2);
            game.playWithOtherPlayer();
            handleGameOver();
            cin.ignore();
            break;
        }
        case 2: {
            string input2;
            bool backToMain = false;

            while (!backToMain) {
                system("cls");
                showSubMenuWBot();
                cin >> input2;
                while (!isDigit(input2) || stoi(input2) < 1 || stoi(input2) > 4) {
                    cout << "Wrong input! please try again: " << endl;
                    cin >> input2;
                }

                switch (stoi(input2)) {
                case 1:
                {
                    system("cls");
                    cout << "You chose Easy Mode.\n";
                    cout << "Enter your name: \n";

                    Player player1("Player", 'X');
                    Bot bot("Easy Bot", 'O', 1);

                    Game game(player1, bot);
                    game.playVsBot();
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 2:
                {
                    system("cls");
                    cout << "You chose Normal Mode.\n";

                    cout << "Enter your name: \n";

                    Player player1("Player", 'X');
                    Bot bot("Normal Bot", 'O', 2);

                    Game game(player1, bot);
                    game.playVsBot();
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 3:
                {
                    system("cls");
                    cout << "You chose Hard Mode.\n";

                    cout << "Enter your name: \n";

                    Player player1("Player", 'X');
                    Bot bot("Hard Bot", 'O', 3);

                    Game game(player1, bot);
                    game.playVsBot();

                    cin.ignore();
                    cin.get();
                    break;
                }
                case 4:
                    backToMain = true;
                    break;
                default:
                    cout << "Invalid choice, please try again.\n";
                }
            }
            break;
        }
        case 3: {
            while (!backToMain) {
                system("cls");
                showReplayMenu();
                string input3;
                cin >> input3;

                // Kiểm tra đầu vào hợp lệ
                if (!isDigit(input3) || stoi(input3) < 1 || stoi(input3) > 3) {
                    cout << "Wrong input! please try again: " << endl;
                    continue;
                }

                int choice = stoi(input3);
                system("cls");
                Game game;

                switch (choice) {
                case 1:
                    game.playReplay();
                    break;
                case 2:
                    game.viewReplay();
                    break;
                case 3:
                    backToMain = true;
                    break;
                default:
                    break;
                }
            }
            break;
        }
        case 4: {
            system("cls");
            cout << "Searching player's information.\n";
            while (!backToMain) {
                string nameSearching;
                cout << "Enter your name player (or type 'exit' to go back Main menu): ";
                if (cin.peek() == '\n') {
                    cin.ignore();
                }
                getline(cin, nameSearching);
                if (nameSearching == "exit") {
                    backToMain = true;
                }
                else {
                    PlayerManager::getInstance().displayPlayerInfoAndSimilarPlayers(nameSearching);
                }
            }
            break;
        }


        case 5:
            system("cls");
            displayGuide();
            cin.get();
            break;
        case 6:
            exit = true;
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }

    std::cout << "Exiting program...\n";
}