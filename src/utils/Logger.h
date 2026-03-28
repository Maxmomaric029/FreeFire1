#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>

namespace Logger {
    inline void Init() {
        std::ofstream file("resources/panel.log", std::ios::out | std::ios::trunc);
        if(file.is_open()) {
            file << "[LOG START] " << __DATE__ << " " << __TIME__ << "\n";
        }
    }

    inline void Info(const std::string& msg) {
        std::ofstream file("resources/panel.log", std::ios::app);
        std::string logMsg = "[INFO] " + msg + "\n";
        if(file.is_open()) file << logMsg;
        std::cout << logMsg;
    }

    inline void Error(const std::string& msg) {
        std::ofstream file("resources/panel.log", std::ios::app);
        std::string logMsg = "[ERROR] " + msg + "\n";
        if(file.is_open()) file << logMsg;
        std::cerr << logMsg;
    }
}
