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

#include "../Include/server.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

server::server(config_webserv& config) : _config(config), _epoll_instance(), _number_triggered_events(),
                                        _client_socket(), _client_event(), _client_address(),
                                                _client_address_len(sizeof(_client_address)) {
    _stat_of_server = false;
}

server::~server() {}

server::server(const server& other) :   _config(other._config), _epoll_instance(other._epoll_instance),
                                        _number_triggered_events(other._number_triggered_events),
                                        _client_socket(other._client_socket),
                                        _client_event(other._client_event), _client_address(other._client_address),
                                        _client_address_len(other._client_address_len){}

server& server::operator=(const server& rhs){
    this->_config = rhs._config;
    this->_epoll_instance = rhs._epoll_instance;
    this->_number_triggered_events = rhs._number_triggered_events;
    this->_client_socket = rhs._client_socket;
    this->_client_event = rhs._client_event;
    this->_client_address = rhs._client_address;
    this->_client_address_len = rhs._client_address_len;
    return *this;
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

server::server_exception::server_exception(server & server, const char * message) :
                        std::exception(), _message(message), _server(server) {}

server::server_exception::~server_exception() throw() {}

const char * server::server_exception::what() const throw() { return _message.c_str(); }

server::server_exception::server_exception(const server_exception & other) :
                        std::exception(), _message(other._message), _server(other._server) {}

server::server_exception &server::server_exception::operator=(const server_exception &rhs) {
    _message = rhs._message;
    _server = rhs._server;
    return *this;
}

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

config_webserv server::get_config_webserv() const {
    return _config;
}

/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

void server::launcher() {
    _stat_of_server = true;
    try {
        set_epoll();

//
//        create_epoll();
//        set_epoll_socket(_server_socket, EPOLLIN);
//        set_epoll_ctl(EPOLL_CTL_ADD, _server_socket, &_event);
//        while(_stat_of_server) {
//            set_epoll_wait();
//            std::cout << "number of trigg = " << _number_triggered_events << std::endl;
//            for (int i = 0; i < _number_triggered_events; ++i) {
//                if (_events[i].data.fd == _server_socket)//@todo change to methode for iter in serversket
//                    accept_connection();
//                else
//                    manage_event(_events[i].data.fd);
//            }
//        }
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
void server::set_epoll(){
    create_epoll();
    for (std::vector<bloc_server>::iterator server = _config._bloc_http._vector_bloc_server.begin();
    server != _config._bloc_http._vector_bloc_server.end(); ++server){
        for (std::vector<listen_data>::iterator vec_listen = server->_vector_listen.begin();
             vec_listen != server->_vector_listen.end(); ++vec_listen) {
            set_epoll_event(vec_listen->_server_socket, _server_event, EPOLLIN);
            set_epoll_ctl(EPOLL_CTL_ADD, vec_listen->_server_socket, &_server_event);
        }
    }
    create_epoll();
}

void server::create_epoll() {
    _epoll_instance = epoll_create(1);
    if (_epoll_instance == -1)
        throw server::server_exception(*this, strerror(errno));
}

void server::set_epoll_ctl(int option, int & server_socket, struct epoll_event * event) {
    if(epoll_ctl( _epoll_instance, option, server_socket, event) == -1)
        throw server::server_exception(*this, strerror(errno));
}


void server::set_socket(int & server_socket) {
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == 0)
        throw server::server_exception(*this, strerror(errno));
}

void server::set_socket_option(int & server_socket){
    int option_val = 1;
    if (setsockopt(server_socket, IPPROTO_TCP, SO_REUSEADDR,
                   &option_val, (socklen_t)sizeof(option_val)))
        throw server::server_exception(*this, strerror(errno));
}

void server::set_bind(int & server_socket, sockaddr_in sock_address) {
    if (bind(server_socket, reinterpret_cast<struct sockaddr *>(&sock_address), sizeof(sock_address)) < 0)
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


void server::set_epoll_event(int & server_socket, struct epoll_event & event, int events){
    event.data.fd = server_socket;
    event.events = events;
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
    set_epoll_event(_client_socket, _client_event, EPOLLIN | EPOLLET);
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



//int data_server::fd_isopen() {
//    int ret = fcntl(getServerFd(), F_GETFL);
//    if (ret == -1) {
//        throw data_server::data_exception();
//    }
//    return 1;
//}
//
//int data_server::socket_isopen() {
//    int error;
//    socklen_t len = sizeof(error);
//    int ret = getsockopt(getServerFd(), SOL_SOCKET, SO_ERROR, &error, &len);
//    if (ret != 0 || error > 0) {i
//        throw data_server::data_exception();
//    }
//    return 1;
//}


