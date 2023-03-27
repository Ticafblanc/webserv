/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-server.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:19:31 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 15:19:34 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../Include/server.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

server::server(data_server & data) : data(data){ }

server::~server() {
    try {
        data.close_server_fd();
    }
    catch (const std::exception& e){
        throw e;
    }
}
server::server(const server& other) : data(other.data) { }

server& server::operator=(const server& rhs){
    data = rhs.data;
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

const char *  server::bind_exception::what() const throw(){
    return ("bind error");
}

const char *  server::listen_exception::what() const throw(){
    return ("listen error");
}

const char * server::accept_exception::what() const throw(){
    return ("accept error");

}
/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

void server::set_socket(int domain, int type, int protocol) {
    if (domain != AF_INET)//add other error
        throw server::arg_exception();
    this->server_fd = socket(domain, type, protocol);
    int i  = this->server_fd;
    if (this->server_fd == 0)
        throw server::socket_exception();
}

void server::set_address(const int domain, const char *ip_address, const int port){
    if (domain != AF_INET)
        throw server::arg_exception();
    this->address.sin_family = domain;
    this->address.sin_addr.s_addr = inet_addr(ip_address);//check format ip address during the parsing no ERROR
    this->address.sin_port = htons(port);//no error
    memset(address.sin_zero, '\0', sizeof address.sin_zero);//a delete
    this->addr_len = sizeof(this->address);
}

void server::set_bind(const int sockfd, struct sockaddr* addr, const size_t size) {
    this->new_socket = bind(sockfd, addr, size);
    if (this->new_socket < 0) {
        close(sockfd);
        throw server::bind_exception();
    }
}

void server::set_listen(const int sockfd, const int backlog) {
    this->new_socket = listen(sockfd, backlog);
    if (this->new_socket < 0)
        throw server::listen_exception();
}

/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

int server::launcher(const int sockfd, struct sockaddr* addr, socklen_t* addr_len) {
    try{
        set_socket();//throw exception
        set_bind();//throw exception
        set_listen();
    }
    catch (const server::bind_exception& e){
        try {
            data.close_server_fd();
        }
        catch (const std::exception& e){
            throw e;
        }
    }
//    signal(SIGINT, handle);
    std::cout << "server = " << this->id_server << " is open on fd = " << this->getServerFd() << std::endl;
    pid = fork();
    if (!pid){
        while (1) {
    //        int fd = accept(sockfd, NULL, NULL);
    //        if (fd < 0)
    //            throw server::accept_exception();

    //        close(this->new_socket);
            //start manage fork and process see to free rocess accept
            //    pid = fork();
            //    if(pid < 0)
            //        exit(EXIT_FAILURE);
            //    if(pid == 0){
        }
    }

    return 0;
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








