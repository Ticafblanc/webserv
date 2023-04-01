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

server::server(data_server & data) : data(data){ }

server::~server() {
    try {
//        this->data.close_server_fd();
    }
    catch (const std::exception& e){
        throw e;
    }
}
server::server(const server& other) : data(other.data) { }

server& server::operator=(const server& rhs){
    this->data = rhs.data;
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

const char * server::accept_exception::what() const throw(){
    return ("accept error");

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

int server::launcher() {
//    try{
    set_socket();
    set_sockoption();
    set_bind();
    set_listen();
    std::cout << "server = " << data.getIdServer() << " is open on fd = " << data.getServerFd()
                << " a l'adress = " << this->data.getIpAddress() << ":" << this->data.getPort()<< std::endl;

//    do{
//        if ((this->data.getNewSocket() = accept(this->data.getServerFd(), (struct sockaddr *) &this->data.getAddress(),
//                                                (socklen_t *) &this->data.getAddrlen())) < 0) {
//            perror("In accept");
//            exit(EXIT_FAILURE);
//        }
//        std::cout << "server = " << data.getIdServer() << " is close " << std::endl;
//        break;
//    }while(1);

//    catch (const server::bind_exception& e){
//        try {
//            data.close_server_fd();
//            throw e;
//        }
//        catch (const std::exception& e){
//            throw e;
//        }
//    }
//    signal(SIGINT, handle);

//        while (1) {
//    //        int fd = accept(sockfd, NULL, NULL);
//    //        if (fd < 0)
//    //            throw server::accept_exception();
//
//    //        close(this->new_socket);
//            //start manage fork and process see to free rocess accept
//            //    pid = fork();
//            //    if(pid < 0)
//            //        exit(EXIT_FAILURE);
//            //    if(pid == 0){
//        }
//    }

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








