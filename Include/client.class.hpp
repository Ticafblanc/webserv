//
// Created by Matthis DoQuocBao on 2023-05-31.
//

#ifndef WEBSERVER_CLIENT_HPP
#define WEBSERVER_CLIENT_HPP

#include <ostream>
#include "../Include/header.hpp"
#include "../Include/config_webserv.class.hpp"
#include "../Include/http_request.class.hpp"

#define FLAG1 0x01 // 0000 0001
#define FLAG2 0x02 // 0000 0010
#define FLAG3 0x04 // 0000 0100
#define FLAG4 0x08 // 0000 1000
#define FLAG5 0x10 // 0001 0000
#define FLAG6 0x20 // 0010 0000
#define FLAG7 0x40 // 0100 0000
#define FLAG8 0x80 // 1000 0000

class client : public epoll_event{

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    char        _stateFlag;
    blocServer& _server;
//    httpRequest _request;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/




/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

    client(char stateFlag, blocServer &server);

    virtual ~client();




/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/



};

struct ClientComparator {
    bool operator()(const client& lhs, const client& rhs) const {
        return lhs.data.fd < lhs.data.fd;
    }
};


#endif //WEBSERVER_CLIENT_HPP
