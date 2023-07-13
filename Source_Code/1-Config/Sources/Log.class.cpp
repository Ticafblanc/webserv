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

//void Log::writeTimeLogFile(const std::string& message) {
//    std::time_t timestamp = std::time(NULL);
//
//    std::string timestampStr = std::ctime(&timestamp);
//
//    timestampStr = "[" + timestampStr.substr(0, timestampStr.length() - 1) +  "] ";
//}

bool Log::setTime() {
    std::time_t timestamp = std::time(NULL);
    if (timestamp == _timestamp)
        return false;
    _timestampStr = std::ctime(&timestamp);
    _timestampStr = "[" + _timestampStr.substr(0, _timestampStr.length() - 1) +  "] ";
    return true;
}

void Log::setMessage(const std::string& message) {
    _message = message;
}

void Log::writeMessageLogFile(const std::string& message) {
    setMessage(message);
    if (_logEnable) {
        std::ofstream logfile(_pathToLogFile.c_str(), std::ios::app);
        if (!logfile.is_open())
            throw LogException("fail to open file");
        if (setTime())
            logfile << "\n" << _timestampStr << "\n" << std::endl;
        logfile << *this;
        logfile.close();
    }
}



std::ostream &operator<<(std::ostream &os, const Log &log) {
    os << log._indent << log._message;
    return os;
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
    writeMessageLogFile(" >>>> Sucesss <<<<");
    removeIndent();
}

void Log::failure() {
    addIndent();
    writeMessageLogFile(" >>>> Failure <<<<");
    removeIndent();
}

void Log::setLogEnable(bool logEnable) {
    _logEnable = logEnable;
}

void Log::setIndent(const std::string &indent) {
    _indent = indent;
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



