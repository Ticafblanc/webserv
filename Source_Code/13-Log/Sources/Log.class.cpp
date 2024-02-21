//
// Created by Matthis DoQuocBao on 2023-06-05.
//

#include "../Includes/Log.class.hpp"

Log::Log()
    : _pathToLogFile(), _logBuffer(), _countErrorFlushBuffer(), _indent("\t"),
      _timestamp(), _threadIdCheck(), _threadMutexEndLog(), _threadMutexLog(),
      _endLog(false), _errorId(), _timeToFlushBuffer(1),
      _timeToFlushBufferSave(_timeToFlushBuffer) {
  std::ostringstream oss;
  oss << "logfile_" << getppid() << ".log";
  _pathToLogFile = oss.str();
  _setLogFile(_pathToLogFile);
  _setMutex();
  _setThread();
}

Log::Log(const string &pathToLogFile, int timeToFlush_buffer)
    : _pathToLogFile(pathToLogFile), _logBuffer(), _countErrorFlushBuffer(),
      _indent("\t"), _timestamp(), _threadIdCheck(), _threadMutexEndLog(),
      _threadMutexLog(), _endLog(false), _errorId(),
      _timeToFlushBuffer(timeToFlush_buffer),
      _timeToFlushBufferSave(_timeToFlushBuffer) {
  _setLogFile(_pathToLogFile);
  _setMutex();
  _setThread();
}

Log::~Log() {
  try {
    _setEndLog();
  } catch (const std::exception &e) {
    cerr << e.what() << endl;
  }
  if (_threadIdCheck) {
    pthread_join(_threadIdCheck, NULL);
  }
}

Log::Log(const Log &other)
    : _pathToLogFile(other._pathToLogFile), _logBuffer(other._logBuffer),
      _countErrorFlushBuffer(other._countErrorFlushBuffer),
      _indent(other._indent), _timestamp(other._timestamp),
      _endLog(other._endLog), _errorId(other._errorId),
      _timeToFlushBuffer(other._timeToFlushBuffer),
      _timeToFlushBufferSave(_timeToFlushBuffer) {
  _setMutex();
  _setThread();
}

Log &Log::operator=(Log rhs) {
  if (this != &rhs) {
    _setEndLog();
    swap(_pathToLogFile, rhs._pathToLogFile);
    swap(_logBuffer, rhs._logBuffer);
    swap(_countErrorFlushBuffer, rhs._countErrorFlushBuffer);
    swap(_indent, rhs._indent);
    swap(_timestamp, rhs._timestamp);
    swap(_endLog, rhs._endLog);
    swap(_errorId, rhs._errorId);
    swap(_timeToFlushBuffer, rhs._timeToFlushBuffer);
    swap(_timeToFlushBufferSave, rhs._timeToFlushBufferSave);
    _setMutex();
    _setThread();
  }
  return *this;
}

void Log::setPathToLogFile(const string &pathToLogFile) {
  _pathToLogFile = pathToLogFile;
  _setLogFile(_pathToLogFile);
}

std::string Log::getPathToLogFile() const { return _pathToLogFile; }

void Log::_setThread() {
  try {
    if (pthread_create(&_threadIdCheck, NULL, &Log::_checkBuffers, this)) {
      throw std::runtime_error(
          "Failed to create thread in setMutexAndThread()");
    }
  } catch (const std::exception &e) {
    pthread_mutex_destroy(&_threadMutexLog);
    pthread_mutex_destroy(&_threadMutexEndLog);
    cerr << e.what() << endl;
  }
}

void Log::_setMutex() {
  if (pthread_mutex_init(&_threadMutexLog, NULL) ||
      pthread_mutex_init(&_threadMutexEndLog, NULL))
    throw runtime_error("fail to init mutex");
}

void Log::_setLogFile(const std::string &pathToLogFile) {
  ofstream file(pathToLogFile.c_str(), std::ios::trunc);
  if (!file.is_open())
    throw runtime_error("Failed to open file " + _pathToLogFile);
  file.close();
}

void Log::setTime() {
  _timestamp = time(NULL);
  ostringstream oss;
  oss << asctime(localtime(&_timestamp));
  pthread_mutex_lock(&(_threadMutexLog));
  _logBuffer.push(oss.str());
  pthread_mutex_unlock(&(_threadMutexLog));
}

void Log::log(const string &message) {
  if (_countErrorFlushBuffer <= 5) {
    ostringstream oss;
    oss << _indent << message << std::endl;
    pthread_mutex_lock(&(_threadMutexLog));
    _logBuffer.push(oss.str());
    pthread_mutex_unlock(&(_threadMutexLog));
  }
}

void *Log::_checkBuffers(void *l) {
  Log *log = static_cast<Log *>(l);
  pthread_mutex_lock(&(log->_threadMutexEndLog));
  while (!log->_endLog) {
    pthread_mutex_unlock(&(log->_threadMutexEndLog));
    pthread_mutex_lock(&(log->_threadMutexLog));
    if (!log->_logBuffer.empty())
      log->_flushBuffers();
    pthread_mutex_unlock(&(log->_threadMutexLog));
    sleep(log->_timeToFlushBuffer);
    pthread_mutex_lock(&(log->_threadMutexEndLog));
  }
  pthread_mutex_unlock(&(log->_threadMutexEndLog));
  return l;
}

void Log::_flushBuffers() {
  _countErrorFlushBuffer++;
  ofstream file(_pathToLogFile.c_str(), ios::app);
  try {
    if (!file.is_open())
      throw runtime_error("Failed to open file " + _pathToLogFile);
    while (!_logBuffer.empty()) {
      file << _logBuffer.front();
      _logBuffer.pop();
    }
    file.close();
  } catch (const exception &e) {
    cerr << e.what() << endl;
  }
  if (_countErrorFlushBuffer > 5) {
    queStr empty;
    swap(_logBuffer, empty);
    _timeToFlushBuffer *= _countErrorFlushBuffer;
  } else {
    _timeToFlushBuffer = _timeToFlushBufferSave;
    _countErrorFlushBuffer = 0;
  }
}

void Log::_setEndLog() {
  pthread_mutex_lock(&(_threadMutexEndLog));
  _endLog = true;
  pthread_mutex_unlock(&(_threadMutexEndLog));
  pthread_mutex_lock(&(_threadMutexLog));
  if (!_logBuffer.empty())
    _flushBuffers();
  pthread_mutex_unlock(&(_threadMutexLog));
  pthread_join(_threadIdCheck, NULL);
  pthread_mutex_destroy(&_threadMutexLog);
  pthread_mutex_destroy(&_threadMutexEndLog);
}

int Log::getTimeToFlushBuffer() const { return _timeToFlushBuffer; }

void Log::setTimeToFlushBuffer(int timeToFlushBuffer) {
  _timeToFlushBuffer = timeToFlushBuffer;
}

const queStr &Log::getLogBuffer() const { return _logBuffer; }
