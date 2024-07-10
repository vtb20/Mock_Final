#include "Utils.h"
#include <algorithm>

bool isDigit(const std::string& s) {
    return std::all_of(s.begin(), s.end(), ::isdigit);
}
