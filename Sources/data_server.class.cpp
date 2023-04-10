/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_server.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */
#include "../Include/data_server.class.hpp"


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

data_server::data_server() {}

data_server::~data_server() {
//    if(!fd_isopen() || !socket_isopen())
//        throw data_server::data_exception();
//    close(getServerFd());
}

// data_server::data_server(const data_server& other) {
//     memcpy(getAddress().sin_zero, other.address.sin_zero, sizeof address.sin_zero);
// }

// data_server& data_server::operator=(const data_server& rhs) {
//     memcpy(this->address.sin_zero, rhs.address.sin_zero, sizeof address.sin_zero);
//     return *this;
// }

data_server::data_server(const data_server& other) {
    *this = other;
}


data_server& data_server::operator=(const data_server& rhs) {
    this->_server_name = rhs._server_name;
    this->_host_port = rhs._host_port;
    this->_default_error = rhs._default_error;
    this->_routes = rhs._routes;
    this->serverId = rhs.serverId;
    this->_address = rhs._address;
    this->_addr_len = rhs._addr_len;
    this->_server_fd = rhs._server_fd;

    return *this;
}

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

const char *  data_server::data_exception::what() const throw(){
    return ("fd error");
}

const char *  data_server::arg_exception::what() const throw(){
    return ("argument invalid");
}

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

vector<string>& data_server::getServerName(void) {
    return _server_name;
}

void data_server::setServerName(const vector<string>& serverName) {
    _server_name = serverName;
}

int& data_server::getIdServer() {
    return serverId;
}

void data_server::setIdServer(int id) {
    serverId = id;
}

vector<std::pair<string, int> >& data_server::getHostPort(void) {
    return _host_port;
}

void data_server::setHostPort(const vector<std::pair<string, int> >& hostPair) {
    _host_port = hostPair;
}

int& data_server::getType() {
    return serverId; //this will have to be changed
}

void data_server::setType(int type) {
    this->_server_fd = type; //will need to be changed
}

vector<Route>& data_server::getRoutes(void) {
    return _routes;
}

void data_server::setRoutes(const vector<Route>& routes) {
    _routes = routes;
}

int& data_server::getServerFd(void) {
    return _server_fd;
}

void data_server::setServerFd(int fd) {
    _server_fd = fd;
}

// int& data_server::getProtocol(){
//     return getIData()[protocol];
// }

// void data_server::setProtocol(int  pro){
//     getIData()[protocol] = pro;
// }

// int&  data_server::getBacklog(){
//     return getIData()[backlog];
// }

// void data_server::setBacklog(int  log){
//     getIData()[backlog] = log;
// }

// int& data_server::getNewSocket(){
//     return getIData()[new_socket];
// }

// void data_server::setNewSocket(int  sok){
//     getIData()[new_socket] = sok;
// }

sockaddr_in& data_server::getAddress(){
    return this->_address;
}

void data_server::setAddress(int dom, const std::string& ip_addr, int por){
    if (dom != AF_INET)
        throw data_server::arg_exception();
    getAddress().sin_family = dom;
    getAddress().sin_addr.s_addr = inet_addr(ip_addr.c_str());//check format ip address during the parsing no ERROR
    getAddress().sin_port = htons(por);//no error
    memset(getAddress().sin_zero, '\0', sizeof getAddress().sin_zero);//a delete
    setAddrlen(sizeof(getAddress()));
}

void data_server::setAddress(int dom, int por){
    if (dom != AF_INET)
        throw data_server::arg_exception();
    getAddress().sin_family = dom;
    getAddress().sin_addr.s_addr = INADDR_ANY;//check format ip address during the parsing no ERROR
    getAddress().sin_port = htons(por);//no error
    memset(getAddress().sin_zero, '\0', sizeof getAddress().sin_zero);//a delete
    getAddrlen() = sizeof(getAddress());
}

// void data_server::setAddress(){
//     getAddress().sin_family = getDomain();
//     getAddress().sin_addr.s_addr = inet_addr(getIpAddress().c_str());//check format ip address during the parsing no ERROR
//     getAddress().sin_port = htons(getIData()[port]);//no error
//     memset(getAddress().sin_zero, '\0', sizeof getAddress().sin_zero);//a delete
//     setAddrlen(sizeof(getAddress()));
// }

std::size_t& data_server::getAddrlen() {
    return this->_addr_len;
}

void data_server::setAddrlen(const std::size_t & s){
    this->_addr_len = s;
}

// int& data_server::getLevel(){
//     return getIData()[level];
// }

// void data_server::setLevel(int lev){
//     getIData()[level] = lev;
// }

// int& data_server::getOptionName(){
//     return getIData()[optionname];
// }

// void data_server::setOptionName(int opt){
//     getIData()[optionname] = opt;
// }

// int& data_server::getOptionVal(){
//     return getIData()[optionval];
// }

// void data_server::setOptionVal(int opt){
//     getIData()[optionval] = opt;
// }

// pid_t& data_server::getPid() {
//     return this->pid;
// }

// void data_server::setPid(pid_t & p){
//     this->pid = p;
// }

void data_server::close_server_fd(){
//    if(!fd_isopen() || !socket_isopen())
//        throw data_server::data_exception();
//    close(getServerFd());
}
/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/

int data_server::fd_isopen() {
    int ret = fcntl(getServerFd(), F_GETFL);
    if (ret == -1) {
        throw data_server::data_exception();
    }
    return 1;
}

int data_server::socket_isopen() {
    int error;
    socklen_t len = sizeof(error);
    int ret = getsockopt(getServerFd(), SOL_SOCKET, SO_ERROR, &error, &len);
    if (ret != 0 || error > 0) {
        throw data_server::data_exception();
    }
    return 1;
}
