#ifndef LOGGER_H_
#define LOGGER_H_
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

extern LogLevel MIN_LOG_LEVEL;  // Declaration only, actual definition should be in the source file where you include this header.

// Colors for logging
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";

// Function declarations
std::string GetCurrentTimeWithMs();

std::string ExtractFilename(const std::string& path);

template<typename T>
void LogHelper(std::ostringstream& oss, T t) {
    oss << t;
}

template<typename T, typename... Args>
void LogHelper(std::ostringstream& oss, T t, Args... args) {
    oss << t;
    LogHelper(oss, args...);
}

template<typename... Args>
void Log(LogLevel level, const std::string& file, int line, Args... args) {
    // ... (Implementation of the Log function as you provided it)
}

#define LOG(level, ...) Log(level, __FILE__, __LINE__, __VA_ARGS__)
#endif //LOGGER_H_