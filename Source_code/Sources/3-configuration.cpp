//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/3-configuration.hpp"

static const setStr createSetMethods() {
  setStr temp;
  temp.insert("GET");
  temp.insert("HEAD");
  temp.insert("POST");
  temp.insert("PUT");
  temp.insert("DELETE");
  temp.insert("CONNECT");
  temp.insert("OPTIONS");
  temp.insert("TRACE");
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
    throw throwMessage("client_size already defined");
  if (words.size() != 2)
    throw throwMessage("need client_size SIZE");
  clientMaxBodySize = myAtoi(words[1], success);
  if (!success)
    throw throwMessage("wrong size for client_size");
  if (clientMaxBodySize == 0)
    clientMaxBodySize = std::numeric_limits<size_t>::max();
}

void Server::_setErrorPages(vecStr words) {
  std::pair<int, std::string> err;
  size_t res;
  bool success;

  if (words.size() != 3)
    throw throwMessage("need error ERROR_NUM ERROR_PAGE");
  res = myAtoi(words[1], success);
  if (!success || res > 599)
    throw throwMessage("invalid ERROR_NUM");
  err.first = res;
  if (!checkWordFormat(words[2]))
    throw throwMessage("invalid ERROR_URL");
  err.second = words[2];
  errorPages.insert(err);
}

void Server::_setRoot(vecStr words) {
  if (!root.empty())
    throw throwMessage("root already defined");
  if (words.size() != 2)
    throw throwMessage("need \"root PATH\"");
  if (!checkWordFormat(words[1]))
    throw throwMessage("invalid PATH for root");
  root = words[1];
  if (root[root.size() - 1] == '/')
    root = root.substr(0, root.size() - 1);
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

  if (!host.empty() || port > 0)
    throw throwMessage("host and port already defined");
  if (words.size() < 2)
    throw throwMessage("need listen HOST:PORT");
  splitPattern(addr, words[1], ':');
  if (addr.size() != 2 || addr.size() != 1)
    throw throwMessage("need listen HOST:PORT");
  if (addr.size() == 2 && addr[0] == "localhost")
    host = "127.0.0.1";
  else {
    if (!checkHostFormat(addr[0]))
      throw throwMessage("wrong HOST format");
    host = addr[0];
  }
  res = myAtoi(addr[1], success);
  if (!success || res > 65535)
    throw throwMessage("wrong PORT");
  port = res;
}

void Server::_setServerNames(vecStr words) {
  if (!names.empty())
    throw throwMessage("server name already defined");
  if (words.size() < 2)
    throw throwMessage("need at least one server name");
  for (vecStrIt it = words.begin() + 1; it != words.end(); ++it) {
    if (!checkWordFormat(*it))
      throw throwMessage("unvalid SERVER_NAME " + *it);
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
      throw throwMessage("server unknown keyword \"" + words[0] + "\"");
    ((this->*(it->second))(words));
  }
}

void Server::checkDefault() {
  if (names.empty())
    names.push_back("localhost");
  if (host.empty())
    host = "127.0.0.1";
  if (port == 0)
    port = 80;
  if (root.empty())
    root = "/";
  if (clientMaxBodySize == 0)
    clientMaxBodySize = 1048576;
  if (locations.empty()) {
    locations.push_back(Location());
    locations.back().checkDefault();
  }
}

void Server::parse(const string &bock) {
  vecStr locBlocks;
  vecStr serverInfo;
  if (!splitBlocks(locBlocks, bock, "location", serverInfo))
    throw throwMessage("miss match brace { } in location block");
  _findMapServerSet(serverInfo);
  for (vecStr::iterator it = locBlocks.begin(); it != locBlocks.end(); ++it) {
    locations.push_back(Location());
    locations.back().parse(*it);
    if (locations.back().root.empty())
      locations.back().root = root;
  }
  checkDefault();
}

bool Server::isDefault() const { return defaultServer; }

Server::Server()
    : names(), defaultServer(false), host(), port(), root(), errorPages(),
      clientMaxBodySize(), locations() {
  mss["server_name"] = &Server::_setServerNames;
  mss["listen"] = &Server::_setListen;
  mss["root"] = &Server::_setRoot;
  mss["error_page"] = &Server::_setErrorPages;
  mss["client_max_body_size"] = &Server::_setMaxClientBody;
}

Server::Server(const Server &other)
    : mss(other.mss), names(other.names), defaultServer(other.defaultServer),
      host(other.host), port(other.port), root(other.root),
      errorPages(other.errorPages), clientMaxBodySize(other.clientMaxBodySize),
      locations(other.locations) {}

Server::~Server() {}

Server &Server::operator=(const Server &rhs) {
  if (this != &rhs) {
    mss = rhs.mss;
    names = rhs.names;
    defaultServer = rhs.defaultServer;
    host = rhs.host;
    port = rhs.port;
    root = rhs.root;
    errorPages = rhs.errorPages;
    clientMaxBodySize = rhs.clientMaxBodySize;
    locations = rhs.locations;
  }
  return *this;
}

void Location::_setCgiPath(vecStr words) {
  if (!cgiPath.empty())
    throw throwMessage("cgi_path already defined");
  if (words.size() != 2)
    throw throwMessage("need cgi_path value");
  if (!checkWordFormat(words[1]))
    throw throwMessage("invalid cgi_path");
  cgiPath = words[1];
}

void Location::_setCgiExtension(vecStr words) {
  if (!cgiExtension.empty())
    throw throwMessage("cgi_extension already defined");
  if (words.size() < 2)
    throw throwMessage("need cgi_extension value");
  for (vecStrIt i = words.begin() + 1; i != words.end(); ++i) {
    if (!checkWordFormat(*i))
      throw throwMessage("invalid cgi_extension");
    cgiExtension.push_back(*i);
  }
}

void Location::_setUrlRedirection(vecStr words) {
  if (!uriReturn.empty())
    throw throwMessage("return already defined");
  if (words.size() != 2)
    throw throwMessage("need return REDIR_URL");
  if (!checkWordFormat(words[1]))
    throw throwMessage("invalid REDIR_URL");
  uriReturn = words[1];
}

void Location::_setIndex(vecStr words) {
  if (!index.empty())
    throw throwMessage("index already defined");
  if (words.size() < 2)
    throw throwMessage("need at least one index page");
  for (size_t i = 1; i < words.size(); i++) {
    if (!checkWordFormat(words[i]))
      throw throwMessage("invalid INDEX");
    index = words[i];
  }
}

void Location::_setAutoIndex(vecStr words) {
  if (words.size() != 2 || (words[1] != "on" && words[1] != "off"))
    throw throwMessage("autoindex needs 'on' or 'off'");
  autoindex = (words[1] == "on");
}

void Location::_setMethods(vecStr words) {
  setStr strMethods = createSetMethods();
  if (!methods.empty())
    throw throwMessage("methods already defined");
  if (words.size() < 2)
    throw throwMessage("need at least one method");
  for (vecStrIt i = words.begin() + 1; i != words.end(); ++i) {
    if (strMethods.find(*i) != strMethods.end())
      methods.insert(*i);
    else
      throw throwMessage("unknown method \"" + *i + "\"");
  }
}

void Location::_setRoot(vecStr words) {
  if (!root.empty())
    throw throwMessage("root already defined");
  if (words.size() != 2)
    throw throwMessage("need \"root PATH\"");
  if (!checkWordFormat(words[1]))
    throw throwMessage("invalid PATH for root");
  root = words[1];
  if (root[root.size() - 1] == '/')
    root = root.substr(0, root.size() - 1);
}

void Location::_findMapLocationSet(const vecStr &lines) {
  for (vecStr::const_iterator vecIt = lines.begin() + 1;
       vecIt != lines.end() - 1; ++vecIt) {
    vecStr words;
    splitPattern(words, *vecIt, ' ');
    mapLocationSetIt it = mls.find(words.front());
    if (it == mls.end())
      throw throwMessage("location unknown keyword \"" + words[0] + "\"");
    ((this->*(it->second))(words));
  }
}

void Location::checkDefault() {
  if (path.empty())
    path = "/";
  if (methods.empty())
    methods = createSetMethods();
  if (index.empty())
    index = "index.html";
  if (!cgiExtension.empty() || !cgiPath.empty()) {
    if (cgiExtension.empty() || cgiPath.empty())
      throw throwMessage("cgi need path and extention ");
    if (!isExecutablePath(cgiPath, cgiExtension.front()))
      throw throwMessage("cgi path or extension invalid");
  }
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
    throw throwMessage(
        "Location block wrong definition [expected] location path {}");
  }
  _findMapLocationSet(locationInfo);
  checkDefault();
}

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
    throw throwMessage("Fail to open file");
  if (!splitBlocks(serverBlocks, fileString, "server", configInfo))
    throw throwMessage("matching { } issues in a server block");
  if (!configInfo.empty())
    throw throwMessage("not only server blocks");
  for (vecStr::iterator it = serverBlocks.begin(); it != serverBlocks.end();
       ++it) {
    _servers.push_back(Server());
    _servers.back().parse(*it);
  }
  if (_servers.empty()) {
    _servers.push_back(Server());
    _servers.back().checkDefault();
    _servers.back().names.push_back("default_server");
  } else {
    if (!checkSameServer(_servers))
      throw throwMessage("2 same listen");
    verifyDefaultServer(_servers);
  }
}

vecServ &Configuration::getServers() { return _servers; }
