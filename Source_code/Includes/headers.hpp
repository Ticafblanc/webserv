//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_HEADERS_HPP
#define WEBSERV_HEADERS_HPP

#include "parser.hpp"
#include "utils.hpp"


class Headers {
public:
  struct request_line {
    string _method;
    string _request_target;
    string _http_version;
  };

  struct status_line {
    string _http_version;
    int _status_code;
    string _reason_phrase;
  };

  struct header_field {
    string _field_name;
    string _field_value;
  };

private:
  struct request_line _request_line;
  struct status_line _status_line;
  vector<struct header_field> _header_fields;
  bool _is_request;
  string _client_ip;
  string _content;
  string _raw_request;

  /**
 *  @brief Split the block in a vector of line.
 *
 *  @param msg the block to split.
 *  @param lines the vector. Can be a reference in the futur.
   */
  void getLines(string msg, vector<string> *lines);

  /**
 *  @brief Parse a request line. (start line)
 *  Like the it's a start line, the getted line is the
 *  first of the header.
 *
 *  @param lines the lines of the header.
   */
  void getRequestLine(vector<string> lines);

  /**
 *  @brief Parse a status line. (start line)
 *  Like the it's a start line, the getted line is the
 *  first of the header.
 *
 *  @param lines the lines of the header.
   */
  void getStatusLine(vector<string> lines);

  /**
 *  @brief Parse a line from the headers block that
 *  isn't the first. Set this in a structure containing
 *  the field name and the field value.
 *
 *  @param lines the lines of the header.
   */
  int getHeaderFileds(vector<string> lines);

public:
  Headers(const string &request, const string &client_ip,
               int content_type);
  Headers(const Headers &copy);
  ~Headers();
  Headers &operator=(const Headers &op);

  bool isRequest(void) const;
  void pushContent(string buffer);

  struct request_line getRequestLine(void) const;
  struct status_line getStatusLine(void) const;
  vector<struct header_field> getHeaderFields(void) const;
  string getContent(void) const;

  /**
 * Get client IP
 * @return the string representation of the client IP
   */
  string getClientIP(void) const;

  /**
 * Get the string plain request.
 * @return the string representation of the request received.
   */
  string getPlainRequest(void) const;
};

ostream &operator<<(ostream &out, const Headers &hb);

#endif // WEBSERV_HEADERS_HPP
