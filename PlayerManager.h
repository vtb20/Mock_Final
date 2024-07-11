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

    PlayerManager();

    void loadPlayers();

    void savePlayers() const;

public:
    ~PlayerManager();

    static PlayerManager& getInstance();

    PlayerManager(const PlayerManager&) = delete;

    void addOrUpdatePlayer(const Player& player);

    bool playerExists(const std::string& name) const;

    const Player* getPlayer(const std::string& name) const;

    vector<Player> getOpponentsWithSimilarSkill(const Player& player) const;

    void displayPlayerInfoAndSimilarPlayers(const string& name) const;
};

#endif // PLAYERMANAGER_H
