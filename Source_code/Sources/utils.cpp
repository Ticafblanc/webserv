//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/utils.hpp"

void throwError(const exception& ex)
{
  cerr << "\033[1m\033[31mERROR \033[0m: " << ex.what() << '\n';
}

void printError(const string& msg)
{
  cerr << "\033[1m\033[31mERROR \033[0m: " << msg << '\n';
}

int treat(int sd, Headers &header_block, Configuration::server server_conf)
{
  (void)sd;
  (void)header_block;
  (void)server_conf;
//  string response = Request(header_block, server_conf).getResponse();
//
//  Log("Send response to : " + itoa(sd));
//  int	rc = write(sd, response.c_str(), response.size());
//  DEBUG("END SEND");
//  if (rc <= 0)
//  {
//    Log("Error or connection close on : " + itoa(sd));
//    return (-1);
//  }
  return (0);
}

void endServer(int signal)
{
  (void)signal;
  //  server.closeServer();
  Log("Ending server...");
  exit(0);
}
