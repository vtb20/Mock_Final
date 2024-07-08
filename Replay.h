#ifndef REPLAY_H
#define REPLAY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Replay {
private:
    vector<pair<int, int>> moves;
    string filename;

public:
    Replay();

    void saveMove(const pair<int, int>& move);
    void saveReplay(const string& p1Name, const string& p2Name);
    void loadReplay(const string& filename, const string& p1Name, const string& p2Name);
    static pair<string, string> getPlayerNamesFromReplayFile(const string& filename);
    static vector<string> getReplayList();
    const vector<pair<int, int>>& getMoves() const;
};

#endif // REPLAY_H
