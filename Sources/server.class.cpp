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

server::server(const config_webserv & config) : _config(config), _event(), _events(), _server_socket(),
                                            _client_socket(), _epoll_fd(), _number_triggered_events(), _client_address(), _client_address_len(sizeof(_client_address)) {}

server::~server() {}

server::server(const server& other) :   _config(other._config), _event(other._event), _events(), _server_socket(other._server_socket),
                                            _client_socket(), _epoll_fd(other._epoll_fd), _number_triggered_events(), _client_address(), _client_address_len() {
    //@todo change maxevent macro to data server variable
    for (int i = 0; i < MAX_EVENTS; ++i) {
        this->_events[i] = other._events[i];
    }
}

server& server::operator=(const server& rhs){
    this->_config = rhs._config;
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

server::server_exception::server_exception(const int server_socket, const char * message) :
                        std::exception(), _message(message), _server_socket(server_socket) {}

server::server_exception::~server_exception() throw() {}

const char * server::server_exception::what() const throw() { return _message.c_str(); }

server::server_exception::server_exception(const server_exception & other) :
                        std::exception(), _message(other._message), _server_socket(other._server_socket) {}

server::server_exception &server::server_exception::operator=(const server_exception &rhs) {
    _message = rhs._message;
    _server_socket = rhs._server_socket;
    return *this;
}

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

data_server server::getDataServer() const{
    return _config;
}
void server::setDataServer(data_server& d){
    this->_config = d;
}

/*
*====================================================================================
*|                                      Signal                                      |
*====================================================================================
*/

//@todo implement handle fonction to quitte de fonction
void server::handle(int sig) {
    (void) sig;
    _stat_of_server = false;
}

/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

void server::launcher() {
    signal(SIGINT, handle);
    signal(SIGKILL, handle);
    try {
        set_socket(_config);//create a new socket new socket with the data sever specification
        set_socket_option();//set option of sever socket
        set_bind();
        set_listen(_config.getBacklog());
        accessor_socket_flag(_server_socket, F_SETFL, O_NONBLOCK);//init the socket non blocking force flag to respect subject
        create_epoll();
        set_epoll_socket(_server_socket, EPOLLIN);
        set_epoll_ctl(EPOLL_CTL_ADD, _server_socket, &_event);
        while(_stat_of_server) {
            set_epoll_wait();
            std::cout << "number of trigg = " << _number_triggered_events << std::endl;
            for (int i = 0; i < _number_triggered_events; ++i) {
                if (_events[i].data.fd == _server_socket)//@todo change to methode for iter in serversket
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

void server::set_socket(int & server_socket, int domain) {
    server_socket = (socket(domain, SOCK_STREAM, IPPROTO_TCP));
    if (server_socket == 0)
        throw server::server_exception(*this, strerror(errno));
}

void server::set_socket_option(int & server_socket){
    int option_val = 1;
    if (setsockopt(server_socket, IPPROTO_TCP, SO_REUSEADDR,
                   &option_val, (socklen_t)sizeof(option_val)))
        throw server::server_exception(*this, strerror(errno));
}

void server::set_bind(int & server_socket, struct sockaddr * sock_address) {
    if (bind(server_socket, sock_address, sizeof(&sock_address)) < 0)
        throw server::server_exception(*this, strerror(errno));
}

void server::set_listen(int & server_socket, int backlog) {
    if (listen(server_socket, backlog) < 0)
        throw server::server_exception(*this, strerror(errno));
}

int server::accessor_socket_flag(int & server_socket, int command, int flag){
    int return_flag = fcntl(server_socket, command, flag);
    if (return_flag < 0)
        throw server::server_exception(*this, strerror(errno));
    return return_flag;
}
void server::create_epoll() {
    _epoll_instance = epoll_create(1);
    if (_epoll_instance == -1)
        throw server::server_exception(*this, strerror(errno));
}

void server::set_epoll_event(int & server_socket, struct epoll_event & event, int events){
    event.data.fd = server_socket;
    event.events = events;
}

void server::set_epoll_ctl(int option, int & server_socket, struct epoll_event * event) {
    if(epoll_ctl( _epoll_instance, option, server_socket, event) == -1)
        throw server::server_exception(*this, strerror(errno));
}

void server::set_epoll_wait() {
    _number_triggered_events = epoll_wait(_epoll_instance, _events, _config.max_events, -1);//@todo switch maxevent
    if (_number_triggered_events == -1)
        throw server::server_exception(*this, strerror(errno));
}

void server::accept_connection(int & server_socket) {
    _client_socket = accept(server_socket, (struct sockaddr *)&_client_address, &_client_address_len);
    if (_client_socket == -1)
        throw server::server_exception(*this, strerror(errno));
    accessor_socket_flag(_client_socket, F_SETFL, O_NONBLOCK);
    set_epoll_event(_client_socket, _client_event,EPOLLIN | EPOLLET);
    set_epoll_ctl(EPOLL_CTL_ADD, _client_socket, &_client_event);

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

/*check if file descriptor is open
 * if process fail throw server::socket_exception();
 */
int fd_isopen();

/*check if socket  is open
 * if process fail throw server::socket_exception();
 */
int socket_isopen();