//
// Created by Matthis DoQuocBao on 2023-06-05.
//


#include <Source_Code/1-Config/Includes/Log.class.hpp>

Log::Log() {}

Log::Log(const std::string &pathToLogFile) : _pathToLogFile(pathToLogFile){
    setLog(pathToLogFile);
}

Log::~Log() {}

Log::Log(const Log & other) : _pathToLogFile(other._pathToLogFile) {}

Log &Log::operator=(const Log & rhs) {
    this->_pathToLogFile = rhs._pathToLogFile;
    return *this;
}

void Log::setLog(const std::string &pathToLogFile) {
    _pathToLogFile = pathToLogFile;
    std::ofstream file(pathToLogFile.c_str(), std::ios::trunc);
    if (!file.is_open())
        throw LogException("fail to open file");
    file.close();
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



Log::LogException::LogException(const char * message)
        : _message(message) {}

Log::LogException::~LogException() throw() {}

const char * Log::LogException::what() const throw() { return _message.c_str(); }

Log::LogException::LogException(const LogException & other) : _message(other._message) {}

Log::LogException &Log::LogException::operator=(const LogException &rhs) {
    this->_message = rhs._message;
    return *this;
}



