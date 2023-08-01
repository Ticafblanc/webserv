

#ifndef WEBSERVER_CLI_HPP
#define WEBSERVER_CLI_HPP

#include <string>
#include <iostream>
#include <queue>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <csignal>

//#include <fstream>
//#include <sys/epoll.h>
//#include <ctime>
//#include <queue>
//#include <stdexcept>
//#include <pthread.h>
//#include <unistd.h>


class Cli {


/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    static Cli*                 _this;
    pid_t                       _pid;
    int                         _status;
    volatile sig_atomic_t       _stop;
    bool                        _launch;
    bool                        _checkFile;
    std::queue<std::string>     _argv;
    std::string                 _pathToConfigFile;
/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/
    void            setArg(int argc, char **argv);
    void            checkArg();
    static void     printCliHelp();
    bool            isMainProgram();
    void            checkOption(const std::string &option);
    void            sendSignal(const std::string &command) const;
    void            checkFile(const std::string &pathFile) const;
    static void     initSignal();
    static void     handleReload(int sig);
    static void     handleExit(int sig);
    static void     handleStop(int sig);

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                      Fonction                                    |
*====================================================================================
*/


/**
 * Constructor of Cli class
 *
 * Cli();
 *
 * @param   pathToCliFile
 * @throw   none
 **/
    Cli(int argc, char ** argv);

/**
 * Destructor of Cli class
 *
 * ~Cli();
 *
 * @throw   none
 **/
    virtual ~Cli();

/**
 * Copy constructor of Cli class
 *
 *     Cli(const Cli &);
 *
 * @param   Cli instance
 * @throw   none
 **/
    Cli(const Cli &);

/**
 * Operator overload= of Cli class
 *
 * Cli& operator=(const Cli &);
 *
 * @param   Cli
 * @throw   none
 **/
    Cli &operator=(const Cli &);

/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

    int getStatus() const;

    bool isStop() const;

    bool isLaunch() const;

    pid_t getPid() const;
};


#endif
