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

// LogLevel MIN_LOG_LEVEL = DEBUG;
LogLevel MIN_LOG_LEVEL = INFO;
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";

std::string GetCurrentTimeWithMs()
{
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    long duration = value.count();
    long seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch).count();
    long milliseconds = duration - seconds * 1000;

    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    struct tm* timeinfo = localtime(&currentTime);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    std::ostringstream oss;
    oss << buffer << '.' << std::setfill('0') << std::setw(3) << milliseconds;

    return oss.str();
}

template<typename T>
void LogHelper(std::ostringstream& oss, T t)
{
    oss << t;
}

template<typename T, typename... Args>
void LogHelper(std::ostringstream& oss, T t, Args... args)
{
    oss << t;
    LogHelper(oss, args...);
}

std::string ExtractFilename(const std::string& path) {
    auto pos = path.find_last_of("/\\");
    if (pos != std::string::npos) {
        return path.substr(pos + 1);
    }
    return path;
}

template<typename... Args>
void Log(LogLevel level, const std::string& file, const std::string& function, int line, Args... args)
{
    if (level < MIN_LOG_LEVEL) {
        return;
    }

    std::string timeStr = GetCurrentTimeWithMs();
    std::string levelStr;
    std::string colorCode;
    switch(level) {
        case DEBUG:    
            levelStr = "DEBUG"; 
            colorCode = BLUE;
            break;
        case INFO:     
            levelStr = "INFO"; 
            colorCode = GREEN;
            break;
        case WARNING:  
            levelStr = "WARNING"; 
            colorCode = YELLOW;
            break;
        case ERROR:    
            levelStr = "ERROR"; 
            colorCode = RED;
            break;
        default:       
            levelStr = "UNKNOWN"; 
            colorCode = RESET;
            break;
    }

    std::ostringstream oss;
    LogHelper(oss, args...);
    
    std::string filename = ExtractFilename(file);
    size_t pos1 = filename.find(".cpp");
        if (pos1 != std::string::npos) {
            filename = filename.substr(0, pos1); // Remove "()"
        }
    
    // Create a non-const copy of the function and remove "void" and "()"
    std::string functionCopy = function;
    size_t pos = functionCopy.find("::");
    if (pos != std::string::npos) {
        functionCopy = functionCopy.substr(pos + 2); // Extract the function name without class name
        pos = functionCopy.find("(");
        if (pos != std::string::npos) {
            functionCopy = functionCopy.substr(0, pos); // Remove "()"
        }
    }
    
    std::cout << "[" << timeStr << "][" << levelStr << "][" << filename << "::" << functionCopy << ":" << line << "] " << colorCode << oss.str() << RESET << std::endl;
}

#define LOG(level, ...) Log(level, __FILE__, __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__)

// int main() {
//     class MyClass {
//     public:
//         void logSomething() {
//             LOG(DEBUG, "This is a debug message from MyClass");
//             LOG(INFO, "This is an info message from MyClass");
//             LOG(ERROR, "This is an error message from MyClass");
//         }
//     };

//     MyClass myObject;
//     myObject.logSomething();

//     return 0;
// }
