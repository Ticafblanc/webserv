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

bool checkPermissionR(const string &path) {
  return !access(path.c_str(), R_OK);
}

bool checkPermissionW(const string &path) {
  return !access(path.c_str(), W_OK);
}

bool checkPermissionX(const string &path) {
  return !access(path.c_str(), X_OK);
}

void checkRessource(string &Path, const string &index, const int &sd,
                    bool (*p)(const string &)) {
  if (isDirectory(Path))
    Path += index;
  if (isFile(Path)) {
    if (p(Path))
      return;
    else
      throw Exception("Permission fail", sd, "403");
  } else
    throw Exception("uri not found", sd, "404");
}

string setTime() {
  time_t now = time(0);
  tm *timeInfo = gmtime(&now);
  char buffer[80];
  strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
  return string(buffer);
}

bool autoIndexToHtml(string &path, string & body) {
  ostringstream oss;
  DIR *directory = opendir(path.c_str());
  if (!directory)
    return false;
  oss << "<!DOCTYPE html><html><head><title>Auto Index of " << path
      << "</title></head><body><h1>Auto Index of " << path << "</h1><ul>";
  struct dirent *entry;
  while ((entry = readdir(directory)) != NULL) {
    oss << "<li><a href=\"" << entry->d_name << "\">" << entry->d_name
        << "</a></li>";
  }
  oss << "</ul></body></html>";
  closedir(directory);
  body = oss.str();
  return true;
}