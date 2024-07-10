#include "Utils.h"
#include <algorithm>

bool isDigit(const std::string& s) {
    return std::all_of(s.begin(), s.end(), ::isdigit);
}

bool isIn(vector <pair<int, int>> v, pair<int, int> p) {
    for (int i = 0; i < v.size(); i++) {
        if (p.first == v[i].first && p.second == v[i].second) {
            return true;
        }
    }
    return false;
}