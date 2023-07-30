

#ifndef WEBSERVER_CLI_HPP
#define WEBSERVER_CLI_HPP

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>

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

    bool                        _option;
    bool                        _stop;
    bool                        _launch;
    bool                        _checkFile;
    std::vector<std::string>    _argv;
/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

    static void printCliHelp();

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

    bool isEnd() const;

    bool isOption() const;

    bool isCheckFile() const;

    void checkOption();

    void checkArg();
};


#endif
