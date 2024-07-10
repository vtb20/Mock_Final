#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "Player.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

class PlayerManager {
private:
    vector<Player> players;

    // Constructor private để ngăn chặn khởi tạo từ bên ngoài
    PlayerManager();

    // Hàm để đọc file và tải dữ liệu người chơi vào danh sách
    void loadPlayers();

    // Hàm để ghi danh sách người chơi vào file
    void savePlayers() const;

public:
    // Destructor để lưu dữ liệu khi đối tượng bị hủy
    ~PlayerManager();

    // Cung cấp phương thức để truy cập đối tượng duy nhất
    static PlayerManager& getInstance();

    // Xóa bỏ các constructor, copy constructor và operator= để đảm bảo Singleton
    PlayerManager(const PlayerManager&) = delete;
    void operator=(const PlayerManager&) = delete;

    // Hàm để thêm hoặc cập nhật thông tin người chơi
    void addOrUpdatePlayer(const Player& player);

    // Hàm để kiểm tra sự tồn tại của người chơi
    bool playerExists(const std::string& name) const;

    // Hàm để lấy thông tin người chơi
    const Player* getPlayer(const std::string& name) const;

    vector<Player> getOpponentsWithSimilarSkill(const Player& player) const;

    void displayPlayerInfoAndSimilarPlayers(const string& name) const;
};

#endif // PLAYERMANAGER_H
