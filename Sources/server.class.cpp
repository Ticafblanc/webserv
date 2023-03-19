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

server::server() : id_server(), pid(), server_fd(), new_socket(), address(), addrlen() {/*std::cout << "without arg" <<std::endl;*/}

server::server(const int id, const char * ip_address, const int port, const int domain, const int type, const int protocol, const int backlog)
        : id_server(id), pid(), server_fd(), new_socket(), address(), addrlen() {/*std::cout << "without arg" <<std::endl;*/
    try{
        set_socket(domain, type, protocol);//throw exception
        set_address(domain, ip_address, port);
        set_bind(this->server_fd, reinterpret_cast<struct sockaddr *>(&this->address), sizeof(address));//throw exception
        set_listen(this->server_fd, backlog);
    }
    catch (const server::bind_exception& e){
        close(this->server_fd);
        throw e;
    }
}

server::~server() {/*std::cout << "arg" <<std::endl;*/}

server::server(const server& other) : id_server(other.addrlen), pid(other.pid), server_fd(other.pid),
        new_socket(other.new_socket), address(other.address), addrlen(){/*std::cout << "copy" <<std::endl;*/}

server& server::operator=(const server& rhs){
    pid = rhs.pid;
    server_fd = rhs.server_fd;
    new_socket = rhs.new_socket;
    address = rhs.address;
    return *this;
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

const char *  server::socket_exception::what() const throw(){
    return ("socket exeption");//voir si return errno !!
}

const char *  server::arg_exception::what() const throw(){
    return ("argument invalid");
}

const char *  server::bind_exception::what() const throw(){
    return ("bind exeption");//voir si return errno
}

const char *  server::listen_exception::what() const throw(){
    return ("listen exeption");//voir si return errno
}

std::pair<int, const char *> server::accept_exception::what(int status) throw(){
    return (std::make_pair(status, "accept error"));//voir si return errno
}
/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

const int& server::getIdServer() const {
    return id_server;
}

const pid_t& server::getPid() const {
    return pid;
}

const int& server::getServerFd() const {
    return server_fd;
}

const int& server::getNewSocket() const {
    return new_socket;
}

const sockaddr_in& server::getAddress() const{
    return address;
}

const int& server::getAddrlen() const {
    return addrlen;
}

void server::setIdServer(int idServer) {
    id_server = idServer;
}

void server::set_socket(const int domain, const int type, const int protocol) {
    if (domain != AF_INET)//add other error
        throw server::arg_exception();
    this->server_fd = socket(domain, type, protocol);
    if (server_fd == 0)
        throw server::socket_exception();
}

void server::set_address(const int domain, const char *ip_address, const int port){
    if (domain != AF_INET)
        throw server::arg_exception();
    this->address.sin_family = domain;
    this->address.sin_addr.s_addr = inet_addr(ip_address);//check format ip address during the parsing no ERROR
    this->address.sin_port = htons(port);//no error
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    this->addrlen = sizeof(this->address);
}

void server::set_bind(const int sockfd, struct sockaddr* addr, const size_t size) {
    int res;
    res = bind(sockfd, addr, size);
    if (res < 0)
        throw server::bind_exception();
}

void server::set_listen(const int sockfd, const int backlog) {
    int res;
    res = listen(sockfd, backlog);
    if (res < 0)
        throw server::listen_exception();
}

/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

int server::launcher(const int sockfd, struct sockaddr* addr, socklen_t* addr_len){
    int res;
    res = accept(sockfd, addr, addr_len);
    if (res < 0)
        throw server::accept_exception();
//    pid = fork();
//    if(pid < 0)
//        exit(EXIT_FAILURE);
//    if(pid == 0){
//        std::cout << address.sin_addr.s_addr << " " << inet_addr("127.0.0.1") << std::endl;
//
    return 0;
    }






