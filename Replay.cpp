#include "Replay.h"

Replay::Replay() {}

void Replay::saveMove(const pair<int, int>& move) {
    moves.push_back(move);
}

void Replay::saveReplay(const string& p1Name, const string& p2Name) {
    time_t now = time(0);
    tm localtm;
    localtime_s(&localtm, &now);

    filename = p1Name + "_vs_" + p2Name + "_" + to_string(localtm.tm_year + 1900) +
        to_string(localtm.tm_mon + 1) + to_string(localtm.tm_mday) + "_" +
        to_string(localtm.tm_hour) + to_string(localtm.tm_min) + to_string(localtm.tm_sec) + ".txt";

    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cout << "Error opening file for saving replay." << endl;
        return;
    }

    for (size_t i = 0; i < moves.size(); ++i) {
        outfile << (i % 2 == 0 ? p1Name : p2Name) << " " << moves[i].first << " " << moves[i].second << "\n";
    }
    outfile.close();
    cout << "Replay saved to " << filename << endl;

    ofstream replayList("replay_list.txt", ios::app);
    if (replayList.is_open()) {
        replayList << filename << "\n";
        replayList.close();
    }
    else {
        cout << "Error opening file for saving replay list." << endl;
    }
}

void Replay::loadReplay(const string& filename, const string& p1Name, const string& p2Name) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Error opening file for loading replay." << endl;
        return;
    }

    string playerName;
    int x, y;
    while (infile >> playerName >> x >> y) {
        char mark = (playerName == p1Name) ? 'X' : 'O';
        moves.push_back({ x, y });
    }
    infile.close();
}

pair<string, string> Replay::getPlayerNamesFromReplayFile(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error opening file for reading: " << filename << endl;
        return make_pair("", "");
    }

    string name1, name2;
    infile >> name1 >> name2;
    infile.close();
    return make_pair(name1, name2);
}

const vector<pair<int, int>>& Replay::getMoves() const {
    return moves;
}

vector<string> Replay::getReplayList(){
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