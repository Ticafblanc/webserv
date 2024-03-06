//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/3-configuration.hpp"

static bool extractBlocks(vecStr &split, istringstream &isStr, string &line) {
  bool ret = true;
  while (getline(isStr, line) && ret) {
    if (line.find('{') != string::npos) {
      split.back() += "\n" + line;
      ret = extractBlocks(split, isStr, line);
    } else {
      split.back() += "\n" + line;
      if (line.find('}') != string::npos) {
        if (line.size() != 1)
          return false;
        return true;
      }
    }
  }
  return ret;
}

bool splitBlocks(vecStr &split, const string &str, const string &pattern,
                 vecStr &otherInfo) {
  istringstream isStr(str);
  size_t typePattern = (pattern == "server" ? 1 : 2);
  string line;
  bool ret = true;
  while (getline(isStr, line) && ret) {
    if (line.find(pattern) != string::npos) {
      vecStr tmpSplit;
      splitPattern(tmpSplit, line, ' ');
      if (tmpSplit[0] == pattern && tmpSplit[typePattern] == "{" &&
          tmpSplit.size() == typePattern + 1) {
        split.push_back(line);
        ret = extractBlocks(split, isStr, line);
      } else
        return false;
    } else {
      istringstream iss(line);
      getline(iss >> ws, line, ';');
      otherInfo.push_back(line);
    }
  }
  return (ret);
}

void splitPattern(vecStr &split, const string &str, const char &pattern) {
  istringstream is(str);
  string toAdd;
  if (pattern == ' ') {
    while (is >> ws >> toAdd) {
      split.push_back(toAdd);
    }
  } else {
    while (getline(is >> ws, toAdd, pattern)) {
      split.push_back(toAdd);
    }
  }
}

vecStr splitStr(string str) {
  vecStr split(3);

  int i = 0;
  istringstream is(str);
  while (is.good() && i < 3) {
    is >> split[i];
    i++;
  }
  return split;
}

static bool uselessLine(string &line) {
  istringstream iss(line);
  string word;
  iss >> ws >> word;
  return word.empty();
}

static string removeSpaces(string &line) {
  if (line.empty())
    return line;
  string word;
  istringstream iss(line);
  line.clear();
  while (iss >> ws >> word)
    line += word + ' ';
  line[line.size() - 1] = '\n';
  return line;
}

static bool removeCommentary(string &line) {
  size_t commentPos;

  commentPos = line.find('#');
  if (commentPos == 0)
    return "";
  else if (commentPos != string::npos)
    line = line.substr(0, commentPos);
  return !line.empty();
}

bool checkWordFormat(const string &str) {
  string validChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                     "0123456789-._~:/?#[]@!$&'()*+,;=";

  for (string::const_iterator i = str.begin(); i != str.end(); ++i) {
    if (validChar.find(*i) == std::string::npos) {
      return (false);
    }
  }
  return (true);
}

bool readFile(const string &file, string &fileString) {
  ifstream fileStream(file.c_str());
  string line;

  if (!fileStream.is_open())
    return false;
  while (getline(fileStream, line)) {
    if (!uselessLine(line) && removeCommentary(line))
      fileString += removeSpaces(line);
  }
  return (true);
}

static const setStr createSetMethods() {
  setStr temp;
  temp.insert("GET");
  temp.insert("HEAD");
  temp.insert("POST");
  temp.insert("DELETE");
  return temp;
}

static size_t myAtoi(string &str, bool &succeed) {
  for (size_t i = 0; i < str.length(); i++) {
    if (!isdigit(str.c_str()[i])) {
      succeed = false;
      return (-1);
    }
  }
  succeed = true;
  return (atoi(str.c_str()));
}

void Server::_setMaxClientBody(vecStr words) {
  bool success;

  if (clientMaxBodySize > 0)
    throw ErrnoException("client_size already defined");
  if (words.size() != 2)
    throw ErrnoException("need client_size SIZE");
  clientMaxBodySize = myAtoi(words[1], success);
  if (!success)
    throw ErrnoException("wrong size for client_size");
  if (clientMaxBodySize == 0)
    clientMaxBodySize = std::numeric_limits<size_t>::max();
}

void Server::_setErrorPages(vecStr words) {
  std::pair<int, std::string> err;
  size_t res;
  bool success;

  if (words.size() != 3)
    throw ErrnoException("need error ERROR_NUM ERROR_PAGE");
  res = myAtoi(words[1], success);
  if (!success || res > 599)
    throw ErrnoException("invalid ERROR_NUM");
  err.first = res;
  if (!checkWordFormat(words[2]))
    throw ErrnoException("invalid ERROR_URL");
  err.second = words[2];
  errorPages.insert(err);
}

void Server::_setRoot(vecStr words) {
  if (!root.empty())
    throw ErrnoException("root already defined");
  if (words.size() != 2)
    throw ErrnoException("need \"root URI\"");
  if (!checkWordFormat(words[1]))
    throw ErrnoException("invalid URI for root");
  root = words[1];
  if (root[root.size() - 1] != '/')
    root += '/';
}

static bool checkHostFormat(const string &str) {
  vecStr addr;
  size_t n;
  bool success;

  splitPattern(addr, str, '.');
  if (addr.size() != 4)
    return (false);
  for (size_t i = 0; i < addr.size(); i++) {
    n = myAtoi(addr[i], success);
    if (!success || n > 255)
      return false;
  }
  return true;
}

void Server::_setListen(vecStr words) {
  vecStr addr;
  bool success;
  size_t res;

  if (!ipAddress.empty() || port > 0)
    throw ErrnoException("host and port already defined");
  if (words.size() < 2)
    throw ErrnoException("need listen HOST:PORT");
  splitPattern(addr, words[1], ':');
  if (addr.size() != 2)
    throw ErrnoException("need listen HOST:PORT");
  host.push_back(words[1]);
  if (addr[0] == "localhost")
    ipAddress = "127.0.0.1";
  else {
    if (!checkHostFormat(addr[0]))
      throw ErrnoException("wrong HOST format");
    ipAddress = addr[0];
  }
  res = myAtoi(addr[1], success);
  if (!success || res > 65535)
    throw ErrnoException("wrong PORT");
  port = res;
  host.push_back(ipAddress + ":" + addr[1]);
}

void Server::_setServerNames(vecStr words) {
  if (!names.empty())
    throw ErrnoException("server name already defined");
  if (words.size() < 2)
    throw ErrnoException("need at least one server name");
  for (vecStrIt it = words.begin() + 1; it != words.end(); ++it) {
    if (!checkWordFormat(*it))
      throw ErrnoException("unvalid SERVER_NAME " + *it);
    names.push_back(*it);
  }
}

void Server::_findMapServerSet(const vecStr &lines) {
  for (vecStr::const_iterator vecIt = lines.begin() + 1;
       vecIt != lines.end() - 1; ++vecIt) {
    vecStr words;
    splitPattern(words, *vecIt, ' ');
    mapServerSetIt it = mss.find(words.front());
    if (it == mss.end())
      throw ErrnoException("server unknown keyword \"" + words[0] + "\"");
    ((this->*(it->second))(words));
  }
}

void Server::checkDefault() {
  if (names.empty()) {
    names.push_back("localhost");
    names.push_back("localhost:2121");
    names.push_back("127.0.0.1:2121");
  }
  if (ipAddress.empty())
    ipAddress = "127.0.0.1";
  if (port == 0)
    port = 8080;
  if (root.empty())
    root = "www/default.com";
  if (clientMaxBodySize == 0)
    clientMaxBodySize = 1048576;
  if (locations.empty()) {
    Location loc;
    loc.checkDefault();
    locations[loc.path] = loc;
  }
}

void Server::parse(const string &bock) {
  vecStr locBlocks;
  vecStr serverInfo;
  if (!splitBlocks(locBlocks, bock, "location", serverInfo))
    throw ErrnoException("miss match brace { } in location block");
  _findMapServerSet(serverInfo);
  for (vecStr::iterator it = locBlocks.begin(); it != locBlocks.end(); ++it) {
    Location tmpLoc;
    tmpLoc.parse(*it);
    if (locations.find(tmpLoc.path) != locations.end())
      throw ErrnoException("2 same location path " + tmpLoc.path);
    locations[tmpLoc.path] = tmpLoc;
  }
  names.insert(names.begin(), host.begin(), host.end());
  checkDefault();
}

bool Server::isDefault() const { return defaultServer; }

Location *Server::getLocationByRessource(const string &path) {
  string tmpPath(path);
  while (!tmpPath.empty()) {
    mapStrLoc::iterator tmp = locations.find(tmpPath);
    if (tmp != locations.end())
      return &tmp->second;
    else
      tmpPath.pop_back();
  }
  return &defaultLocation;
}

Server::Server()
    : names(), defaultServer(false), host(), ipAddress(), port(), root(),
      errorPages(), clientMaxBodySize(), locations(), defaultLocation() {
  defaultLocation.checkDefault();
  mss["server_name"] = &Server::_setServerNames;
  mss["listen"] = &Server::_setListen;
  mss["root"] = &Server::_setRoot;
  mss["error_page"] = &Server::_setErrorPages;
  mss["client_max_body_size"] = &Server::_setMaxClientBody;
}

Server::Server(const Server &other)
    : mss(other.mss), names(other.names), defaultServer(other.defaultServer),
      host(other.host), ipAddress(other.ipAddress), port(other.port),
      root(other.root), errorPages(other.errorPages),
      clientMaxBodySize(other.clientMaxBodySize), locations(other.locations),
      defaultLocation(other.defaultLocation) {}

Server::~Server() {}

Server &Server::operator=(const Server &rhs) {
  if (this != &rhs) {
    mss = rhs.mss;
    names = rhs.names;
    defaultServer = rhs.defaultServer;
    host = rhs.host;
    ipAddress = rhs.ipAddress;
    port = rhs.port;
    root = rhs.root;
    errorPages = rhs.errorPages;
    clientMaxBodySize = rhs.clientMaxBodySize;
    locations = rhs.locations;
    defaultLocation = rhs.defaultLocation;
  }
  return *this;
}

void Location::_setCgiPath(vecStr words) {
  if (!cgiPath.empty())
    throw ErrnoException("cgi_path already defined");
  if (words.size() < 2)
    throw ErrnoException("need cgi_path value");
  for (vecStrIt i = words.begin() + 1; i != words.end(); ++i) {
    if (!checkWordFormat(*i))
      throw ErrnoException("invalid cgi_path");
    cgiPath.push_back(*i);
  }
}

void Location::_setCgiExtension(vecStr words) {
  if (!cgiExtension.empty())
    throw ErrnoException("cgi_extension already defined");
  if (words.size() < 2)
    throw ErrnoException("need cgi_extension value");
  for (vecStrIt i = words.begin() + 1; i != words.end(); ++i) {
    if (!checkWordFormat(*i))
      throw ErrnoException("invalid cgi_extension");
    cgiExtension.push_back(*i);
  }
}

void Location::_setUrlRedirection(vecStr words) {
  if (!uriReturn.empty())
    throw ErrnoException("return already defined");
  if (words.size() != 2)
    throw ErrnoException("need return REDIR_URL");
  if (!checkWordFormat(words[1]))
    throw ErrnoException("invalid REDIR_URL");
  uriReturn = words[1];
}

void Location::_setIndex(vecStr words) {
  if (!index.empty())
    throw ErrnoException("index already defined");
  if (words.size() < 2)
    throw ErrnoException("need at least one index page");
  if (!checkWordFormat(words[1]))
    throw ErrnoException("invalid INDEX");
  index = words[1];
}

void Location::_setAutoIndex(vecStr words) {
  if (words.size() != 2 || (words[1] != "on" && words[1] != "off"))
    throw ErrnoException("autoindex needs 'on' or 'off'");
  autoindex = (words[1] == "on");
}

void Location::_setMethods(vecStr words) {
  setStr strMethods = createSetMethods();
  if (!methods.empty())
    throw ErrnoException("methods already defined");
  if (words.size() < 2)
    throw ErrnoException("need at least one method");
  for (vecStrIt i = words.begin() + 1; i != words.end(); ++i) {
    if (strMethods.find(*i) != strMethods.end())
      methods.insert(*i);
    else
      throw ErrnoException("unknown method \"" + *i + "\"");
  }
}

void Location::_setRoot(vecStr words) {
  if (!root.empty())
    throw ErrnoException("root already defined");
  if (words.size() != 2)
    throw ErrnoException("need \"root URI\"");
  if (!checkWordFormat(words[1]))
    throw ErrnoException("invalid URI for root");
  root = words[1];
  if (root[root.size() - 1] != '/')
    root += '/';
}

void Location::_findMapLocationSet(const vecStr &lines) {
  for (vecStr::const_iterator vecIt = lines.begin() + 1;
       vecIt != lines.end() - 1; ++vecIt) {
    vecStr words;
    splitPattern(words, *vecIt, ' ');
    mapLocationSetIt it = mls.find(words.front());
    if (it == mls.end())
      throw ErrnoException("location unknown keyword \"" + words[0] + "\"");
    ((this->*(it->second))(words));
  }
}

static bool checkValidCgi(string &cgi) {
  if (cgi == "php")
    return true;
  throw ErrnoException("cgi extension " + cgi + " invalid");
}

static bool checkCgi(vecStr &path, vecStr &ext) {
  pair<vecStrIt, vecStrIt> p;
  for (p = make_pair(path.begin(), ext.begin());
       p.first != path.end() && p.second != ext.end(); ++p.first, ++p.second) {
    if (p.first->length() < p.second->length() ||
        p.first->substr(p.first->length() - p.second->length()) != *p.second ||
        !isFile(*p.first) || !checkPermissionX(*p.first) ||
        !checkValidCgi(*p.second)) {
      return false;
    }
  }
  return true;
}

void Location::checkDefault() {
  if (path.empty())
    path = "/";
  if (methods.empty())
    methods = createSetMethods();
  if (index.empty())
    index = "index.html";
  if (cgiExtension.size() != cgiPath.size())
    throw ErrnoException("cgi need path and extention ");
  if (!checkCgi(cgiPath, cgiExtension))
    throw ErrnoException("cgi path or extension invalid");
}

bool Location::_setPath(const string &str) {
  vecStr words;

  splitPattern(words, str, ' ');
  if (words.size() != 3 || words[2] != "{" || !checkWordFormat(words[1]))
    return (false);
  path = words[1];
  return true;
}

void Location::parse(const string &bock) {
  vecStr block;
  vecStr locationInfo;
  splitBlocks(block, bock, "error", locationInfo);
  if (!_setPath(locationInfo[0])) {
    throw ErrnoException(
        "Location block wrong definition [expected] location path {}");
  }
  _findMapLocationSet(locationInfo);
  checkDefault();
}
string Location::getCgiPath(const string &ext) {
  vecStrIt it = find(cgiExtension.begin(), cgiExtension.end(), ext);
  if (it != cgiExtension.end())
    return cgiPath[it - cgiExtension.begin()];
  return "";
}

bool Location::isCgi() { return !cgiPath.empty() && !cgiExtension.empty(); }

Location::Location()
    : path(), root(), methods(), autoindex(false), index(), cgiExtension(),
      cgiPath() {
  mls["methods"] = &Location::_setMethods;
  mls["root"] = &Location::_setRoot;
  mls["autoindex"] = &Location::_setAutoIndex;
  mls["index"] = &Location::_setIndex;
  mls["return"] = &Location::_setUrlRedirection;
  mls["cgi_extension"] = &Location::_setCgiExtension;
  mls["cgi_path"] = &Location::_setCgiPath;
}

Location::Location(const Location &other)
    : mls(other.mls), path(other.path), root(other.root),
      methods(other.methods), autoindex(other.autoindex), index(other.index),
      cgiExtension(other.cgiExtension), cgiPath(other.cgiPath) {}

Location::~Location() {}

Location &Location::operator=(const Location &rhs) {
  if (this != &rhs) {
    mls = rhs.mls;
    path = rhs.path;
    root = rhs.root;
    methods = rhs.methods;
    autoindex = rhs.autoindex;
    index = rhs.index;
    uriReturn = rhs.uriReturn;
    cgiExtension = rhs.cgiExtension;
    cgiPath = rhs.cgiPath;
  }
  return *this;
}

Configuration::Configuration() {}

Configuration &Configuration::operator=(const Configuration &other) {
  this->_servers = other._servers;
  return (*this);
}

Configuration::~Configuration() {}

static bool checkSameName(vecStr &left, vecStr &right) {
  for (vecStrIt itLeft = left.begin(); itLeft != left.end(); ++itLeft) {
    for (vecStrIt itRight = right.begin(); itRight != right.end(); ++itRight) {
      if (*itLeft == *itRight)
        return false;
    }
  }
  return true;
}

static bool checkSameServer(vecServ &servers) {
  for (vecServIt its = servers.begin(); its != servers.end(); ++its) {
    for (vecServIt it = its + 1; it != servers.end(); ++it) {
      if (its->port == it->port && its->host == it->host &&
          !checkSameName(its->names, it->names))
        return false;
    }
  }
  return true;
}

static void verifyDefaultServer(vecServ &servers) {
  for (vecServIt i = servers.begin(); i != servers.end(); ++i) {
    if (checkVectorContain<std::string>(i->names, "default_server").first) {
      i->defaultServer = true;
      rotate(servers.begin(), i, i + 1);
      return;
    }
  }
  servers.begin()->names.push_back("default_server");
  servers.begin()->defaultServer = true;
}

void Configuration::parseConfig(const string &pathFile) {
  string fileString;
  vecStr serverBlocks;
  vecStr configInfo;

  if (!readFile(pathFile, fileString))
    throw ErrnoException("Fail to open file");
  if (!splitBlocks(serverBlocks, fileString, "server", configInfo))
    throw ErrnoException("matching { } issues in a server block");
  if (!configInfo.empty())
    throw ErrnoException("not only server blocks");
  for (vecStr::iterator it = serverBlocks.begin(); it != serverBlocks.end();
       ++it) {
    _servers.push_back(Server());
    _servers.back().parse(*it);
  }
  if (_servers.empty()) {
    throw ErrnoException("no server config");
  } else {
    if (!checkSameServer(_servers))
      throw ErrnoException("2 same listen");
    verifyDefaultServer(_servers);
  }
}

vecServ &Configuration::getServers() { return _servers; }
