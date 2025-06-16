#pragma once
#include "Logger.h"

using namespace std;

void Logger::open(const string& filename) {
    logFile.open(filename.c_str());
}

void Logger::close() {
    logFile.close();
}

void Logger::logMessage(const string& msg) {
    if (logFile.is_open()) {
        logFile << msg << endl;
    }
}
