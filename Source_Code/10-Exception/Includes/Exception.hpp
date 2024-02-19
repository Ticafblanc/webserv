//
// Created by Matthis DoQuocBao on 2023-06-05.
//

#ifndef WEBSERVER_EXCEPTION_HPP
#define WEBSERVER_EXCEPTION_HPP

#include "../../40-Utils/Includes/Utils.hpp"

class Exception : public std::exception {

  /*>*******************************private
   * section**********************************/

private:
  /*
   *====================================================================================
   *|                                       Member |
   *====================================================================================
   */

  std::string _message;
  int _code;

  /*>********************************public
   * section**********************************/

public:
  /*
   *====================================================================================
   *|                                      Fonction |
   *====================================================================================
   */

public:
  /**
   * Constructor of Exception class
   *
   * Exception(const char * message, int statusCode);
   *
   * @param   Log is a LogSocket reference to set the private _Log
   *          to manage the close of LogSocket class
   *          message to store const char*
   * @throw   none
   **/
  Exception(const char *message, int code);

  /**
   * Copy constructor of Exception class
   *
   * Exception(Exception &);
   *
   * @param   Exception instance to build the Exception
   *          Log_socket in an int to close
   * @throw   none
   **/
  Exception(const Exception &) throw();

  /**
   * Operator overload= of Exception class
   *
   * operator=(const Exception&);
   *
   * @param   Exception instance const to copy the Exception
   * @throw   none
   **/
  Exception &operator=(const Exception &);

  /**
   * Destructor of Exception class
   *
   * virtual ~Exception() throw();
   *
   * @throw   none
   **/
  virtual ~Exception() throw();

  /**
   * Public methode of Exception
   *
   * virtual const char * what() const throw();
   *
   * @returns  const char * store in private std::string _message
   *          at the construction defaut constructor "7-Socket error"
   * @param   void
   * @throw   none
   **/
  virtual const char *what() const throw();

  int getCode() const;
};

#endif // WEBSERVER_EXCEPTION_HPP
