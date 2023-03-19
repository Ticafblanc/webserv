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

server::server() : pid(), server_fd(), new_socket(), address() {/*std::cout << "without arg" <<std::endl;*/}

server::server(int server_fd_, struct sockaddr_in& address_)
        : pid(fork()), server_fd(server_fd_), new_socket(), address(address_){/*std::cout << "arg" <<std::endl;*/}

server::~server() {/*std::cout << "arg" <<std::endl;*/}

server::server(const server& other) : pid(other.pid), server_fd(other.pid),
        new_socket(other.new_socket), address(other.address){/*std::cout << "copy" <<std::endl;*/}

server& server::operator=(const server& rhs){
    pid = rhs.pid;
    server_fd = rhs.server_fd;
    new_socket = rhs.new_socket;
    address = rhs.address;
    return *this;
}

