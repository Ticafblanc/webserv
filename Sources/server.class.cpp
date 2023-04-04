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

server::server() : data(), i_arg(1), s_arg(), fds() {}

server::server(data_server & data) : data(data), i_arg(1), s_arg(), fds(){ }

server::~server() {
    try {
//        this->data.close_server_fd();
    }
    catch (const std::exception& e){
        throw e;
    }
}
server::server(const server& other) : data(other.data), i_arg(other.i_arg), s_arg(other.s_arg), fds() {
    for (int i = 0; i < other.i_arg[nbr_clients]; ++i) {
        fds[i] = other.fds[i];
    }
}

server& server::operator=(const server& rhs){
    this->data = rhs.data;
    this->i_arg = rhs.i_arg;
    this->s_arg = rhs.s_arg;
    for (int i = 0; i < rhs.i_arg[nbr_clients]; ++i) {
        this->fds[i] = rhs.fds[i];
    }
    return *this;
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

const char *  server::socket_exception::what() const throw(){
    return ("socket error");
}

const char *  server::socketopt_exception::what() const throw(){
    return ("socketopt error");
}

const char *  server::bind_exception::what() const throw(){
    return ("bind error");
}

const char *  server::listen_exception::what() const throw(){
    return ("listen error");
}

const char * server::accept_exception::what() const throw() {
    return ("accept error");
}

const char * server::launch_exception::what() const throw(){
    return ("launch error");
}

const char * server::epoll_exception::what() const throw(){
    return ("poll error");
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
    try {
        set_socket();
        set_sockoption();
        set_bind();
        set_listen();
        set_server_non_blocking(this->data.getServerFd());
        set_pollfd(this->data.getServerFd());
        this->i_arg[nbr_clients] == 1;
        std::cout << "server = " << data.getIdServer() << " is open on fd = " << data.getServerFd()
                  << " a l'adresse = " << this->data.getIpAddress() << ":" << this->data.getPort() << std::endl;

        do {
            set_epoll();
//            if ((this->data.getNewSocket() = accept(this->data.getServerFd(),
//                                                    (struct sockaddr *) &this->data.getAddress(),
//                                                    (socklen_t *) &this->data.getAddrlen())) < 0) {
//                perror("In accept");
//                exit(EXIT_FAILURE);
//            }
            std::cout << "server = " << data.getIdServer() << " is close " << std::endl;
            break;
        } while (1);
    }
    catch (const std::exception& e){
        throw e;
    }
}

server::server(const data_server &data, const vector<int> &iArg, const vector<std::string> &sArg,
               const server::epoll_event &iEpoll, server::epoll_event *tEpoll) : data(data), i_arg(iArg), s_arg(sArg),
                                                                                 i_epoll(iEpoll), t_epoll(tEpoll) {}

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
*|                                 private utils membre function                    |
*====================================================================================
*/

void server::set_socket() {
    this->data.setServerFd(socket(this->data.getDomain(), this->data.getType(), this->data.getProtocol()));
    if (this->data.getServerFd() == 0)
        throw server::socket_exception();
}

void server::set_sockoption(){
    if (setsockopt(this->data.getServerFd(), this->data.getLevel(), this->data.getOptionName(),
                   &this->data.getOptionVal(), (socklen_t)sizeof(this->data.getOptionVal()))) {
        throw server::socketopt_exception();
    }
}

void server::set_bind() {
    if (bind(this->data.getServerFd(), reinterpret_cast<struct sockaddr *>(&this->data.getAddress()), sizeof this->data.getAddress()) < 0) {
        close(this->data.getServerFd());
        throw server::bind_exception();
    }
}

void server::set_listen() {
    if (listen(this->data.getServerFd(), this->data.getBacklog()) < 0)
        throw server::listen_exception();
}

void server::set_server_non_blocking(int fd){
    fcntl(this->data.getServerFd(), F_SETFL, get_flag(fd) | O_NONBLOCK);
}

void server::set_t_epoll(int fd){
    this->t_epoll[this->i_arg[nbr_events]].data.fd = fd;

    fds[this->i_arg[nbr_clients]].events = POLLIN;
}

void server::create_epoll() {
    if ((i_epoll = epoll_create(0)) < 0) {
        perror("Epoll creation failed");
        exit(EXIT_FAILURE);
    }
    if(poll(fds, this->i_arg[nbr_clients], -1) == -1)
        throw server::epoll_exception();
}

void server::wait_epoll(){
    nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    if (nfds == -1) {
        perror("Epoll wait failed");
        exit(EXIT_FAILURE);
    }
}

int server::get_flag(int fd) {
    int flag;
    socklen_t len = sizeof(flag);
    if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &flag, &len) == -1)
        throw server::socketopt_exception();
    return flag;
}

std::ostream &operator<<(std::ostream &os, const server &server) {
    os << "data: " << server.data << " i_arg: " << server.i_arg << " s_arg: " << server.s_arg << " i_epoll: "
       << server.i_epoll << " t_epoll: " << server.t_epoll;
    return os;
}




