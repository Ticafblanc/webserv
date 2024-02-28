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

#include "0-main.hpp"

template <class T>
pair<bool, typename vector<T>::iterator> checkVectorContain(vector<T> &vec,
                                                            T obj) {
  for (typename vector<T>::iterator i = vec.begin(); i != vec.end(); ++i)
    if (*i == obj)
      return make_pair(true, i);
  return make_pair(false, vec.end());
}

class Log {
public:
  Log(string msg) {
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
  throwMessage(const std::string &msg) throw() : _msg(msg) {}
  throwMessage(const throwMessage &) throw() {}
  throwMessage &operator=(const throwMessage &) throw();
  virtual ~throwMessage() throw() {}
  virtual const char *what() const throw() { return (_msg.c_str()); }
};

class throwMessageErrno : public exception {
private:
  string _msg;

public:
  throwMessageErrno(const string &msg) throw() {
    stringstream ss;
    ss << msg << " : " << strerror(errno);
    this->_msg = ss.str();
  }

  throwMessageErrno(const throwMessageErrno &) throw() {}
  throwMessageErrno &operator=(const throwMessageErrno &) throw();
  virtual ~throwMessageErrno() throw() {}
  virtual const char *what() const throw() { return (_msg.c_str()); }
};

void throwError(const exception &ex);
void printError(const string &msg);
string itoa(int nb);
bool isDirectory(string &path);
bool isFile(const string &path);
bool isExec(const string &path);
int pathType(const string &path);
string setTime();
bool autoIndexToHtml(string & path, string & url, ostringstream &oss);
bool removeDirectory(string &path);
bool removeFile(string &path);
bool extractFileToFd(const string & path, int fd, size_t & contentLength);

#endif // WEBSERV_UTILS_HPP
