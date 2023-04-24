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

data_server::data_server() {
    this->_client_max_body_size = 0;
    this->_max_body_size_def = false;
}

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

void data_server::printAll(void) {
    cout << "server id: " << _serverId << endl;
    for (std::size_t i = 0; i < _server_name.size(); i++) {
        cout << "server names: " << _server_name.at(i) << " ";
    }
    cout << endl;
    for (std::size_t i = 0; i < _host_port.size(); i++) {
        cout << "host: " << _host_port.at(i).first << " port: " << _host_port.at(i).second << endl;
    }
    for (std::size_t i = 0; i < _error_page.size(); i++) {
        for (std::size_t k = 0; k < _error_page.at(i).first.size(); k++) {
            cout << "error codes: " << _error_page.at(i).first.at(k) << " ";
        }
        cout << endl << "path: " << _error_page.at(i).second << endl;
    }
    for (std::size_t i = 0; i < _routes.size(); i++) {
        _routes.at(i).printAll();
    }
    cout << "root: " << _root << endl;
    cout << "max body size: " << _client_max_body_size << endl;
    cout << "address len: " << _addr_len << endl; 
}

data_server::data_server(const data_server& other) {
    *this = other;
}


data_server& data_server::operator=(const data_server& rhs) {
    this->_server_name = rhs._server_name;
    this->_host_port = rhs._host_port;
    this->_error_page = rhs._error_page;
    this->_routes = rhs._routes;
    this->_serverId = rhs._serverId;
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

const vector<string>& data_server::getServerName(void) const throw() {
    return _server_name;
}

void data_server::setServerName(const vector<string>& serverName) throw() {
    _server_name = serverName;
}

const std::size_t& data_server::getIdServer() const throw() {
    return _serverId;
}

void data_server::setIdServer(std::size_t id) throw() {
    _serverId = id;
}

const vector<std::pair<string, int> >& data_server::getHostPort(void) const throw() {
    return _host_port;
}

void data_server::setHostPort(const vector<std::pair<string, int> >& hostPair) throw() {
    _host_port = hostPair;
}

const int& data_server::getType() const throw() {
    return SOCK_STREAM; //this will have to be changed
}

void data_server::setType(int type) throw() {
    this->_server_fd = type; //will need to be changed
}

const vector<Route>& data_server::getRoutes(void) const throw() {
    return _routes;
}

void data_server::setRoutes(const vector<Route>& routes) throw() {
    _routes = routes;
}

const int& data_server::getServerFd(void) const throw() {
    return _server_fd;
}

void data_server::setServerFd(int fd) throw() {
    _server_fd = fd;
}

// void setRoot(const string& root);
// string getRoot(void);

const string& data_server::getRoot(void) const throw() {
    return _root;
}

void data_server::setRoot(const string& root) {
    _root = root;
}

void data_server::setMaxBodySize(int maxBodySize) throw() {
    this->_client_max_body_size = maxBodySize;
}

int data_server::getMaxBodySize(void) const throw() {
    return this->_client_max_body_size;
}

    // void setBodySizeStatus(bool status) throw();
    // bool getBodySizeStatus(void) const throw();

void data_server::setBodySizeStatus(bool status) throw() {
    this->_max_body_size_def = status;
}

bool data_server::getBodySizeStatus(void) const throw() {
    return this->_max_body_size_def;
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
