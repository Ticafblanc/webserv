//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_CONFIGURATION_HPP
#define WEBSERV_CONFIGURATION_HPP

#include "2-parser.hpp"

struct Location {
  typedef void (Location::*locationSet)(vecStr words);
  typedef map<string, locationSet> mapLocationSet;
  typedef mapLocationSet::iterator mapLocationSetIt;

  mapLocationSet mls;
  string path;
  string root;
  setStr methods;
  bool autoindex;
  string index;
  string uriReturn;
  vecStr cgiExtension;
  vecStr cgiPath;
  Location();
  Location(const Location& other);
  ~Location();

  Location &operator=(const Location& rhs);
  void parse(const string &block);
  void checkDefault();
  bool isCgi();

private:
  bool _setPath(const string &str) ;
  void _findMapLocationSet(const vecStr &lines);
  void _setMethods(vecStr words);
  void _setRoot(vecStr words);
  void _setAutoIndex(vecStr words);
  void _setIndex(vecStr words);
  void _setUrlRedirection(vecStr words);
  void _setCgiExtension(vecStr words);
  void _setCgiPath(vecStr words);
};


typedef map<string, Location> mapStrLoc;

struct Server {
  typedef void (Server::*serverSet)(vecStr words);
  typedef map<string, serverSet> mapServerSet;
  typedef mapServerSet::iterator mapServerSetIt;
  mapServerSet mss;
  vecStr names;
  bool defaultServer;
  vecStr host;
  string ipAddress;
  uint16_t port;
  string root;
  mapIntStr errorPages;
  size_t clientMaxBodySize;
  mapStrLoc locations;
  Location defaultLocation;
  Server();
  Server(const Server& other);
  ~Server();

  Server &operator=(const Server& rhs);
  void parse(const string &block);
  void checkDefault();
  bool isDefault() const;
  Location *getLocationByRessource(const string &ressource) ;

private:
  void _findMapServerSet(const vecStr &lines);
  void _setServerNames(vecStr words);
  void _setListen(vecStr words);
  void _setRoot(vecStr words);
  void _setErrorPages(vecStr words);
  void _setMaxClientBody(vecStr words);
};

typedef vector<Server> vecServ;
typedef vecServ::iterator vecServIt;

class Configuration {

public:
  Configuration();
  Configuration &operator=(const Configuration &other);
  ~Configuration();

  /**
   * Parse a file into the current configuration object.
   * @throw Configuration::ParsingException
   * @param file path to the file to parse
   */
  void parseConfig(const string &file);

  /**
   * Get servers configuration
   * @return servers configurations
   */
  vecServ &getServers();

private:
  vecServ _servers;

};

#endif // WEBSERV_CONFIGURATION_HPP
