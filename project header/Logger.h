#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
private:
    std::ofstream logFile;

public:
    void open(const std::string& filename);
    void close();
    void logMessage(const std::string& msg);
};

#endif