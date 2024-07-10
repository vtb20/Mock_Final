#include "PlayerManager.h"

// Constructor private để ngăn chặn khởi tạo từ bên ngoài
PlayerManager::PlayerManager() {
    loadPlayers();
}

// Hàm để đọc file và tải dữ liệu người chơi vào danh sách
void PlayerManager::loadPlayers() {
    std::ifstream file("players.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name;
            int wins, losses, draws;
            if (iss >> name >> wins >> losses >> draws) {
                Player player(name, ' ');
                player.addWin(wins);
                player.addLoss(losses);
                player.addDraw(draws);
                players.push_back(player);
            }
        }
        file.close();
    }
}

// Hàm để ghi danh sách người chơi vào file
void PlayerManager::savePlayers() const {
    std::ofstream file("players.txt");
    if (file.is_open()) {
        for (const Player& player : players) {
            file << player.getName() << " "
                << player.getWins() << " "
                << player.getLosses() << " "
                << player.getDraws() << "\n";
        }
        file.close();
    }
}

// Destructor để lưu dữ liệu khi đối tượng bị hủy
PlayerManager::~PlayerManager() {
    savePlayers();
}

// Cung cấp phương thức để truy cập đối tượng duy nhất
PlayerManager& PlayerManager::getInstance() {
    static PlayerManager instance;
    return instance;
}

// Hàm để thêm hoặc cập nhật thông tin người chơi
void PlayerManager::addOrUpdatePlayer(const Player& player) {
    for (Player& p : players) {
        if (p.getName() == player.getName()) {
            p.addWin(player.getWins());
            p.addLoss(player.getLosses());
            p.addDraw(player.getDraws());
            savePlayers();
            return;
        }
    }
    players.push_back(player);
    savePlayers();
}

// Hàm để kiểm tra sự tồn tại của người chơi
bool PlayerManager::playerExists(const std::string& name) const {
    for (const Player& player : players) {
        if (player.getName() == name) {
            return true;
        }
    }
    return false;
}

// Hàm để lấy thông tin người chơi
const Player* PlayerManager::getPlayer(const std::string& name) const {
    for (const Player& player : players) {
        if (player.getName() == name) {
            return &player;
        }
    }
    return nullptr;
}

struct WinLossDrawRatio {
    double winRatio;
    double lossRatio;
    double drawRatio;
};

WinLossDrawRatio calculateWinLossDrawRatio(const Player& player) {
    int totalGames = player.getWins() + player.getLosses() + player.getDraws();
    if (totalGames == 0) {
        return { 0.0, 0.0, 0.0 }; // Avoid division by zero
    }
    return {
        static_cast<double>(player.getWins()) / totalGames,
        static_cast<double>(player.getLosses()) / totalGames,
        static_cast<double>(player.getDraws()) / totalGames
    };
}


// Add this method to the PlayerManager class
void PlayerManager::displayPlayerInfoAndSimilarPlayers(const std::string& name) const {
    system("cls");
    const Player* player = getPlayer(name);
    if (player) {
        cout << "Player Information:\n";
        cout << "Name: " << player->getName() << "\n";
        cout << "Wins: " << player->getWins() << "\n";
        cout << "Losses: " << player->getLosses() << "\n";
        cout << "Draws: " << player->getDraws() << "\n";

        cout << "\nFinding opponents with similar skill level...\n";
        vector<Player> similarPlayers = getOpponentsWithSimilarSkill(*player);
        if (!similarPlayers.empty()) {
            cout << "Found the following opponents:\n";
            for (const auto& opponent : similarPlayers) {
                cout << "Name: " << opponent.getName() << "\n";
                cout << "Wins: " << opponent.getWins() << ", Losses: " << opponent.getLosses() << ", Draws: " << opponent.getDraws() << "\n";
                cout << "-----------------------------------\n";
            }
        }
        else {
            cout << "No opponents with similar skill level found.\n";
        }
    }
    else {
        cout << "Player not found.\n";
    }
}

vector<Player> PlayerManager::getOpponentsWithSimilarSkill(const Player& player) const {
    vector<Player> similarSkillOpponents;
    WinLossDrawRatio playerRatio = calculateWinLossDrawRatio(player);

    for (const auto& opponent : players) {
        if (opponent.getName() == player.getName()) {
            continue; // Skip the same player
        }
        WinLossDrawRatio opponentRatio = calculateWinLossDrawRatio(opponent);

        // Define your threshold for similarity, e.g., within 10% difference
        double threshold = 0.3;

        if (fabs(playerRatio.winRatio - opponentRatio.winRatio) <= threshold &&
            fabs(playerRatio.lossRatio - opponentRatio.lossRatio) <= threshold &&
            fabs(playerRatio.drawRatio - opponentRatio.drawRatio) <= threshold) {
            similarSkillOpponents.push_back(opponent);
        }
    }

    return similarSkillOpponents;
}
