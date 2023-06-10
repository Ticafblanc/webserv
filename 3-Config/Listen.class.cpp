//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include "Listen.class.hpp"

Listen::Listen(Config& config) : _config(config), _ipAddress(), _port() {}

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
        : _config(other._config), _ipAddress(other._ipAddress),
          _port(other._port){}

Listen &Listen::operator=(const Listen & rhs) {
    this->_config = rhs._config;
    this->_ipAddress = rhs._ipAddress;
    this->_port = rhs._port;
    return *this;
}

std::string Listen::parseListenData() {
    //@todo check port and ip
    return std::string("");
}

std::string Listen::parseListenData(std::string in) {
    std::stringstream input(in);
    std::string port;
    std::getline(input >> std::ws, _ipAddress, ':');
    input >> port >> std::ws;
    _port = std::atoi(port.c_str());
    return std::string();
}

std::pair<std::string, int> Listen::getDataListen() {
    return std::make_pair(_ipAddress, _port);
}

