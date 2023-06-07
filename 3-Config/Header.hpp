//
// Created by Matthis DoQuocBao on 2023-06-07.
//

#ifndef WEBSERVER_HEADER_HPP
#define WEBSERVER_HEADER_HPP

#include "0-Main/Includes/Headers.hpp"

class Header {


/*>*******************************private section**********************************/

private:
/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    std::string                                         _startLine;
    std::map<std::string, std::string (Header::*)()>    _mapTokenListActionMethode;
    std::map<std::string, std::string (Header::*)()>    _mapTokenListActionInformation;
};


#endif //WEBSERVER_HEADER_HPP
