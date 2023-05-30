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

server::server(config_webserv& config) : _config(config), _request(config), _epoll_instance(), _number_triggered_events(), _webserv_event(),
                                         _server_events(new struct epoll_event[config._bloc_http._number_max_events]),
                                         _client_address(), _client_address_len(sizeof(_client_address)), _map_connection(){
    _map_connection["connection"] = &server::connect_new_client;
    _map_connection["close"] = &server::disconnect_client;
    _map_connection["keep-alive"] = &server::keep_alive;
}

server::~server() {
    delete[] _server_events;
}

server::server(const server& other) :   _config(other._config), _request(other._request),_epoll_instance(other._epoll_instance),
                                        _number_triggered_events(other._number_triggered_events),
                                        _webserv_event(other._webserv_event), _server_events(other._server_events),
                                        _client_address(other._client_address),
                                        _client_address_len(other._client_address_len){}

server& server::operator=(const server& rhs){
    this->_config = rhs._config;
    this->_epoll_instance = rhs._epoll_instance;
    this->_number_triggered_events = rhs._number_triggered_events;
    this->_webserv_event = rhs._webserv_event;
    this->_server_events = rhs._server_events;
    this->_client_address = rhs._client_address;
    this->_client_address_len = rhs._client_address_len;
    return *this;
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

server::server_exception::server_exception(const char * message) : _message(message) {}

server::server_exception::~server_exception() throw() {}

const char * server::server_exception::what() const throw() { return _message.c_str(); }

server::server_exception::server_exception(const server::server_exception & other) : _message(other._message) {}

server::server_exception &server::server_exception::operator=(const server::server_exception &rhs) {
    this->_message = rhs._message;
    return *this;
}


/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

void server::launcher() {
    try {
        set_epoll();
        while(true) {
            try {
                set_epoll_wait();
                for (int i = 0; i < _number_triggered_events; ++i) {
                    _server_events[i].data.fd = (this->*(_map_connection.find(_request.manage_request(_server_events[i]))->second))(_server_events[i].data.fd);

                }
            }
            catch (const std::exception& e){
                std::cout << e.what() << std::endl;
                //@todo http_request request(_server_events[position], *server);
            }
        }
    }
    catch (const std::exception& e){//if necessary to save the socket in process reset error value
        std::cout << e.what() << std::endl;
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
            set_epoll_event(vec_listen->_server_socket, _webserv_event, EPOLLIN);
            set_epoll_ctl(EPOLL_CTL_ADD, vec_listen->_server_socket);
        }
    }
}

void server::create_epoll() {
    _epoll_instance = epoll_create(1);
    if (_epoll_instance == -1)
        throw server_exception(strerror(errno));
}

void server::set_epoll_event(int & server_socket, struct epoll_event & event, int events){
    event.data.fd = server_socket;
    event.events = events;
}

void server::set_epoll_ctl(int option, int server_socket) {
    if(epoll_ctl( _epoll_instance, option, server_socket, &_webserv_event) == -1){
        server_exception server_exception(strerror(errno));
        throw server_exception;
    }
}

void server::set_epoll_wait() {
    _number_triggered_events = epoll_wait(_epoll_instance, _server_events,_config._bloc_http._number_max_events, -1);//@todo manage limit connectiuon
    if (_number_triggered_events == -1)
        throw server::server_exception(strerror(errno));
}



int server::accessor_socket_flag(int & server_socket, int command, int flag){
    int return_flag = fcntl(server_socket, command, flag);
    if (return_flag < 0)
        throw server::server_exception(strerror(errno));
    return return_flag;
}

int server::connect_new_client(int new_client_socket) {
    new_client_socket = accept(new_client_socket, reinterpret_cast<struct sockaddr *>(&_client_address),
            &_client_address_len);
    if (new_client_socket == -1) {
        server_exception server_exception(strerror(errno));
        throw server_exception;
    }
    accessor_socket_flag(new_client_socket, F_SETFL, O_NONBLOCK);
    set_epoll_event(new_client_socket, _webserv_event, EPOLLIN | EPOLLET);
    set_epoll_ctl(EPOLL_CTL_ADD, new_client_socket);
    _config._bloc_http._number_max_events--;
    _config._bloc_http._map_client_socket.insert(std::make_pair(new_client_socket, _config._bloc_http._select_bloc_server));
    _request.send_data_client(new_client_socket);
    return new_client_socket;
}

int server::disconnect_client(int client_socket) {
    _request.send_data_client(client_socket);
    _config._bloc_http._number_max_events++;
    set_epoll_ctl(EPOLL_CTL_DEL, client_socket);
    close(client_socket);
    return client_socket;
}

int server::keep_alive(int client_socket) {
    _request.send_data_client(client_socket);
    return client_socket;
}
