//
// Created by Matthis DoQuocBao on 2023-06-02.
//

#pragma once

#ifndef WEBSERVER_EPOLL_HPP
#define WEBSERVER_EPOLL_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/1-Config/Includes/Config.hpp>

class Epoll :public epoll_event {

/*>*******************************private section**********************************/

protected:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    Config&                                         _config;
    int                                             _epollInstanceFd;
    epoll_event*                                    _events;
    int                                             _numberTriggeredEvents;

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
 * Constructor of 2-Engin class
 *
 * 2-Engin(const vector<2-Engin> & socket);
 *
 * @param   void
 * @throw   none
 **/
    explicit Epoll(Config& config);

/**
 * Copy constructor of 2-Engin class
 *
 * 2-Engin(2-Engin &);
 *
 * @param   other instance to build the 2-Engin
 * @throw   none
 **/
    Epoll(const Epoll & other);

/**
 * Operator overload= of 2-Engin class
 *
 * operator=(const 2-Engin&);
 *
 * @param   rhs instance const to copy the 2-Engin
 * @throw   none
 **/
    Epoll& operator=(const Epoll & rhs);

/**
 * Destructor of 2-Engin class
 *
 * 2-Engin();
 **/
    virtual ~Epoll();

/*
*====================================================================================
*|                                  Class Exception                                 |
*====================================================================================
*/


/**
 * Class exception of 2-Engin class
 *
 * class epollException;
 *
 * @inherit std::exception
 **/
    class epollException: public std::exception
    {
    public:

        /**
         * Constructor of epollException class
         *
         * epollException(const char * message, int statusCode);
         *
         * @param   epoll is a 2-Engin reference to set the private _epoll
         *          to manage the close of 2-Engin class
         *          message to store const char*
         * @throw   none
         **/
        epollException(const char * message);

        /**
         * Copy constructor of epollException class
         *
         * epollException(epollException &);
         *
         * @param   epollException instance to build the epollException
         *          epoll_epoll in an int to close
         * @throw   none
         **/
        epollException(const epollException &);

        /**
         * Operator overload= of epollException class
         *
         * operator=(const epollException&);
         *
         * @param   epollException instance const to copy the epollException
         * @throw   none
         **/
        epollException& operator=(const epollException &);

        /**
        * Destructor of epollException class
        *
        * virtual ~epollException() throw();
        *
        * @throw   none
        **/
        virtual ~epollException() throw();

        /**
         * Public methode of epollException
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "2-Engin error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

    private:
        std::string     _message;
    };

/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

/**
 * Private methode of socket class
 *
 * set epollEvent instance with 7-Socket and type of event to follow
 * before to add a epollEvent to 2-Engin
 *
 * int setEpollEvent(int & socket_socket, struct epoll_event & event, int & events);
 *
 * @returns void
 * @param   flag is int to add to the event
 *          EPOLLIN the event occurs when data can be read from the file descriptor
 *          EPOLLOUT the event occurs when data can be written to the file descriptor
 *          EPOLLERR the event occurs when there is an error on the file descriptor
 *          EPOLLRDHUP the event occurs when the connection is closed by the remote peer
 *          EPOLLHUP the event occurs when the file descriptor is closed by the local peer
 *          EPOLLET edge triggering mode
 *          EPOLLONESHOT single trigger mode
 *
 * @throws  socket::socketException
 * */
    void setEpollEvent(int socket, int flag);

/**
 * create an instance of 2-Engin in _epollInstance and
 * return a file descriptor to new instance of 2-Engin
 *
 * int createEpoll();
 *
 * @returns -1 if fail or int file descriptor
 * @param   void
 * @throw   epollException
 * */
    void createEpollInstance(int nbr);

/**
 * set Event instance with 2-Engin to add remove or modify
 *
 * void setEpollCtl(int  option, 7-Socket & sock) const;
 *
 * @returns void
 * @param   option is an int action to do:
 *          EPOLL_CTL_ADD to add a new descriptor to be monitored
 *          EPOLL_CTL_MOD to modify the monitoring of an already monitored descriptor
 *          EPOLL_CTL_DEL to delete a monitored descriptor.
 * @param   sock instance of 7-Socket
 * @throw   epollException
 * */
    void setEpollCtl(int  option);

/**
 * wait un event in request connect or new event in 7-Socket already open
 *
 * int setEpollWait(int epollInstance, epoll_event * serverEvents, int maxEvents, int timeOut);
 *
 * @returns void
 * @param   serverEvents table of 2-Engin event to store value
 * @param   maxEvents is the maximum number of events to be returned
 * @param   timeOut time to wait event -1 until first event or >0
 * */
    bool EpollWait(int  timeOut);
    bool EpollWait();


/**
 * add socket to Epoll
 *
 * void addSocket(std::string & ipAddr, int & port);
 *
 * @returns void
 * @param   int socket
 * @throw   none
 * */
    void addSocket(int socket, int events);

    /**
 * add socket to Epoll
 *
 *  void modSocket(int socket, int events);
 *
 * @returns void
 * @param   int socket
 * @throw   none
 * */
    void modSocket(int socket, int events);

/**
 * add socket to Epoll
 *
 * void removeSocket(int socket);
 *
 * @returns void
 * @param   int socket
 * @throw   none
 * */
    void removeSocket(int socket);

/**
 * add socket to Epoll
 *
 * void launchEpoll();
 *
 * @returns void
 * @param   int socket
 * @throw   none
 * */
    void launchEpoll();

/**
 * add socket to Epoll
 *
 * void manageEvent();
 *
 * @returns void
 * @param   int socket
 * @throw   none
 * */
    void manageEvent();

/**
 * add socket to Epoll
 *
 *  void addConnexion();
 *
 * @returns void
 * @param   int socket
 * @throw   none
 * */
    void addConnexion(int numberTrigged);

/**
 * add socket to Epoll
 *
 *  void removeConnexion(Socket& client, int numberTrigged);
 *
 * @returns void
 * @param   int socket
 * @throw   none
 * */
    void removeConnexionClient(Socket& client);
    void removeConnexionServer(Socket& server);

/**
 * add socket to Epoll
 *
 *  void selectEvent(Socket& client, int numberTrigged);
 *
 * @returns void
 * @param   int socket
 * @throw   none
 * */
    void selectEvent(Socket& client, int numberTrigged);
};


#endif //WEBSERVER_EPOLL_HPP
