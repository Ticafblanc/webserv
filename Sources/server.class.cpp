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

server::server() : data() {}

server::server(const data_server & data) : data(data) {}

server::~server() {}

server::server(const server& other) : data(other.data) {}

server& server::operator=(const server& rhs){
    this->data = rhs.data;
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
    return this->data;
}
void server::setDataServer(data_server& d){
    this->data = d;
}

/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

void server::launcher() {
    struct epoll_event event = {}, events[MAX_EVENTS];
    int server_socket;
    try {
        server_socket = set_socket(data.getDomain(), data.getType(), data.getProtocol());//create a new socket new socket with the data sever specification
        set_sockoption(server_socket, data.getLevel(), data.getOptionName(), data.getOptionVal());//set option of sever socket
        set_bind(server_socket);
        set_listen(server_socket, data.getBacklog());
        accessor_socket_flag(F_SETFL, O_NONBLOCK);//init the socket non blocking force flag to respect subject
        create_epoll();
        set_epoll_socket();
        set_epoll_ctl();//standars tyo other fonction in while loop
        do {
            set_server_non_blocking();
            set_pollfd();
            this->i_arg[nbr_clients]++;
            set_poll();
            this->data.setNewSocket(accept(this->data.getServerFd(),
                (struct sockaddr *) &this->data.getAddress(),
                (socklen_t *) &this->data.getAddrlen()));
            if ((this->data.getNewSocket()) < 0) {
                    perror("In accept");
                    exit(EXIT_FAILURE);
            }
            // std::cout << "server = " << data.getIdServer() << " is close " << std::endl;
            break;
        } while (true);
    }
    catch (const std::exception& e){//if necessary to save the socket in process
        throw e;
    }

}
/*@todo move all set to static fonction*/
/*
*====================================================================================
*|                                      signal                                      |
*====================================================================================
*/

//void server::handle(int sig) {
//    close(this->new_socket);
//    close(this->server_fd);
//    exit(this->id_server);
//}

/*
*====================================================================================
*|                                 private utils function to launch                 |
*====================================================================================
*/

int server::set_socket(int domain, int type, int protocol) {
    int server_socket = (socket(domain, type, protocol));
    if (server_socket == 0)
        throw server::socket_exception();
    return server_socket;
}

void server::set_sockoption(int server_socket, int level, int option_name, int option_val){
    if (setsockopt(server_socket, level, option_name,
                   &option_val, (socklen_t)sizeof(option_val)))
        throw server::socketopt_exception(server_socket);

}

void server::set_bind(int server_socket) {
    if (bind(server_socket, reinterpret_cast<struct sockaddr *>(&this->data.getAddress()),
            sizeof this->data.getAddress()) < 0)
    throw server::bind_exception(server_socket);
}

void server::set_listen(int server_socket, int backlog) {
    if (listen(server_socket, backlog) < 0)
        throw server::listen_exception(server_socket);
}

int server::accessor_socket_flag(int server_socket, int command, int flag){
    int return_flag = fcntl(server_socket, command, flag);
    if (return_flag < 0)
        //throw an error
    return return_flag;
}
int server::create_epoll() {
    int epoll_fd = epoll_create(1);//if its necessary to save the epollfd in class
    if (epoll_fd == -1)
        throw server::epoll_exception();//possible to add message to differ each epoll exeption
    return epoll_fd;
}

struct epoll_event server::set_epoll_socket(int server_socket, struct epoll_event event){
    event.data.fd = i_arg[server_socket];
    event.events = POLLIN;
    return event;//show if its necessary to store in class
}

void server::set_epoll_ctl(int option) {
    if(epoll_ctl( i_arg[epoll_fd], option, i_arg[server_socket], &event) == -1)
        throw server::epoll_exception();//possible to add message to differ each epoll exeption
}

void server::set_epoll_wait() {
    i_arg[nbr_clients] = epoll_wait( i_arg[epoll_fd], events, MAX_EVENTS, -1) == -1;
    if (i_arg[nbr_clients] == -1)
        throw server::epoll_exception();//possible to add message to differ each epoll exeption
}