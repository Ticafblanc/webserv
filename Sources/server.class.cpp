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

server::server(t_data_server& data)
        : id_server(data.id), server_fd(), new_socket(), address(), addr_len() {
    try{
        set_socket(data.domain, data.type, data.protocol);//throw exception
        set_address(data.domain, data.ip_address, data.port);
        set_bind(this->server_fd, reinterpret_cast<struct sockaddr *>(&this->address), sizeof(address));//throw exception
        set_listen(this->server_fd, data.backlog);
    }
    catch (const server::bind_exception& e){
        close(this->server_fd);
        perror(e);
    }
}

server::~server() { close(this->server_fd); }

server::server(const server& other) : id_server(other.id_server), pid(other.pid), server_fd(other.server_fd),
                                      new_socket(other.new_socket), address(other.address), addr_len(other.addr_len){/*std::cout << "copy" <<std::endl;*/}

server& server::operator=(const server& rhs){
    id_server = rhs.id_server;
    pid = rhs.pid;
    server_fd = rhs.server_fd;
    new_socket = rhs.new_socket;
    address = rhs.address;
    addr_len = rhs.addr_len;
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

const char *  server::arg_exception::what() const throw(){
    return ("argument invalid");
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

int& server::getIdServer() {
    return id_server;
}

int& server::getServerFd(){
    return server_fd;
}

int& server::getNewSocket(){
    return new_socket;
}

sockaddr_in& server::getAddress() {
    return address;
}

size_t& server::getAddrlen(){
    return addr_len;
}

pid_t server::getPid() const {
    return pid;
}

void server::setIdServer(int idServer) {
    this->id_server = idServer;
}

void server::set_socket() {
    if (domain != AF_INET)//add other error
        throw server::arg_exception();
    this->server_fd = socket(domain, type, protocol);
    if (this->server_fd == 0)
        throw server::socket_exception();
}

void server::set_address(){
    if (domain != AF_INET)
        throw server::arg_exception();
    this->address.sin_family = domain;
    this->address.sin_addr.s_addr = inet_addr(ip_address);//check format ip address during the parsing no ERROR
    this->address.sin_port = htons(port);//no error
    memset(address.sin_zero, '\0', sizeof address.sin_zero);//a delete
    this->addr_len = sizeof(this->address);
}

void server::set_bind() {
    this->new_socket = bind(sockfd, addr, size);
    if (this->new_socket < 0) {
        close(sockfd);
        throw server::bind_exception();
    }
}

void server::set_listen() {
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

/*
*====================================================================================
*|                            private static fonction utils                         |
*====================================================================================
*/


int server::fd_isopen() {
    int ret = fcntl(fd, F_GETFL);
    if (ret == -1) {
        perror("fcntl");
        return 0;
    }
    return 0;
}

int server::socket_isopen() {
    int error = 0;
    socklen_t len = sizeof(error);
    int ret = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);
    if (ret != 0) {
        perror("getsockopt");
        return -1;
    }
    // Si l'erreur est 0, le socket est ouvert
    return (error == 0) ? 0 : -1;
}






