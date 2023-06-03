//
// Created by Matthis DoQuocBao on 2023-06-02.
//

#pragma once

#ifndef WEBSERVER_BASEEPOLL_HPP
#define WEBSERVER_BASEEPOLL_HPP

#include "webserv.hpp"

class baseEpoll {

/*>*******************************private section**********************************/

protected:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    int                                     _epollInstanceFd;
    int                                     _maxEvents;
    epoll_event                             *_events;
    int                                     _numberTriggeredEvents;

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
 * Constructor of baseEpoll class
 *
 * baseEpoll();
 *
 * @param   void
 * @throw   none
 **/
    baseEpoll();

/**
 * Constructor of baseEpoll class
 *
 * baseEpoll(const vector<baseEpoll> & socket);
 *
 * @param   void
 * @throw   none
 **/
    baseEpoll(std::vector<serverSocket> & sock, int maxEvents);

/**
 * Copy constructor of baseEpoll class
 *
 * baseEpoll(baseEpoll &);
 *
 * @param   other instance to build the baseEpoll
 * @throw   none
 **/
    baseEpoll(const baseEpoll & other);

/**
 * Operator overload= of baseEpoll class
 *
 * operator=(const baseEpoll&);
 *
 * @param   rhs instance const to copy the baseEpoll
 * @throw   none
 **/
    baseEpoll& operator=(const baseEpoll & rhs);

/**
 * Destructor of baseEpoll class
 *
 * baseEpoll();
 **/
    virtual ~baseEpoll();

/*
*====================================================================================
*|                                  Class Exception                                 |
*====================================================================================
*/


/**
 * Class exception of baseEpoll class
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
         * @param   epoll is a baseEpoll reference to set the private _epoll
         *          to manage the close of baseEpoll class
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
         *          at the construction defaut constructor "baseEpoll error"
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
 * create an instance of baseEpoll in _epollInstance and
 * return a file descriptor to new instance of baseEpoll
 *
 * int createEpoll();
 *
 * @returns -1 if fail or int file descriptor
 * @param   void
 * @throw   epollException
 * */
    void createEpollInstance(int nbr);

/**
 * set Event instance with baseEpoll to add remove or modify
 *
 * void setEpollCtl(int  option, AbaseSocket & sock) const;
 *
 * @returns void
 * @param   option is an int action to do:
 *          EPOLL_CTL_ADD to add a new descriptor to be monitored
 *          EPOLL_CTL_MOD to modify the monitoring of an already monitored descriptor
 *          EPOLL_CTL_DEL to delete a monitored descriptor.
 * @param   sock instance of AbaseSocket
 * @throw   epollException
 * */
    void setEpollCtl(int  option, AbaseSocket & sock) const;

/**
 * wait un event in request connect or new event in AbaseSocket already open
 *
 * int setEpollWait(int epollInstance, epoll_event * serverEvents, int maxEvents, int timeOut);
 *
 * @returns void
 * @param   serverEvents table of baseEpoll event to store value
 * @param   maxEvents is the maximum number of events to be returned
 * @param   timeOut time to wait event -1 until first event or >0
 * */
    virtual bool EpollWait(int  timeOut);
    bool EpollWait();

/**
 *  get epoll_event instance
 *
 * epoll_event *getEvents() const;
 *
 * @returns epoll_event *
 * @param   void
 * @throw   none
 * */
    epoll_event *getEvents() const;

/**
 *  get number of triggred events
 *
 * int getNumberTriggeredEvents() const;
 *
 * @returns int of number of triggered events
 * @param   void
 * @throw   none
 * */
    int getNumberTriggeredEvents() const;

};


#endif //WEBSERVER_EPOLL_HPP
