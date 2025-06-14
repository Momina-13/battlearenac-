#include "Utils.h"

// Simple string to int conversion function
int stringToInt(const std::string& str) {
    int result = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result;
}

// Simple int to string conversion function
std::string intToString(int value) {
    if (value == 0) return "0";

    std::string result = "";
    bool negative = false;
    if (value < 0) {
        negative = true;
        value = -value;
    }

    while (value > 0) {
        result = char('0' + value % 10) + result;
        value /= 10;
    }

    if (negative) result = "-" + result;
    return result;
}