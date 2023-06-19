//
// Created by Matthis DoQuocBao on 2023-06-05.
//


#include <Source_Code/1-Config/Includes/Log.class.hpp>

Log::Log() {}

Log::Log(const std::string &pathToLogFile) : _pathToLogFile(pathToLogFile), _indent(){
    setLog(pathToLogFile);
}

Log::~Log() {}

Log::Log(const Log & other) : _pathToLogFile(other._pathToLogFile), _indent(other._indent){}

Log &Log::operator=(const Log & rhs) {
    this->_pathToLogFile = rhs._pathToLogFile;
    this->_indent = rhs._indent;
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
    logfile << "[" << timestampStr << "] " << _indent << message << std::endl;
    logfile.close();
}

void Log::writePidLogFile(const std::string& message) {
    std::ofstream logfile(_pathToLogFile.c_str(), std::ios::app);
    if (!logfile.is_open())
        throw LogException("fail to open file");
    logfile << _indent << message << std::endl;
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

void Log::addIndent() {
    _indent += "\t";
}

void Log::removeIndent() {
    _indent.erase(0, 1);
}

std::string Log::convertEventsTostring(int events){
    return std::string((events & (EPOLLOUT | EPOLLET)) ? "EPOLLOUT | EPOLLET" :
                       ((events & (EPOLLIN | EPOLLET)) ? "EPOLLIN | EPOLLET" :
                        ((events & (EPOLLOUT)) ? "EPOLLOUT" :
                         (events & (EPOLLIN)) ? "EPOLLIN" : "ERROR" )));
}

void Log::success() {
    addIndent();
    writePidLogFile(" >>>> Sucesss <<<<");
    removeIndent();
}

void Log::failure() {
    addIndent();
    writePidLogFile(" >>>> Failure <<<<");
    removeIndent();
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



