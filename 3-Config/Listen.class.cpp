//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include "Listen.class.hpp"

Listen::Listen(Config& config, ConfigServer& configServer)
: _config(config), _configServer(configServer){}

Listen::~Listen() {}
//todo manage close fd at end of programme
/*check if file descriptor is open
 * if process fail throw serverSocket::socket_exception();
 */
//    int fd_isopen();

/*check if AbaseSocket  is open
 * if process fail throw serverSocket::socket_exception();
 */
//    int socket_isopen();

Listen::Listen(const Listen& other)
        : _config(other._config), _configServer(other._configServer) {}

Listen &Listen::operator=(const Listen & rhs) {
    this->_config = rhs._config;
    return *this;
}

std::string Listen::parseListenData() {
    //@todo check port and ip
    return std::string("");
}

std::string Listen::parseListenData(std::string in) {
    std::stringstream input(in);
    std::string ip;
    std::string portStr;
    int         portInt;
    std::getline(input >> std::ws, ip, ':');
    input >> portStr >> std::ws;
    portInt = std::atoi(portStr.c_str());
    _configServer.listen[ip] = portInt;
    return std::string();
}



