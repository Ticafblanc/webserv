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

server::server() : id_server(), server_fd(), new_socket(), address(), addr_len() {
    return;
}

server::server(const int id, const char * ip_address, const int port, const int domain, const int type, const int protocol, const int backlog)
        : id_server(id), server_fd(), new_socket(), address(), addr_len() {/*std::cout << "without arg" <<std::endl;*/
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

server::~server() { close(this->server_fd); }

server::server(const server& other) : id_server(other.id_server), server_fd(other.server_fd),
                                      new_socket(other.new_socket), address(other.address), addr_len(other.addr_len){/*std::cout << "copy" <<std::endl;*/}

server& server::operator=(const server& rhs){
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

int & server::getAddrlen(){
    return addr_len;
}

void server::setIdServer(int idServer) {
    this->id_server = idServer;
}

void server::set_socket(int domain, int type, int protocol) {
    if (domain != AF_INET)//add other error
        throw server::arg_exception();
    this->server_fd = socket(domain, type, protocol);
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
//    signal(SIGINT, handle);
    pid_t pid = fork();
    if (!pid) {
        while (1) {
            this->new_socket = accept(this->server_fd, (struct sockaddr *)&this->address, (socklen_t*)&this->addr_len);
            if (this->new_socket < 0)
                throw server::accept_exception();
            std::cout << this->id_server << std::endl;
            close(this->new_socket);
            //start manage fork and process see to free rocess accept
            //    pid = fork();
            //    if(pid < 0)
            //        exit(EXIT_FAILURE);
            //    if(pid == 0){
        }
    }

    return 0;
}

//pid_t server::getPid() const {
//    return pid;
//}

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








