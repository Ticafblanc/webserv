//
// Created by Matthis DoQuocBao on 2023-06-05.
//

#ifndef WEBSERVER_LOG_HPP
#define WEBSERVER_LOG_HPP

#include "../../12-Utils/Includes/Utils.hpp"

class Log {

private:
  string _pathToLogFile;
  queStr _logBuffer;
  int _countErrorFlushBuffer;
  string _indent;
  time_t _timestamp;
  pthread_t _threadIdCheck;
  pthread_mutex_t _threadMutexEndLog;
  pthread_mutex_t _threadMutexLog;
  bool _endLog;
  int _errorId;
  int _timeToFlushBuffer;
  int _timeToFlushBufferSave;

  void _setThread();

  void _setMutex();

  void _setLogFile(const string &pathToLogFile);

  static void *_checkBuffers(void *l);

  void _flushBuffers();

  void _setEndLog();

public:
  Log();

  explicit Log(const string &pathToLogFile, int timeToFlush_buffer = 1);

  virtual ~Log();

  Log(const Log &other);

  Log &operator=(Log rhs);

  void setPathToLogFile(const string &pathToLogFile);

  string getPathToLogFile() const;

  void log(const string &message);

  void setTime();

  int getTimeToFlushBuffer() const;

  void setTimeToFlushBuffer(int timeToFlushBuffer);

  const queStr &getLogBuffer() const;
};

#endif
