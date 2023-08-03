//
// Created by Matthis DoQuocBao on 2023-06-05.
//
#pragma once

#ifndef WEBSERVER_LOG_HPP
#define WEBSERVER_LOG_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <queue>
#include <stdexcept>
#include <pthread.h>
#include <unistd.h>
#ifdef LINUX
    #include <sys/epoll.h>
#endif
#ifdef MAC
    #include <sys/types.h>
    #include <sys/event.h>
    #include <sys/time.h>
#endif
#ifdef DOCKER
    #define _PATHTOPIDLOGFILE_      "/webserv/Source_Code/5-Log/.Log_files/pid.log"
    #define _PATHTOCONFIGLOGFILE_   "/webserv/Source_Code/5-Log/.Log_files/config.log"
    #define _PATHTOACCESSLOGFILE_   "/webserv/Source_Code/5-Log/.Log_files/access.log"
    #define _PATHTOERRORLOGFILE_    "/webserv/Source_Code/5-Log/.Log_files/error.log"
#else
    #define _PATHTOPIDLOGFILE_      "../.webserv/log/pid.log"
    #define _PATHTOCONFIGLOGFILE_   "../.webserv/log/config.log"
    #define _PATHTOACCESSLOGFILE_   "../.webserv/log/access.log"
    #define _PATHTOERRORLOGFILE_    "../.webserv/log/error.log"
#endif

class Log {


/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    std::string                 _pathToPidLogFile;
    std::string                 _pathToConfigLogFile;
    std::string                 _pathToAccessLogFile;
    std::string                 _pathToErrorLogFile;
    std::queue<std::string>     _accessLogBuffer;
    std::queue<std::string>     _errorLogBuffer;
    std::string                 _indent;
    std::time_t                 _timestamp;
    pthread_t                   _threadIdCheck;
    pthread_mutex_t             _threadMutexEndLog;
    pthread_mutex_t             _threadMutexAccess;
    pthread_mutex_t             _threadMutexError;
    bool                        _endLog;
    int                         _errorId;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

    bool setLog(const std::string &pathToLogFile);
    void addIndent();
    void removeIndent();
    void failure();
    std::string setTime();
    static void* checkBuffers(void * l);
    void flushErrorBuffers();
    void flushAccessBuffers();

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                      Fonction                                    |
*====================================================================================
*/


/**
 * Constructor of Log class
 *
 * Log();
 *
 * @param   pathToLogFile
 * @throw   none
 **/
    Log();

/**
 * Destructor of Log class
 *
 * ~Log();
 *
 * @throw   none
 **/
    virtual ~Log();

/**
 * Copy constructor of Log class
 *
 *     Log(const Log &);
 *
 * @param   Log instance
 * @throw   none
 **/
    Log(const Log &);

/**
 * Operator overload= of Log class
 *
 * Log& operator=(const Log &);
 *
 * @param   Log
 * @throw   none
 **/
    Log &operator=(const Log &);

/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

/**
 * Public methode of Log class
 *
 * set a new path for log file
 *
 * void    setPathToLogFile(const std::string &pathToLogFile);
 *
 * @returns void
 * @param pathToLogFile newPath to log
 * @throw std::runtime_error
 */
    void    setPathToPidLogFile(const std::string &pathToLogFile);
    void    setPathToConfigLogFile(const std::string &pathToLogFile);
    void    setPathToAccessLogFile(const std::string &pathToLogFile);
    void    setPathToErrorLogFile(const std::string &pathToLogFile);

/**
 * Public methode of Log class
 *
 * add message to buffer
 *
 * void    openToAccesLogBuffer(const std::string &message);
 * void    openToErrorLog(const std::string &message);
 * void    addToAccesLogBuffer(const std::string &message);
 * void    addToErrorLog(const std::string &message);
 * void    closeToAccesLogBuffer(const std::string &message);
 * void    closeToErrorLog(const std::string &message);
 *
 * @returns void
 * @param message message to add buffer
 * @throw std::runtime_error
 */
    void    openToAccesLogBuffer(const std::string &message);
    void    addToAccesLogBuffer(const std::string &message);
    void    addClientToAccess(const std::string &ipAddress, const int port, const int clientSocket, const int serverSocket);
    void    addEventToAccess(const int id, const int fd, const int events);
    void    closeToAccesLogBuffer();
    void    addToErrorLogBuffer(const std::string &message);

/**
 * Public methode of Log class
 *
 * add message to buffer
 *
 * void setEndLog();
 *
 * @returns void
 * @param void
 */
    void setEndLog();

};


#endif
