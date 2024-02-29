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
string checkRessource(string &root, string& path) ;
#endif // WEBSERV_UTILS_HPP
