#pragma once

#ifndef WEBSERV_RECV_SEND_TPP
#define WEBSERV_RECV_SEND_TPP

#include <Source_Code/0-Main/Includes/Headers.hpp>

template<class T>
void recvData(int socket, std::vector<char>& buffer, T& base,
             bool (T::*dataIsNotComplete)(std::size_t&)) {
    std::size_t bytesRecv;

    do {
        bytesRecv = recv(socket, buffer.data(), buffer.size(), 0);
    } while ((base.*(dataIsNotComplete))(bytesRecv));
}

template<class T>
void sendData(int socket, std::vector<char>& buffer, T& base,
             bool (T::*dataIsNotComplete)(std::size_t&)){
    std::size_t bytesSend;

    do {
        bytesSend = send(socket, buffer.data(), buffer.size(), 0);
    }while ((base.*(dataIsNotComplete))(bytesSend));
    return 0;
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
    std::size_t bytesWrite;

    do {
        bytesWrite = write(fd, buffer.data(), buffer.size());
    }while ((base.*(dataIsNotComplete))(bytesWrite));
}

template<class T>
void recvAndWriteData(int fd, int socket, std::vector<char>& buffer, T& base,
                        bool (T::*dataIsNotComplete)(std::size_t&)) {
    std::size_t bytes;

    do {
        bytes = write(fd, buffer.data(), buffer.size());
        if (bytes != buffer.size())
            break;
        bytes = recv(socket, buffer.data(), buffer.size(), 0);
    } while ((base.*(dataIsNotComplete))(bytes));
}


#endif