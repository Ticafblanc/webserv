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
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <strings.h>
#include <sys/_types/_socklen_t.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

server::server() : data(), i_arg(1), s_arg(), fds() {this->ndfs = 1;}

server::server(data_server & data) : data(data), i_arg(1), s_arg(), fds(){this->ndfs = 1;}

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

const char * server::poll_exception::what() const throw(){
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
        this->ndfs = 1;
        std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 9\n\nReceived!";
        int newSocket = 0;
        char buf[4096] = {0};
        set_socket();
        set_sockoption();
        set_bind();
        set_listen();
        fcntl(this->data.getServerFd(), F_SETFL, O_NONBLOCK);
        set_first_pollfd();
        while(1)
        {
            set_poll();
            if (fds[0].revents & POLLIN)
            {
                if ((newSocket = accept(this->data.getServerFd(), (struct sockaddr *) &this->data.getAddress(), (socklen_t *)&this->data.getAddrlen())) < 0)
                {
                    perror("accept failed:");
                    exit(EXIT_FAILURE);
                }
                set_pollfd(newSocket);
                std::cout << "new connection." << std::endl;
            }
            for(int i = 1; i < this->ndfs; i++)
            {
                if (fds[i].revents & POLLIN)
                {
                    int recvLen = recv(fds[i].fd, buf, 4096, 0);
                    if (recvLen == 0)
                    {
                        std::cout << buf << std::endl;
                        close(fds[i].fd);
                        this->ndfs--;
                        i--;
                        bzero(buf, 4096);
                    }
                    else if (recvLen > 0)
                        send(fds[i].fd, response.c_str(), response.length(), 0);
                    else
                        std::cout << "not ready for data." << std::endl;
                }
            }
        }
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

void server::set_server_non_blocking(){
    fcntl(this->data.getServerFd(), F_SETFL, O_NONBLOCK);
}

void server::set_first_pollfd(){
    fds[0].fd = this->data.getServerFd();
    fds[0].events = POLLIN;
}

void server::set_pollfd(int fd)
{
    fds[this->ndfs].fd = fd;
    fds[this->ndfs].events = POLLIN;
    this->ndfs++;
}

void server::set_poll() {
    if(poll(fds, this->ndfs, -1) == -1)
        throw server::poll_exception();
}
