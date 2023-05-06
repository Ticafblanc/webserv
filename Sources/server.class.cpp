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

server::server() : data(), i_arg(2), s_arg(), event(), events() {}

server::server(data_server & data) : data(data), i_arg(2), s_arg(), event(), events() { }

server::~server() {
    try {
//        this->data.close_server_fd();
    }
    catch (const std::exception& e){
        throw e;
    }
}
server::server(const server& other) : data(other.data), i_arg(other.i_arg), s_arg(other.s_arg), event(other.event), events() {
    for (int i = 0; i < other.i_arg[nbr_clients]; ++i) {
        events[i] = other.events[i];
    }
}

server& server::operator=(const server& rhs){
    this->data = rhs.data;
    this->i_arg = rhs.i_arg;
    this->s_arg = rhs.s_arg;
    for (int i = 0; i < rhs.i_arg[nbr_clients]; ++i) {
        this->events[i] = rhs.events[i];
    }
    return *this;
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

const char *  server::socket_exception::what() const throw(){
    std::cout <<"errno = "<< errno << std::endl;
    return ("socket error");
}

const char *  server::socketopt_exception::what() const throw(){
    std::cout <<"errno = "<< errno << std::endl;
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
    return ("epoll error");
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
        set_socket();//create a new socket new socket with the data sever specification
        set_sockoption();
        set_bind();
        set_listen();
        accessor_server(F_SETFL, O_NONBLOCK);//init the socket non blocking
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
    catch (const std::exception& e){
        throw e;
    }

}

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

int server::set_socket() {
    i_arg[server_socket] = (socket(data.getDomain(), data.getType(), data.getProtocol()));
    if (data.getServerFd() == 0)
        throw server::socket_exception();
    return i_arg[server_socket];
}

void server::set_sockoption(){
    if (setsockopt(i_arg[server_socket], data.getLevel(), data.getOptionName(),
                   &data.getOptionVal(), (socklen_t)sizeof(data.getOptionVal()))) {
        throw server::socketopt_exception();
    }
}

void server::set_bind() {
    if (bind(i_arg[server_socket], reinterpret_cast<struct sockaddr *>(&this->data.getAddress()), sizeof this->data.getAddress()) < 0) {
        close(this->data.getServerFd());
        throw server::bind_exception();
    }
}

void server::set_listen() {
    if (listen(i_arg[server_socket], this->data.getBacklog()) < 0)
        throw server::listen_exception();
}

void server::accessor_server(int cmd, int flag){
    fcntl(i_arg[server_socket], cmd, flag);
}
void server::create_epoll() {
    i_arg[epoll_fd] = epoll_create(1);
    if (i_arg[epoll_fd] == -1) {
        throw server::epoll_exception();//possible to add message to differ each epoll exeption
    }
}

void server::set_epoll_socket(){
    event.data.fd = i_arg[server_socket];
    event.events = POLLIN;
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