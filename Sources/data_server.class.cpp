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
#include "../Include/colors.hpp"


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

data_server::data_server(): _iData(9), _address(), _addr_len(), _client_max_body_size(0), _max_body_size_def(false) {
    _iData[domain] = AF_INET;
    _iData[type] = SOCK_STREAM;
    _iData[protocol] = 0;
    _iData[backlog] = 10;
    _iData[level] = SOL_SOCKET;
    _iData[optionname] = SO_REUSEADDR;
    _iData[optionval] = 1;
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

void data_server::printAll() {
    cout << GRN << "server id: " << _iData[id_server] << reset << "\n" << endl;
    cout << MAG;
    for (std::size_t i = 0; i < _server_name.size(); i++) {
        cout << "server names: " << _server_name.at(i) << " ";
    }
    cout << endl;
    for (std::size_t i = 0; i < _host_port.size(); i++) {
        cout << "host: " << _host_port.at(i).first << " port: " << _host_port.at(i).second << endl;
    }
    for (std::size_t i = 0; i < _error_page.size(); i++) {
        cout << "error_codes: ";
        for (std::size_t k = 0; k < _error_page.at(i).first.size(); k++) {
            cout << _error_page.at(i).first.at(k) << " ";
        }
        cout << " path: " << _error_page.at(i).second << endl;
    }
    cout << MAG;
    cout << "root: " << this->getRoot() << endl;
    cout << "max body size: " << _client_max_body_size << endl;
    cout << "address len: " << _addr_len << endl << endl;
    cout << reset;
    for (std::size_t i = 0; i < _routes.size(); i++) {
        cout << BLU;
        _routes.at(i).printAll();
        cout << reset;
    }
}

data_server::data_server(const data_server& other) : _client_max_body_size(), _max_body_size_def(), _address(), _addr_len() {
    *this = other;
}


data_server& data_server::operator=(const data_server& rhs) {
    this->_server_name = rhs._server_name;
    this->_host_port = rhs._host_port;
    this->_error_page = rhs._error_page;
    this->_routes = rhs._routes;
    this->_iData = rhs._iData;
    this->_address = rhs._address;
    this->_addr_len = rhs._addr_len;
    this->_server_fd = rhs._server_fd;
    this->_root = rhs._root;
    this->_client_max_body_size = rhs._client_max_body_size;
    this->_max_body_size_def = rhs._max_body_size_def;
    this->_ipAddress = rhs._ipAddress;

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

const char* data_server::DuplicateDirective::what() const throw() {
    return "Duplicate directive";
}

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

std::vector<int>& data_server::getIData() {
    return _iData;
}

const vector<string>& data_server::getServerName() const throw() {
    return _server_name;
}

void data_server::setServerName(const vector<string>& serverName) throw() {
    _server_name = serverName;
}

const vector<std::pair<vector<int>, string> >& data_server::getErrorPages() const throw() {
    return _error_page;
}

void data_server::setErrorPages(const vector<std::pair<vector<int>, string> >& errorPages) throw() {
    this->_error_page = errorPages;
}

const vector<std::pair<string, int> >& data_server::getHostPort() const throw() {
    return _host_port;
}

void data_server::setHostPort(const vector<std::pair<string, int> >& hostPair) throw() {
    _host_port = hostPair;
}

const vector<Route>& data_server::getRoutes() const throw() {
    return _routes;
}

void data_server::setRoutes(const vector<Route>& routes) throw() {
    _routes = routes;
}

const int& data_server::getServerFd() const throw() { // Will need to be changed
    return _server_fd[0];
}

void data_server::setServerFd(int fd) throw() { // Will need to be changed
    _server_fd.push_back(fd);
}

const string& data_server::getRoot() const throw() {
    return _root;
}

void data_server::setRoot(const string& root) {
    if (!_root.empty()) {
        throw DuplicateDirective();
    }
    this->_root = root;
}

void data_server::setMaxBodySize(int maxBodySize) throw() {
    this->_client_max_body_size = maxBodySize;
}

std::size_t data_server::getMaxBodySize() const throw() {
    return this->_client_max_body_size;
}

void data_server::setBodySizeStatus(bool status) throw() {
    this->_max_body_size_def = status;
}

bool data_server::getBodySizeStatus() const throw() {
    return this->_max_body_size_def;
}

const int& data_server::getPort() const throw() { //Will have to be changed
    return _host_port.at(0).second;
}

void data_server::setPort(int port) throw() { //will have to be changed
    _host_port.at(0).second = port;
}

/************* iData methods ***************/

const int& data_server::getIdServer() throw() {
    return getIData()[id_server];
}

void data_server::setIdServer(int id) throw() {
    _iData[id_server] = id;
}

const int& data_server::getDomain() throw() {
    return getIData()[domain];
}

void data_server::setDomain(int dom) throw() {
    _iData[domain] = dom;
}

const int& data_server::getType() throw() {
    return getIData()[type];
}

void data_server::setType(int type) throw() {
    this->_iData[this->type] = type;
}

const int& data_server::getProtocol() throw() {
    return getIData()[protocol];
}

void data_server::setProtocol(int  pro) throw() {
    getIData()[protocol] = pro;
}

const int&  data_server::getBacklog() throw() {
    return getIData()[backlog];
}

void data_server::setBacklog(int  log) throw() {
    _iData[backlog] = log;
}

const int& data_server::getNewSocket() throw() {
    return getIData()[new_socket];
}

void data_server::setNewSocket(int  sok) throw() {
    _iData[new_socket] = sok;
}

const int& data_server::getLevel() throw() {
    return getIData()[level];
}

void data_server::setLevel(int lvl) throw() {
    this->_iData[level] = lvl;
}

const int& data_server::getOptionName() throw() {
    return getIData()[optionname];
}

void data_server::setOptionName(int opt) throw() {
    _iData[optionname] = opt;
}

const int& data_server::getOptionVal() throw() {
    return getIData()[optionval];
}

void data_server::setOptionVal(int val) throw() {
    _iData[optionval] = val;
}

sockaddr_in& data_server::getAddress(){
    return this->_address;
}

std::string& data_server::getIpAddress(){
    return _ipAddress;
}

void data_server::setIpAddress(std::string & ip){
    _ipAddress = ip;
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

void data_server::setAddress(){
    getAddress().sin_family = getDomain();
    getAddress().sin_addr.s_addr = inet_addr(getIpAddress().c_str());//check format ip address during the parsing no ERROR
    getAddress().sin_port = htons(getPort());//no error
    memset(getAddress().sin_zero, '\0', sizeof getAddress().sin_zero);//a delete
    setAddrlen(sizeof(getAddress()));
}

std::size_t& data_server::getAddrlen() {
    return this->_addr_len;
}

void data_server::setAddrlen(const std::size_t & s){
    this->_addr_len = s;
}


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
