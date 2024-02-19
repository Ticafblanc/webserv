//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#ifndef WEBSERVER_LISTEN_HPP
#define WEBSERVER_LISTEN_HPP

#include "../../4-Config/Includes/Config.hpp"

class Listen {

  /*>****************************public section********************************/

public:
  /*
   *============================================================================
   *|                            Member Fonction
   *============================================================================
   */

  /**
   * Constructor of configServer.class class
   *
   * Listen(8-ConfigFile& config);
   *
   * @param   input is a string reference extract befor;
   * @param   config is config webserv reference
   * @throw   none
   **/
  Listen(Config &config, Config &configBase);

  /**
   * Destructor of Listen.class class
   *
   * Listen*
   * @throw   none
   **/
  ~Listen();

  /**
   * Constructor of configServer.class class
   *
   * Listen(const Listen & Listen);
   *
   * @param   listenData &
   * @throw   none
   **/
  Listen(const Listen &);

  /**
   * Destructor of Listen.class class
   *
   *  Listen& operator=(const Listen& Listen);
   *
   * @param   listenData&
   * @throw   none
   **/
  Listen &operator=(const Listen &);

  /*
   *============================================================================
   *|                             Element access
   *============================================================================
   */

  /**
   * Public methode of Listen.class class
   *
   * std::string parseListenData();
   *
   * @returns     std::vector<std::string>& contain all names of serverSocket
   * @param       void
   * @throw       none
   */
  string parseListenData(const string &input);

  /**
   * private function of config_webserv.class
   *
   * check if the _input member is valid
   * is a valid ip address.
   *
   * @return std::string of an error message
   * @param none
   * @throws none
   */
  string check_input();

  /**
   * private function of config_webserv.class
   *
   * check if the ip address pass in the function
   * is a valid ip address.
   *
   * @return none
   * @param ip_address is a stringstream, error is a string for the error
   * message if an error occur
   * @throws none
   */
  void check_ip(string, string &);

  /**
   * private function of config_webserv.class
   *
   * check if the ip address pass in the function
   * is a valid ip address.
   *
   * @return none
   * @param port is a stringstream, error is a string for the error message if
   * an error occur
   * @throws none
   */
  void check_port(string, string &);

  /*>***************************private section********************************/

private:
  /*
   *============================================================================
   *|                           Member
   *============================================================================
   */

  Config &_config;
  Config &_configBase;
  stringstream _input;
  string _ipAddress;
  int _port;
};

#endif // WEBSERVER_LISTEN_HPP
