//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_UTILS_HPP
#define WEBSERV_UTILS_HPP
#if DEBUG_ACTIVE == 1
#define DEBUG(x) std::cout << x << std::endl;
#else
#define DEBUG(x)
#endif

#include "main.hpp"
#include "configuration.hpp"
#include "headers.hpp"


class Log
{
public:
  Log(string msg)
  {
    struct timeval current_time;
    char time_buffer[100];
    bzero(time_buffer, 100);
    gettimeofday(&current_time, NULL);
//    strftime(time_buffere_buffer,100, localtime(&current_time.tv_sec));
    cout << "[" << time_buffer << "] : " << msg << endl;
  }
};

class throwMessage : public exception {
private:
  string _msg;

public:
  throwMessage (const std::string& msg) throw() : _msg(msg) {}
  throwMessage (const throwMessage&) throw() {}
  throwMessage& operator= (const throwMessage&) throw();
  virtual ~throwMessage() throw() {}
  virtual const char* what() const throw() { return (_msg.c_str()); }
};

class throwMessageErrno : public exception {
private:
  string _msg;

public:
  throwMessageErrno (const string& msg) throw()
  {
    stringstream ss;
    ss << msg << " : " << strerror(errno);
    this->_msg = ss.str();
  }

  throwMessageErrno (const throwMessageErrno&) throw() {}
  throwMessageErrno& operator= (const throwMessageErrno&) throw();
  virtual ~throwMessageErrno() throw() {}
  virtual const char* what() const throw() { return (_msg.c_str()); }
};

void throwError(const std::exception& ex);
void printError(const std::string& msg);
//int treat(int sd, Headers &header_block, Server server_conf);
void endServer(int signal);

#endif // WEBSERV_UTILS_HPP
