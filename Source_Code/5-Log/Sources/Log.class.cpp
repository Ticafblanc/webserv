//
// Created by Matthis DoQuocBao on 2023-06-05.
//


#include <Includes/Log.class.hpp>


Log::Log()
:_pathToPidLogFile(_PATHTOPIDLOGFILE_), _pathToConfigLogFile(_PATHTOCONFIGLOGFILE_),
_pathToAccessLogFile(_PATHTOACCESSLOGFILE_), _pathToErrorLogFile(_PATHTOERRORLOGFILE_),
_accessLogBuffer(), _errorLogBuffer(), _indent(), _timestamp(), _endLog(false){
    setLog(_pathToPidLogFile);
    setLog(_pathToConfigLogFile);
    setLog(_pathToAccessLogFile);
    setLog(_pathToErrorLogFile);
    if (pthread_mutex_init(&_threadMutexAccess, NULL) ||
    pthread_mutex_init(&_threadMutexError, NULL) ||
    pthread_mutex_init(&_threadMutexEndLog, NULL))
        throw std::runtime_error("fail to init mutex");
    pthread_create(&_threadIdCheck, NULL, &Log::checkBuffers, this);
}

Log::~Log() {
    setEndLog();
    pthread_mutex_lock(&(_threadMutexAccess));
    if (!_accessLogBuffer.empty())
        flushAccessBuffers();
    pthread_mutex_unlock(&(_threadMutexAccess));
    pthread_mutex_lock(&(_threadMutexError));
    if (!_errorLogBuffer.empty())
        flushErrorBuffers();
    pthread_join(_threadIdCheck, NULL);
    pthread_mutex_unlock(&(_threadMutexError));
    pthread_mutex_destroy(&_threadMutexError);
    pthread_mutex_destroy(&_threadMutexAccess);
    pthread_mutex_destroy(&_threadMutexEndLog);
    setLog(_pathToPidLogFile);
}

Log::Log(const Log & other)
:_pathToPidLogFile(other._pathToPidLogFile), _pathToConfigLogFile(other._pathToConfigLogFile),
_pathToAccessLogFile(other._pathToAccessLogFile), _pathToErrorLogFile(other._pathToErrorLogFile),
_accessLogBuffer(other._accessLogBuffer), _errorLogBuffer(other._errorLogBuffer), _indent(other._indent),
_timestamp(other._timestamp),_endLog(other._endLog){}

Log &Log::operator=(const Log & rhs) {
    if (this != &rhs){
        this->_pathToPidLogFile = rhs._pathToPidLogFile;
        this->_pathToConfigLogFile = rhs._pathToConfigLogFile;
        this->_pathToAccessLogFile = rhs._pathToAccessLogFile;
        this->_pathToErrorLogFile = rhs._pathToErrorLogFile;
        this->_accessLogBuffer = rhs._accessLogBuffer;
        this->_errorLogBuffer = rhs._accessLogBuffer;
        this->_indent = rhs._indent;
        this->_timestamp = rhs._timestamp;
        this->_endLog = rhs._endLog;
    }
    return *this;
}

void Log::setPathToPidLogFile(const std::string &pathToLogFile) {
    if (setLog(pathToLogFile))
        _pathToPidLogFile = pathToLogFile;
}

void Log::setPathToConfigLogFile(const std::string &pathToLogFile) {
    if (setLog(pathToLogFile))
        _pathToConfigLogFile = pathToLogFile;

}

void Log::setPathToAccessLogFile(const std::string &pathToLogFile) {
    if (setLog(pathToLogFile))
        _pathToAccessLogFile = pathToLogFile;

}

void Log::setPathToErrorLogFile(const std::string &pathToLogFile) {
    if (setLog(pathToLogFile))
        _pathToErrorLogFile = pathToLogFile;
}

bool Log::setLog(const std::string &pathToLogFile) {
    std::ofstream file(pathToLogFile.c_str(), std::ios::trunc);
    if (!file.is_open())
        std::cerr << "fail to open file " <<  pathToLogFile << std::endl;
    file.close();
    return true;
}

std::string Log::setTime() {
    _timestamp = std::time(NULL);
    std::ostringstream oss;
    oss << "\n" << std::asctime(std::localtime(&_timestamp)) ;
    return oss.str();
}

void Log::addIndent() {
    _indent += "\t";
}

void Log::removeIndent() {
    if (!_indent.empty())
        _indent.erase(0, 1);
}

void Log::addEventToAccess(const int id, const int fd, const int events) {
    std::ostringstream oss;
    oss << _indent << "Event number [" << id
    << "] with an event fd [" << fd
#ifdef LINUX
    << "] and events flag => [" << std::string((events & EPOLLOUT && events & EPOLLET) ? "EPOLLOUT | EPOLLET" :
                                               (events & EPOLLIN && events &EPOLLET) ? "EPOLLIN | EPOLLET" :
                                               ((events & EPOLLOUT) ? "EPOLLOUT" :
                                                (events & EPOLLIN) ? "EPOLLIN" : "ERROR" ))
#endif

#ifdef MAC
    << "] and events flag => [" << std::string((events & EVFILT_READ ) ? "EVFILT_READ" :
                                               (events & EVFILT_WRITE) ? "EVFILT_WRITE" : "ERROR" )
#endif

    << "]" << std::endl;
    pthread_mutex_lock(&(_threadMutexAccess));
    _accessLogBuffer.push(oss.str());
    pthread_mutex_unlock(&(_threadMutexAccess));
    return ;
}

void Log::addClientToAccess(const std::string& ipAddress, const int port, const int clientSocket, const int serverSocket) {
    std::ostringstream oss;
    oss << _indent << "Address [" << ipAddress << ":"
    << port << "] with socket [" << clientSocket << "] on socket server ["
    << serverSocket <<  "]" << std::endl;
    pthread_mutex_lock(&(_threadMutexAccess));
    _accessLogBuffer.push(oss.str());
    pthread_mutex_unlock(&(_threadMutexAccess));
    return ;
}


void Log::failure() {
    std::ostringstream oss;
    oss << _indent << ">>>> Failure[" << _errorId << "] <<<<"  << std::endl;
    addToAccesLogBuffer(oss.str());
    closeToAccesLogBuffer();
}

void Log::openToAccesLogBuffer(const std::string &message) {
    addToAccesLogBuffer(setTime() + "\n" + _indent + message + " {");
    addIndent();
}

void Log::addToAccesLogBuffer(const std::string &message) {
    std::ostringstream oss;
    oss << _indent << message << std::endl;
    pthread_mutex_lock(&(_threadMutexAccess));
    _accessLogBuffer.push(oss.str());
    pthread_mutex_unlock(&(_threadMutexAccess));
}

void Log::closeToAccesLogBuffer() {
    removeIndent();
    addToAccesLogBuffer( " }" + setTime());
}

void Log::addToErrorLogBuffer(const std::string &message) {
    _errorId++;
    failure();
    std::ostringstream oss;
    oss << setTime() <<" [" << _errorId << "] " << message << std::endl;
    pthread_mutex_lock(&(_threadMutexError));
    _errorLogBuffer.push(oss.str());
    pthread_mutex_unlock(&(_threadMutexError));
}

void* Log::checkBuffers(void * l) {
    Log* log = static_cast<Log*>(l);
    pthread_mutex_lock(&(log->_threadMutexEndLog));
    while (!log->_endLog) {
        pthread_mutex_unlock(&(log->_threadMutexEndLog));
        pthread_mutex_lock(&(log->_threadMutexAccess));
        if (!log->_accessLogBuffer.empty())
            log->flushAccessBuffers();
        pthread_mutex_unlock(&(log->_threadMutexAccess));
        pthread_mutex_lock(&(log->_threadMutexError));
        if (!log->_errorLogBuffer.empty())
            log->flushErrorBuffers();
        pthread_mutex_unlock(&(log->_threadMutexError));
        sleep(1);//add flag debug
        pthread_mutex_lock(&(log->_threadMutexEndLog));
    }
    pthread_mutex_unlock(&(log->_threadMutexEndLog));
    std::cout << "end" <<std::endl;
    return l;
}

void Log::flushErrorBuffers() {
    std::ofstream file(_pathToErrorLogFile.c_str(), std::ios::app);
    if (!file.is_open())
        std::cerr <<"fail to open file " << _pathToErrorLogFile << std::endl;
    while(!_errorLogBuffer.empty()){
        file << _errorLogBuffer.front();
        _errorLogBuffer.pop();
    }
    file.close();
}

void Log::flushAccessBuffers() {
    std::ofstream file(_pathToAccessLogFile.c_str(), std::ios::app);
    if (!file.is_open())
        throw std::runtime_error("fail to open file " + _pathToAccessLogFile);
    while(!_accessLogBuffer.empty()){
        file << _accessLogBuffer.front();
        _accessLogBuffer.pop();
    }
    file.close();
}


void Log::setEndLog() {
    pthread_mutex_lock(&(_threadMutexEndLog));
    _endLog = true;
    pthread_mutex_unlock(&(_threadMutexEndLog));
}

