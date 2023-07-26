#pragma once

#ifndef WEBSERV_RECV_SEND_TPP
#define WEBSERV_RECV_SEND_TPP

#include <Source_Code/0-webserv_launch_main_project/Headers_external_library.hpp>

template<class T>
void recvData(int socket, std::vector<char>& buffer, T& base,
             bool (T::*dataIsNotComplete)(std::size_t&)) {
    std::size_t bytesRecv;

    do {
        bytesRecv = recv(socket, buffer.data(), buffer.size(), 0);
    } while ((base.*(dataIsNotComplete))(bytesRecv));
}

template<class T>
void sendData(int socket, std::vector<std::vector<char> >& buffers, T& base,
             bool (T::*dataIsNotComplete)(std::size_t&)){
    std::size_t bytesSend;

    do {
//        std::cout << buffers.front().data()  <<std::endl;
        bytesSend = send(socket, buffers.front().data(), buffers.front().size(), 0);
    }while ((base.*(dataIsNotComplete))(bytesSend));
    return ;
}

template<class T>
void readData(int fd, std::vector<char>& buffer,T& base,
              bool (T::*dataIsNotComplete)(std::size_t&)) {
    std::size_t bytesRead;

    do {
        bytesRead = read(fd, buffer.data(), buffer.size());
    } while ((base.*(dataIsNotComplete))(bytesRead));
}

template<class T>
void writeData(int fd, std::vector<char>& buffer, T& base,
               bool (T::*dataIsNotComplete)(std::size_t&)){
    std::size_t bytesWrite = 1;

    while ((base.*(dataIsNotComplete))(bytesWrite)){
        bytesWrite = write(fd, buffer.data(), buffer.size());
    }
}

template<class T>
void recvAndWriteData(int fd, int socket, std::vector<char>& buffer, T& base,
                        bool (T::*dataIsNotComplete)(std::size_t&)) {
    std::size_t bytes;

    do {
        if (!buffer.empty()) {
            write(fd, buffer.data(), buffer.size());
            buffer.clear();
        }
        if (buffer.empty())
            bytes = recv(socket, buffer.data(), buffer.size(), 0);
    } while ((base.*(dataIsNotComplete))(bytes));
}


#endif