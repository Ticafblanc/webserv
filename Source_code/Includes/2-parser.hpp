//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_PARSER_HPP
#define WEBSERV_PARSER_HPP

#include "1-utils.hpp"

bool splitBlocks(vecStr &split, const string &str, const string &pattern,
                 vecStr &otherInfo);
void splitPattern(vecStr &split, const string &str, const char &pattern);

bool readFile(const string &file, string &fileString);

bool checkWordFormat(const string &str);

string readFile(string file);


//class ParsingException : public exception {
//private:
//  string _msg;
//
//public:
//  ParsingException(int line = 0,
//                   string msg = "Unable to parse the given config file.")
//      : _msg("Line: " + uIntegerToString(line + 1) + ": " + msg){};
//  ~ParsingException() throw(){};
//  const char *what() const throw() { return (_msg.c_str()); };
//};

#endif // WEBSERV_PARSER_HPP
