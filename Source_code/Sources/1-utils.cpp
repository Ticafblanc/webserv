//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/1-utils.hpp"

void throwError(const exception &ex) {
  cerr << "\033[1m\033[31mERROR \033[0m: " << ex.what() << '\n';
}

void printError(const string &msg) {
  cerr << "\033[1m\033[31mERROR \033[0m: " << msg << '\n';
}

string itoa(int nb) {
  string s;
  stringstream out;
  out << nb;
  s = out.str();
  return (s);
}

bool isDirectory(const string &path) {
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

bool isExec(const string &path) {
  struct stat statBuf = {};
  if (stat(path.c_str(), &statBuf) != 0)
    return false;
  return S_ISREG(statBuf.st_mode) &&
         (statBuf.st_mode & S_IXUSR || statBuf.st_mode & S_IXGRP ||
          statBuf.st_mode & S_IXOTH);
}

int pathType(const string &path) {
  if (isDirectory(path))
    return 1;
  if (isFile(path))
    return 2;
  if (isExec(path))
    return 3;
  return 0;
}

string checkRessource(string &root, string &path) {
  pathType(root + path);
  if (!pathType(root + path))
    return "";
  return root + path;
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

bool removeDirectory(string &path) {
  DIR *directory = opendir(path.c_str());
  if (!directory)
    return removeFile(path);
  struct dirent *entry;
  while ((entry = readdir(directory)) != NULL) {
    if (string(entry->d_name) != "." || string(entry->d_name) != "..") {
      string entryPath = path + "/" + string(entry->d_name);
      if (isFile(entryPath))
        if (removeFile(entryPath))
          continue;
    }
  }
  closedir(directory);
  return removeFile(path);
}

bool removeFile(string &path) {
  if (remove(path.c_str()) != 0)
    return false;
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
  //    while (!is.eof()) {
  is.read(buffer.data(), buffer.size());
  streamsize bytes_read = is.gcount();
  cout << "conten " << contentLength << "gcount " << bytes_read << "buffer size"
       << buffer.size() << endl;
  //        if (bytes_read <= 0) {
  //            break;
  //        }
  write(fd, buffer.data(), contentLength);
  buffer.clear();
  //    }
  return true;
}
