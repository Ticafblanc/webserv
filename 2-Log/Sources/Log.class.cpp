//
// Created by Matthis DoQuocBao on 2023-06-05.
//


#include "../Includes/Log.class.hpp"

Log::Log() {}

Log::Log(const string &pathToLogFile) {
    std::ofstream file(pathToLogFile.c_str(), std::ios::trunc);
    if (!file.is_open())
        throw LogException("fail to open file");
    file.close();
}

Log::~Log() {}

Log::Log(const Log & other) : _pathToLogFile(other._pathToLogFile) {}

Log &Log::operator=(const Log & rhs) {
    this->_pathToLogFile = rhs._pathToLogFile;
    return *this;
}


void Log::writeLogFile(const std::string& message) {

    std::time_t timestamp = std::time(NULL);

    std::string timestampStr = std::ctime(&timestamp);

    timestampStr = timestampStr.substr(0, timestampStr.length() - 1);
    std::ofstream logfile(_pathToLogFile.c_str(), std::ios::app);
    if (!logfile.is_open())
        throw LogException("fail to open file");
    logfile << "[" << timestampStr << "] " << message << std::endl;
    logfile.close();
}

void Log::printLogFile() {
    std::ifstream logfile(_pathToLogFile.c_str());
    if (!logfile.is_open())
        throw LogException("fail to open file");
    std::string line;
    while (std::getline(logfile, line)) {
        std::cout << line << std::endl;
    }
    logfile.close();
}




