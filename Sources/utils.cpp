//
// Created by Matthis DoQuocBao on 2023-05-31.
//

#include "../Include/header.hpp"

bool setLogFile(const std::string& filename) {
    std::ofstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "fail to open file" << std::endl;
        return false;
    }
    file.close();
    return true;
}

void writeLogFile(const std::string& message, const std::string& filename) {

    std::time_t timestamp = std::time(NULL);

    std::string timestampStr = std::ctime(&timestamp);

    timestampStr = timestampStr.substr(0, timestampStr.length() - 1);
    std::ofstream logfile(filename.c_str(), std::ios::app);
    if (!logfile.is_open()) {
        std::cerr << "fail to open file" << std::endl;
        return;
    }
    logfile << "[" << timestampStr << "] " << message << std::endl;
    logfile.close();
}

void printLogFile(const std::string& filename) {

    std::ifstream logfile(filename.c_str());
    if (!logfile.is_open()) {
        std::cerr << "fail to open file" << std::endl;
        return;
    }
    std::cout << logfile << std::endl;
    logfile.close();
}


