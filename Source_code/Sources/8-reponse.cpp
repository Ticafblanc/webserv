//
// Created by Matthis DoQuocBao on 2024-02-25.
//

#include "../Includes/8-reponse.hpp"
// static std::string alpha =
//     "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
// static std::string digit = "0123456789";

// static bool isValidReasonPhrase(std::string reason_phrase) {
//   if (reason_phrase.length() == 0)
//     return (false);
//   for (size_t i = 0; i < reason_phrase.length(); i++)
//     if (reason_phrase[i] != '\t' && reason_phrase[i] != ' ' &&
//         !((unsigned long)reason_phrase[i] >= (unsigned long)20 &&
//           (unsigned long)reason_phrase[i] <= (unsigned long)126))
//       return (false);
//   return (true);
// }

// static bool isValidStatusCode(std::string status_code) {
//   if (status_code.length() != 3)
//     return (false);
//   for (size_t cur = 0; cur < status_code.length(); cur++)
//     if (digit.find(status_code[cur]) == std::string::npos)
//       return (false);
//   return (true);
// }

// static bool isValidToken(std::string token) {
//   std::string vchars = "!#$%&'*+-.^_`|~" + digit + alpha;
//
//   if (token.length() == 0)
//     return (false);
//   for (size_t cur = 0; cur < token.length(); cur++)
//     if (vchars.find(token[cur]) == std::string::npos)
//       return (false);
//   return (true);
// }

// void Headers::getLines(std::string msg, std::vector<std::string> *lines) {
//   size_t start = 0;
//   size_t end = msg.find("\n");
//   while (end != std::string::npos) {
//     (*lines).push_back(msg.substr(start, end - start));
//     start = end + 1;
//     end = msg.find("\n", start);
//   }
//   (*lines).push_back(msg.substr(start, end - start));
// }

// void Headers::getRequestLine(std::vector<std::string> lines) {
//  Method
//  this->_request_line._method = lines[0].substr(0, lines[0].find(' '));
//  if (isValidToken(this->_request_line._method) == false)
//    throw(Exception("Request line not well formated (method)."));
//  lines[0].erase(0, this->_request_line._method.length() + 1);
//
//  // Request Target
//  this->_request_line._request_target = lines[0].substr(0, lines[0].find('
//  ')); lines[0].erase(0, this->_request_line._request_target.length() + 1);
//
//  // HTTP-version
//  if (lines[0].find('\r') != std::string::npos)
//    this->_request_line._http_version = lines[0].substr(0,
//    lines[0].find('\r'));
//  else if (lines[0].find('\n') != std::string::npos)
//    this->_request_line._http_version = lines[0].substr(0,
//    lines[0].find('\n'));
//  else
//    this->_request_line._http_version = lines[0].substr(0, lines[0].find('
//    '));
//  if (isValidHTTPVersion(this->_request_line._http_version) == false)
//    throw(Exception("Request line not well formated (http version) : " +
//                       this->_request_line._http_version));
//  this->_is_request = true;
//}
//
// void Headers::getStatusLine(std::vector<std::string> lines) {
//  std::string first_word = lines[0].substr(0, lines[0].find(" "));
//  std::string tmp;
//
//  // HTTP-version
//  this->_status_line._http_version = first_word;
//  if (isValidHTTPVersion(this->_status_line._http_version) == false)
//    throw(Exception("Status line not well formated (http_version)."));
//  lines[0].erase(0, first_word.length() + 1);
//
//  // Status code
//  tmp = lines[0].substr(0, lines[0].find(" "));
//  if (isValidStatusCode(tmp) == false)
//    throw(Exception("Status line not well formated (status code)."));
//  this->_status_line._status_code = std::atoi(tmp.c_str());
//  lines[0].erase(0, tmp.length() + 1);
//
//  // Reason phrase
//  if (lines[0].find('\r') != std::string::npos)
//    this->_request_line._http_version = lines[0].substr(0,
//    lines[0].find('\r'));
//  else if (lines[0].find('\n') != std::string::npos)
//    this->_request_line._http_version = lines[0].substr(0,
//    lines[0].find('\n'));
//  else
//    this->_request_line._http_version = lines[0].substr(0, lines[0].find('
//    '));
//  this->_status_line._reason_phrase = lines[0].substr(0, lines[0].find(' '));
//  if (isValidReasonPhrase(this->_status_line._reason_phrase) == false)
//    throw(Exception("Status line not well formated (reason phrase)."));
//
//  this->_is_request = false;
//}

// int Headers::getHeaderFileds(std::vector<std::string> lines) {
//   size_t i = 1;
//
//   size_t lines_size = lines.size();
//   for (i = 1; i < lines_size; i++) {
//     struct header_field field;
//     size_t posin;
//
//     DEBUG("CHECKED = " << lines[i]);
//
//      Empty
//     if (lines[i] == "\r" || lines[i].length() == 0)
//       return (i);
//
//      Field name
//     if ((posin = lines[i].find(':')) == std::string::npos)
//       throw(Exception("Header field name not well formated : " +
//       lines[i]));
//     field._field_name = lines[i].substr(0, posin);
//     if (!isValidToken(field._field_name))
//       throw(Exception("Header field name not well formated : " +
//       lines[i]));
//     lines[i].erase(0, posin + 1);
//
//      OWS
//     if (lines[i][0] == ' ')
//       lines[i].erase(0, 1);
//
//      Field value
//     if (lines[i].find('\r') != std::string::npos)
//       field._field_value = lines[i].substr(0, lines[i].find('\r'));
//     else if (lines[i].find('\n') != std::string::npos)
//       field._field_value = lines[i].substr(0, lines[i].find('\n'));
//     else
//       field._field_value = lines[i].substr(0, lines[i].length());
//
////    this->_header_fields.push_back(field);
////  }
////  return (i);
//}

// std::string server_name = getServerName(header);
//             Socket *last = _serverManager.getBySDandHost(
//                 client_socket.getParent()->getSd(),
//                 server_name);

// size_t len = header.getPlainRequest().length();
// if (header.getPlainRequest() == "\r\n" || len < 9)
//   throw(Exception("Empty request"));
// static size_t getContentLen(std::string request) {
//   size_t pos_in = 0;
//   std::string line;
//
//   size_t pos = 0;
//   size_t end = request.find("\n");
//   while (end != std::string::npos) {
//     line = request.substr(pos, end - pos);
//     if (((pos_in = line.find("Content-Length")) != std::string::npos) &&
//         pos_in == 0)
//       return (atoi(line.substr(line.find(":") + 2, line.length()).c_str()));
//     if ((pos_in = request.find("\r\n\r\n")) != std::string::npos &&
//         pos_in == pos)
//       break;
//     pos = end + 1;
//     end = request.find("\n", pos);
//   }
//   return (0);
// }
//
///* return 0 = nop, 1 = classic content, 2 = chunked*/
// static int hasContent(std::string request) {
//   size_t pos_in = 0;
//   std::string line;
//
//   size_t pos = 0;
//   size_t end = request.find("\n");
//   while (end != string::npos) {
//     line = request.substr(pos, end - pos);
//     if ((pos_in = line.find("Transfer-Encoding: chunked")) !=
//             std::string::npos &&
//         pos_in == 0)
//       return (2);
//     else if (((pos_in = line.find("Content")) != std::string::npos) &&
//              pos_in == 0)
//       return (1);
//     if ((pos_in = request.find("\r\n\r\n")) != std::string::npos &&
//         pos_in == pos)
//       break;
//     pos = end + 1;
//     end = request.find("\n", pos);
//   }
//   return (0);
// }
//   std::vector<std::string> block_lines;
//
//   getLines(request, &block_lines);
//   try {
//     if (block_lines.size() < 1)
//       throw(Exception("Not valid header (size to low)"));
//     size_t pos = block_lines[0].find(" ");
//     std::string first_word = block_lines[0].substr(0, block_lines[0].find("
//     ")); if (pos != std::string::npos) {
//       //      int methods_number = 0;
//       //      int i;
//       //      while (methods[methods_number++])
//       //        ;
//
//       //      for (i = 0; i < methods_number /*&& methods[i]*/; i++) {
//       //        if (first_word == methods[i]) {
//       //          this->getRequestLine(block_lines);
//       //          break;
//       //        }
//       //      }
//       //      if (methods[i] == NULL)
//       //        this->getStatusLine(block_lines);
//     }
//     size_t end_headers = this->getHeaderFileds(block_lines);
//     while (42) {
//       if (end_headers < block_lines.size() && block_lines[end_headers] ==
//       "\r")
//         end_headers++;
//       else
//         break;
//     }
//     if (content_type != 2) /* Non chunked transfer */
//       for (size_t i = end_headers; i < block_lines.size(); i++)
//         this->pushContent(block_lines[i]);
//     else if (content_type == 2) {
//       while (42) {
//         size_t nbr_char =
//             0; /*= std::stoi(block_lines[end_headers].c_str(), 0, 16);*/
//         end_headers++;
//         if (nbr_char == 0)
//           break;
//         std::string new_line;
//         for (size_t i = 0; i < nbr_char; i++) {
//           size_t pos_cut = nbr_char;
//           std::string line = block_lines[end_headers];
//           size_t line_len = line.length();
//           if (nbr_char > line_len - 1)
//             pos_cut = line_len;
//           new_line.append(line.substr(0, pos_cut));
//           if (line_len - 1 < nbr_char - i) {
//             new_line.append("\n");
//             i++;
//           }
//           end_headers++;
//           i += pos_cut;
//         }
//         if (block_lines[end_headers][0] == '\r') {
//           new_line.append("\n");
//           end_headers++;
//         }
//         this->pushContent(new_line);
//       }
//     }
//   } catch (const std::exception &e) {
//     throwError(e);
//     exit(0);
//     throw(Exception("Can't parse header."));
//   }
// }