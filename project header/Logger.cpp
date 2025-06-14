#pragma once
#include "Logger.h"

void Logger::open(const std::string& filename) {
    logFile.open(filename.c_str());
}

void Logger::close() {
    logFile.close();
}

void Logger::logMessage(const std::string& msg) {
    if (logFile.is_open()) {
        logFile << msg << std::endl;
    }
}