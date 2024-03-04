//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/2-utils.hpp"

string itoa(int nb) {
  string s;
  stringstream out;
  out << nb;
  s = out.str();
  return (s);
}

bool isDirectory(const string &path, const int & sd) {
  struct stat statBuf = {};
  if (stat(path.c_str(), &statBuf) != 0)
    return false;
  return S_ISDIR(statBuf.st_mode);
}

bool isFile(const string &path) {
  struct stat statBuf = {};
  if (stat(path.c_str(), &statBuf) != 0) {
    return false;
  }
  return S_ISREG(statBuf.st_mode);
}

bool checkPermissionR(const string &path) {
  return !access(path.c_str(), R_OK);
}

bool checkPermissionW(const string &path) {
  return !access(path.c_str(), W_OK);
}

bool checkPermissionX(const string &path) {
  return !access(path.c_str(), X_OK);
}

string setTime() {
  time_t now = time(0);
  tm *timeInfo = gmtime(&now);
  char buffer[80];
  strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
  return string(buffer);
}

bool autoIndexToHtml(string &path, string &url, ostringstream &oss) {
  DIR *directory = opendir(path.c_str());
  if (!directory)
    return false;
  oss << "<!DOCTYPE html><html><head><title>Auto Index of " << url
      << "</title></head><body><h1>Auto Index of " << url << "</h1><ul>";
  struct dirent *entry;
  while ((entry = readdir(directory)) != NULL) {
    oss << "<li><a href=\"" << entry->d_name << "\">" << entry->d_name
        << "</a></li>";
  }
  oss << "</ul></body></html>";
  closedir(directory);
  return true;
}

bool extractFileToFd(const string &path, int fd, size_t &contentLength) {
  ifstream is(path.c_str(), ios::binary | ios::in);
  if (!is.is_open())
    return false;
  is.seekg(0, ios::end);
  contentLength = is.tellg();
  is.seekg(0, ios::beg);
  vector<char> buffer(contentLength);
  is.read(buffer.data(), buffer.size());
  streamsize bytes_read = is.gcount();
  cout << "conten " << contentLength << "gcount " << bytes_read << "buffer size"
       << buffer.size() << endl;
  write(fd, buffer.data(), contentLength);
  return true;
}
