//
// Created by Matthis DoQuocBao on 2023-06-05.
//
#pragma once

#ifndef WEBSERVER_LOG_HPP
#define WEBSERVER_LOG_HPP

#include <Source_Code/0-webserv_launch_main_project/Headers_external_library.hpp>
#include <ostream>


class Log {


/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    std::string     _pathToLogFile;
    std::string     _indent;
public:
    void setIndent(const std::string &indent);

private:
    std::string     _message;
    std::time_t     _timestamp;
    std::string     _timestampStr;
    bool            _logEnable;
public:
    void setLogEnable(bool logEnable);

public:


/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/


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
 * @param   void
 * @throw   none
 **/
    Log();

/**
 * Constructor of Log class
 *
 * Log(std::string & pathToLogFile);
 *
 * @param   pathToLogFile
 * @throw   none
 **/
    explicit Log(const std::string &pathToLogFile);

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
*|                                  Class Exception                                 |
*====================================================================================
*/


/**
 * Class exception of Log class
 *
 * class LogException;
 *
 * @inherit std::exception
 **/
class LogException : public std::exception {
    public:

        /**
         * Constructor of LogException class
         *
         * LogException(const char * message, int statusCode);
         *
         * @param   Log is a LogSocket reference to set the private _Log
         *          to manage the close of LogSocket class
         *          message to store const char*
         * @throw   none
         **/
        LogException(const char *message);

        /**
         * Copy constructor of LogException class
         *
         * LogException(LogException &);
         *
         * @param   LogException instance to build the LogException
         *          Log_socket in an int to close
         * @throw   none
         **/
        LogException(const LogException &);

        /**
         * Operator overload= of LogException class
         *
         * operator=(const LogException&);
         *
         * @param   LogException instance const to copy the LogException
         * @throw   none
         **/
        LogException &operator=(const LogException &);

        /**
        * Destructor of LogException class
        *
        * virtual ~LogException() throw();
        *
        * @throw   none
        **/
        virtual ~LogException() throw();

        /**
         * Public methode of LogException
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "7-Socket error"
         * @param   void
         * @throw   none
         **/
        virtual const char *what() const throw();

    private:
        std::string _message;
    };



/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/
/**
 * Public methode of Log class
 *
 * void writeTimeLogFile(const std::string& message);
 *
 * @returns void
 * @param message
 * @throw LogException
 */
    void setLog(const std::string &pathToLogFile);

/**
 * Public methode of Log class
 *
 * void writeTimeLogFile(const std::string& message);
 *
 * @returns void
 * @param message
 * @throw LogException
 */
//    void writeTimeLogFile(const std::string& message);
    void writeMessageLogFile(const std::string &message);


/**
 * Public methode of Log class
 *
 * void printLogFile();
 *
 * @returns void
 * @param void
 * @throw LogException
 */
    void printLogFile();
    void addIndent();
    void removeIndent();

    std::string convertEventsTostring(int events);
/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/


    void success();

    void failure();

    friend std::ostream &operator<<(std::ostream &os, const Log &log);

    void setTime();

    void setMessage(const std::string &message);
};


#endif //WEBSERVER_LOG_HPP
