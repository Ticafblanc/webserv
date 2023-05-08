/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:31 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/31 21:54:51 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <Include/server.class.hpp>

bool stat_of_server = true;

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

server::server() : _data(), _event(), _events(), _server_socket(), _client_socket(),
                    _epoll_fd(), _number_triggered_events(), _client_address(), _client_address_len(sizeof(_client_address)) {}

server::server(const data_server & data) : _data(data), _event(), _events(), _server_socket(),
                                            _client_socket(), _epoll_fd(), _number_triggered_events(), _client_address(), _client_address_len(sizeof(_client_address)) {}

server::~server() {}

server::server(const server& other) :   _data(other._data), _event(other._event), _events(), _server_socket(other._server_socket),
                                            _client_socket(), _epoll_fd(other._epoll_fd), _number_triggered_events(), _client_address(), _client_address_len() {
    //@todo change maxevent macro to data server variable
    for (int i = 0; i < MAX_EVENTS; ++i) {
        this->_events[i] = other._events[i];
    }
}

server& server::operator=(const server& rhs){
    this->_data = rhs._data;
    this->_event = rhs._event;
    this->_server_socket = rhs._server_socket;
    this->_client_socket = rhs._client_socket;
    this->_epoll_fd = rhs._epoll_fd;
    this->_number_triggered_events = rhs._number_triggered_events;
    this->_client_address = rhs._client_address;
    this->_client_address_len = rhs._client_address_len;
    //@todo change maxevent macro to data server variable
    for (int i = 0; i < MAX_EVENTS; ++i) {
        _events[i] = rhs._events[i];
    }
    return *this;
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

server::socket_exception::socket_exception() : std::exception(), _message("socket error"){}

server::socket_exception::socket_exception(const char * message) : std::exception(), _message(message) {}

server::socket_exception::~socket_exception() throw() {}

const char * server::socket_exception::what() const throw() { return _message.c_str(); }

server::socket_exception::socket_exception(const socket_exception & other) : std::exception(), _message(other._message) {}

server::socket_exception &server::socket_exception::operator=(const socket_exception &rhs) {
    _message = rhs._message;
    return *this;
}

server::socketopt_exception::socketopt_exception(const int server_socket) :
                        std::exception(), _message("socketopt error"), _server_socket(server_socket) {}

server::socketopt_exception::socketopt_exception(const int server_socket, const char * message) :
                        std::exception(), _message(message), _server_socket(server_socket) {}

server::socketopt_exception::~socketopt_exception() throw() {}

const char * server::socketopt_exception::what() const throw() { return _message.c_str(); }

server::socketopt_exception::socketopt_exception(const socketopt_exception & other) :
                        std::exception(), _message(other._message), _server_socket(other._server_socket) {}

server::socketopt_exception &server::socketopt_exception::operator=(const socketopt_exception &rhs) {
    _message = rhs._message;
    _server_socket = rhs._server_socket;
    return *this;
}

server::bind_exception::bind_exception(const int server_socket) :
                        std::exception(), _message("bind error"), _server_socket(server_socket){}

server::bind_exception::bind_exception(const int server_socket, const char * message) :
                        std::exception(), _message(message), _server_socket(server_socket){}

server::bind_exception::~bind_exception() throw() {
    if(_server_socket != 0 && _server_socket != 1 && _server_socket != 2)
        close(_server_socket);
}

const char * server::bind_exception::what() const throw() { return _message.c_str(); }

server::bind_exception::bind_exception(const bind_exception & other) :
                        std::exception(), _message(other._message), _server_socket(other._server_socket) {}

server::bind_exception &server::bind_exception::operator=(const bind_exception &rhs) {
    _message = rhs._message;
    _server_socket = rhs._server_socket;
    return *this;
}

server::listen_exception::listen_exception(const int server_socket) :
                        std::exception(), _message("listen error"), _server_socket(server_socket){}

server::listen_exception::listen_exception(const int server_socket, const char * message) :
                        std::exception(), _message(message), _server_socket(server_socket) {}

server::listen_exception::~listen_exception() throw() {
    if(_server_socket != 0 && _server_socket != 1 && _server_socket != 2)
        close(_server_socket);
}

const char * server::listen_exception::what() const throw() { return _message.c_str(); }

server::listen_exception::listen_exception(const listen_exception & other) :
                        std::exception(), _message(other._message), _server_socket(other._server_socket) {}

server::listen_exception &server::listen_exception::operator=(const listen_exception &rhs) {
    _message = rhs._message;
    _server_socket = rhs._server_socket;
    return *this;
}

server::accept_exception::accept_exception() : std::exception(), _message("accept error"){}

server::accept_exception::accept_exception(const char * message) : std::exception(), _message(message) {}

server::accept_exception::~accept_exception() throw() {}

const char * server::accept_exception::what() const throw() { return _message.c_str(); }

server::accept_exception::accept_exception(const accept_exception & other) : std::exception(), _message(other._message) {}

server::accept_exception &server::accept_exception::operator=(const accept_exception &rhs) {
    _message = rhs._message;
    return *this;
}

server::epoll_exception::epoll_exception() : std::exception(), _message("epoll error"){}

server::epoll_exception::epoll_exception(const char * message) : std::exception(), _message(message) {}

server::epoll_exception::~epoll_exception() throw() {}

const char * server::epoll_exception::what() const throw() { return _message.c_str(); }

server::epoll_exception::epoll_exception(const epoll_exception & other) : std::exception(), _message(other._message) {}

server::epoll_exception &server::epoll_exception::operator=(const epoll_exception &rhs) {
    _message = rhs._message;
    return *this;
}

server::launch_exception::launch_exception() : std::exception(), _message("launch error"){}

server::launch_exception::launch_exception(const char * message) : std::exception(), _message(message) {}

server::launch_exception::~launch_exception() throw() {}

const char * server::launch_exception::what() const throw() { return _message.c_str(); }

server::launch_exception::launch_exception(const launch_exception & other) : std::exception(), _message(other._message) {}

server::launch_exception &server::launch_exception::operator=(const launch_exception &rhs) {
    _message = rhs._message;
    return *this;
}

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

data_server server::getDataServer() const{
    return this->_data;
}
void server::setDataServer(data_server& d){
    this->_data = d;
}

/*
*====================================================================================
*|                                      Signal                                      |
*====================================================================================
*/

//@todo implement handle fonction to quitte de fonction
void server::handle(int sig) {
    (void) sig;
    stat_of_server = false;
}

/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

void server::launcher() {
    try {
        signal(SIGINT, handle);
        signal(SIGKILL, handle);
        set_socket(_data.getDomain(), _data.getType(), _data.getProtocol());//create a new socket new socket with the data sever specification
        set_socket_option(_data.getLevel(), _data.getOptionName(), _data.getOptionVal());//set option of sever socket
        set_bind();
        set_listen(_data.getBacklog());
        accessor_socket_flag(_server_socket, F_SETFL, O_NONBLOCK);//init the socket non blocking force flag to respect subject
        create_epoll();
        set_epoll_socket(_server_socket, EPOLLIN);
        set_epoll_ctl(EPOLL_CTL_ADD, _server_socket, &_event);
        while(stat_of_server) {
            set_epoll_wait();
            std::cout << "number of trigg = " << _number_triggered_events << std::endl;
            for (int i = 0; i < _number_triggered_events; ++i) {
                if (_events[i].data.fd == _server_socket)
                    accept_connection();
                else
                    manage_event(_events[i].data.fd);
            }
        }
    }
    catch (const std::exception& e){//if necessary to save the socket in process
        throw e;
    }
}

/*
*====================================================================================
*|                                 private utils function to launch                 |
*====================================================================================
*/

int server::set_socket(int domain, int type, int protocol) {
    _server_socket = (socket(domain, type, protocol));
    if (_server_socket == 0)
        throw server::socket_exception();
    return _server_socket;
}

void server::set_socket_option(int level, int option_name, int option_val){
    if (setsockopt(_server_socket, level, option_name,
                   &option_val, (socklen_t)sizeof(option_val)))
        throw server::socketopt_exception(_server_socket);

}

void server::set_bind() {
    if (bind(_server_socket, reinterpret_cast<struct sockaddr *>(&_data.getAddress()),
            sizeof _data.getAddress()) < 0)
        throw server::bind_exception(_server_socket);
}

void server::set_listen(int backlog) {
    if (listen(_server_socket, backlog) < 0)
        throw server::listen_exception(_server_socket);
}

int server::accessor_socket_flag(int server_socket, int command, int flag){
    int return_flag = fcntl(server_socket, command, flag);
    if (return_flag < 0)
        throw server::bind_exception(_server_socket);
    return return_flag;
}
int server::create_epoll() {
    _epoll_fd = epoll_create(1);
    if (_epoll_fd == -1)
        throw server::epoll_exception();
    return _epoll_fd;
}

void server::set_epoll_socket(int socket, int events){
    _event.data.fd = socket;
    _event.events = events;
}

void server::set_epoll_ctl(int option, int socket, struct epoll_event *event) {
    if(epoll_ctl( _epoll_fd, option, socket, event) == -1)
        throw server::epoll_exception();
}

void server::set_epoll_wait() {
    _number_triggered_events = epoll_wait(_epoll_fd, _events, MAX_EVENTS, -1);//@todo switch maxevent
    if (_number_triggered_events == -1)
        throw server::epoll_exception();//possible to add message to differ each epoll exeption
}

void server::accept_connection() {
    _client_socket = accept(_server_socket, (struct sockaddr *)&_client_address, &_client_address_len);
    if (_client_socket == -1)
        throw server::accept_exception();
    accessor_socket_flag(_client_socket, F_SETFL, O_NONBLOCK);
    set_epoll_socket(_client_socket, EPOLLIN | EPOLLET);
    set_epoll_ctl(EPOLL_CTL_ADD, _client_socket, &_event);

}

void server::manage_event(int socket){
    //@todo juste simple recv and send to test
    char buffer[1024];
    ssize_t bytes_received;
    ssize_t bytes_send;
    std::string response;
    while ((bytes_received = recv(socket, buffer, sizeof(buffer), 0)) > 0) {
        response.append("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nHello, World!");
        bytes_send = send(socket, response.c_str(), response.length(), 0);
        if (bytes_send == -1 || bytes_received == -1) {
            std::cerr << "error" << std::endl;
            break;
        }
    }
    close(socket);

//    set_epoll_ctl(EPOLL_CTL_DEL, socket, NULL); for close socket unlonk
}