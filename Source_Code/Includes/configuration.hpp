//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_CONFIGURATION_HPP
#define WEBSERV_CONFIGURATION_HPP

#include "parser.hpp"

class Configuration {
public:
  struct location {
    string name;
    string root;
    vecStr methods;
    bool autoindex;
    string index;
    vecStr cgi_extension;
    string cgi_path;
    bool upload_enable;
    string upload_path;
    size_t client_max_body_size;
//    location();
  };

  struct server {
    vecStr names;
    string host;
    string root;
    mapIntStr error_pages;
    vector<location> locations;
    size_t port;
//    server();
  };

  Configuration(void);
  Configuration(std::string file);
  Configuration &operator=(const Configuration &other);
  ~Configuration(void);

  /**
   * Get servers configuration
   * @return servers configurations
   */
  std::vector<server> getServers(void);

  /**
   * Prints an entire configuration to ensure parsing is good
   */
  void print(void);

private:
  vector<server> _servers;

  /**
   * Parse a file into the current configuration object.
   * @throw Configuration::ParsingException
   * @param file path to the file to parse
   */
  void _parseConfig(string file);

  /**
   * Add a server structure based on lines given
   * @param source the config string
   * @param line_start the line where server definition starts, aka "server {"
   * @param line_end the line where server definition ends, aka "}"
   */
  void _parseServer(string source, size_t line_start, size_t line_end);

  /**
   * Takes a line containing a property, and set the right property of s
   * @param source the config string
   * @param line the line of the property
   * @param s reference to the server to edit property to
   */
  void _parseServerProperty(string source, size_t line, server &s);

  /**
   * Takes a line with a location property, and set it to the given l location
   * struct
   * @param source the config string
   * @param line the line to read the property from
   * @param l a reference to the location struct to edit
   */
  void _parseLocationProperty(string source, size_t line, location &l);

  /**
   * Check if the parsed configuration is correct.
   * @throw ParsingException if the config is not valid.
   */
  void _validateConfig();

  /**
   * If the config is valid but incomplete, we add default values.
   */
  void _completeConfig();

  /**
   * Get the default server configuration
   * @return the default server struct
   */
  server _defaultServer();

  /**
   * Get the default location configuration
   * @return the default location struct
   */
  location _defaultLocation();

  /**
   * Return a location based on the given string
   * @param source the config string
   * @param line_start the line where location definition starts, aka "location
   * /
   * {"
   * @param line_end the line where location definition ends, aka "}"
   * @return a location struct based on configuration given
   */
  location _parseLocation(string source, size_t line_start, size_t line_end);

public:
};

#endif // WEBSERV_CONFIGURATION_HPP
