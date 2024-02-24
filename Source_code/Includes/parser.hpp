//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_PARSER_HPP
#define WEBSERV_PARSER_HPP

#include "utils.hpp"

bool splitBlocks(vecStr &split, const string &str, const string &pattern,
                 vecStr &otherInfo);
void splitPattern(vecStr &split, const string &str, const char &pattern);

bool readFile(const string &file, string &fileString);

bool checkWordFormat(const string &str);

//static const char *server_properties[] = {"listen", "server_name", "error_page",
//                                          "root", 0};
//
//static const char *route_properties[] = {"method",
//                                         "root",
//                                         "autoindex",
//                                         "index",
//                                         "cgi_extension",
//                                         "cgi_path",
//                                         "upload_enable",
//                                         "upload_path",
//                                         "client_max_body_size",
//                                         0};

string readFile(string file);
bool isExecutablePath(const string& path, const string& extension) ;


/**
 * Count the number of lines in a string.
 * @param source the config string
 * @return the number of lines
 */
size_t countLines(string source);

/**
 * Get the string inner the curly braces pair starting at given line.
 *
 * @throw ParsingException if the brackets are not closed
 * @param source the string to process
 * @param line the line where curly brackets opens
 * @return the line where the curly brackets ends
 * @example "server {\na\nb\nc\n}" with line 0 will return line 4
 */
size_t getClosingBracket(string source, size_t line);

/**
 * Check if a server or route property is well formated, valid, and then splits
 * it in args
 * @param source the config string
 * @param line the line to parse
 * @param object should be either "server" or "route"
 * @return a vector of values, first is the key
 * @throw ParsingException if the property isn't valid
 * @example "listen 80 localhost;" will return a vector of 3 -> "listen", "80"
 * and "localhost"
 */
vector<string> parseProperty(string source, size_t line, string object);

/**
 * Splits a string by whitespaces
 * @param str the string to split
 * @return a vector of strings
 */
vector<string> splitWhitespace(string source);

/**
 * Check if the property name is inside the given properties name list
 * @param name the property name
 * @param valid_propeties the list of valid properties name
 * @return wether the name is valid or not
 * @example "listen" in {"server_name", "listen", 0} will return true
 * @example "hello" in {"server_name", "listen", 0} will return false
 */
bool isPropertyNameValid(string name, const char **valid_names);

/**
 * Reads a file into a std::vector of unsigned char
 * @throw ParsingException if the file does not exists
 * @param file the file to read
 * @return a string containing the file content
 */
vector<unsigned char> readBinaryFile(string file);
string itoa(int n);

/**
 * Get the n-th line of source, without whitespaces before and after
 * @param source the config string
 * @param n the wanted line
 * @return the n-th line
 */
string getLine(string, size_t line);

/**
 * Check if the line is skippable (empty line or starting with #)
 * @param source the config string
 * @param line the line to check
 * @return wether we want to skip the line or not
 */
bool isSkippable(istringstream &line);

/**
 * Does the given line in source has a '{' as last char
 * @param source the config string
 * @param line the line to check
 * @return wether the lines ends with '{'
 */
bool endsWithOpenBracket(string source, size_t line);

/**
 * Converts a string to an integer, check if it's positive.
 * @param param the string to parse
 * @param line the line where the param occurs
 * @return the integer representation of the param
 * @throw ParsingExecption if the string doesn't represent a positive integer
 */
size_t uIntegerParam(string param, size_t line);

/**
 * Converts a "on"/"off" string into a bool
 * @param param the param to convert
 * @param line the line where the param occurs
 * @throw ParsingException if the param isn't "on" or "off"
 * @return the boolean value of the string
 */
bool boolParam(string param, size_t line);

/**
 * Check if a given method exists
 * @param method the method to check
 * @return wether the method given is valid or not
 */
bool isMethodValid(string method);

/**
 * Converts a size_t in std::string
 * @param n the size_t to convert
 * @return the std::string representation of n
 */
string uIntegerToString(size_t value);

/**
 * Replace all occurences in a std::string
 * @param source the string to replace from
 * @param to_replace the string to replace
 * @param new_value the value to replace by
 * @return the processed string
 */
string replace(string source, string to_replace, string new_value);

/**
 * Check if a path is non-existent, a file, or a directory, and get its
 * last-modified date
 * @param path the path to check
 * @param file_date a time_t value that will be set to the date of modification
 * of the file
 * @return 0 if the path is non-existant, 1 if the path is a file, 2 if the path
 * is a directory
 */
int pathType(string path, time_t *file_date);

class ParsingException : public exception {
private:
  string _msg;

public:
  ParsingException(int line = 0,
                   string msg = "Unable to parse the given config file.")
      : _msg("Line: " + uIntegerToString(line + 1) + ": " + msg){};
  ~ParsingException() throw(){};
  const char *what() const throw() { return (_msg.c_str()); };
};

#endif // WEBSERV_PARSER_HPP
