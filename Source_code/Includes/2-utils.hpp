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

#include "1-exception.hpp"

template <class T>
pair<bool, typename vector<T>::iterator> checkVectorContain(vector<T> &vec,
                                                            T obj) {
  for (typename vector<T>::iterator i = vec.begin(); i != vec.end(); ++i)
    if (*i == obj)
      return make_pair(true, i);
  return make_pair(false, vec.end());
}
string itoa(int nb);
bool isDirectory(const string &path);
bool isFile(const string &path);
bool checkPermissionR(const string &path);
bool checkPermissionW(const string &path);
bool checkPermissionRW(const string &path);
bool checkPermissionX(const string &path);
void checkRessource(string &Path, const string &index, const int &sd,
                    bool (*p)(const string &));
bool autoIndexToHtml(string &path, string &body);
#endif // WEBSERV_UTILS_HPP
