#include <iostream>
#include <cctype>
#include <string>
#include "Player.h" 
using namespace std;

#include "Game.h"


static void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static bool isDigit(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

static void showMainMenu() {
    cout << "*-----------MAIN MENU-----------*\n";
    cout << "Press number to choice:\n";
    cout << "1. Play with Other Player\n";
    cout << "2. Play with BOT\n";
    cout << "3. Replay\n";
    cout << "4. Player's Information\n";
    cout << "5. Guild\n";
    cout << "6. Exit\n";
}

static void showSubMenuWBot() {
    cout << "*--------Play with BOT--------*\n";
    cout << "Press number to choice:\n";
    cout << "1. Easy Mode\n";
    cout << "2. Normal Mode\n";
    cout << "3. Hard Mode\n";
    cout << "4. Back to MAIN MENU\n";
}

static void displayGuide() {
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
}

int main() {
    bool exit = false;
    string input1;

    while (!exit) {
        clearScreen();
        showMainMenu();
        cin >> input1;
        while (!isDigit(input1) || stoi(input1) < 1 || stoi(input1) > 6) {
            cout << "Wrong input! please try again: " << endl;
            cin >> input1;
        }

        switch (stoi(input1)) {
        case 1: {
            clearScreen();
            cout << "Your choice is play with other player!\n";
            string name1, name2;
            cout << "Enter name for Player 1 (X): ";
            cin >> name1;
            cout << "Enter name for Player 2 (O): ";
            cin >> name2;

            Player player1(name1, 'X');
            Player player2(name2, 'O');

            Game game(player1, player2);
            game.playWithOtherPlayer();
            cin.ignore();
            cin.get();
            break;
        }
        case 2: {
            string input2;
            bool backToMain = false;

            while (!backToMain) {
                clearScreen();
                showSubMenuWBot();
                cin >> input2;
                while (!isDigit(input2) || stoi(input2) < 1 || stoi(input2) > 4) {
                    cout << "Wrong input! please try again: " << endl;
                    cin >> input2;
                }

                switch (stoi(input2)) {
                case 1:
                    clearScreen();
                    cout << "You chose Easy Mode.\n";

                    cin.ignore();
                    cin.get(); 
                    break;
                case 2:
                    clearScreen();
                    cout << "You chose Normal Mode.\n";

                    cin.ignore();
                    cin.get(); 
                    break;
                case 3:
                    clearScreen();
                    cout << "You chose Hard Mode.\n";
                    // Khởi tạo trò chơi với bot khó

                    cin.ignore();
                    cin.get(); 
                    break;
                case 4:
                    backToMain = true;
                    break;
                default:
                    cout << "Invalid choice, please try again.\n";
                }
            }
            break;
        }
        case 3:
            clearScreen();
            cout << "Replay\n";
            // Chơi lại game đấu gần nhất 
            cin.ignore();
            cin.get();
            break;
        case 4:
            clearScreen();
            cout << "Sreaching player's information.\n";
            // Show thông tin player theo tên     
            cin.ignore();
            cin.get(); 
            break;
        case 5:
            clearScreen();
             // Show guide hướng dẫn 
            displayGuide();
            cin.ignore();
            cin.get();
            break;
        case 6:
            exit = true;
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }

    cout << "Exiting program...\n";
    return 0;
}
