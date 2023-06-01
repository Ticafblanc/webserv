///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   http_request.class.cpp                           :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
///*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
///*                                                                            */
///* ************************************************************************** */
//
//
//#include "../Include/http_request.class.hpp"
//
//
///*
//*==========================================================================================================
//*|                                                  http_request                                          |
//*==========================================================================================================
//*/
//
//http_request::http_request(configWebserv &config)
//: _config(config), _map_status_code(), _map_content_type(), _status_code(200), _content_type("html"),
//  _connection("keep-alive"), _buffer(), _header_buffer(1024, '\0'), _body_buffer(1024, '\0'){
//    set_map_status_code();
//    set_map_content_type();
//    set_map_token_information();
//    set_map_token_methode();
//}//@todo manage buffer client_header_buffer_size client_body_buffer_size client_max_body_size
//
//http_request::~http_request() {}
//
//http_request::http_request(const http_request & other) : _config(other._config), _status_code(other._status_code){}
//
//http_request &http_request::operator=(const http_request &rhs) {
//    this->_config = rhs._config;
//    this->_status_code = rhs._status_code;
//    return *this;
//}
//
///*
//*====================================================================================
//*|                                       Methode                                    |
//*====================================================================================
//*/
//
//std::string http_request::manage_request(epoll_event & event) {//update to return int
//    //@todo add reset value
//    try {
//        switch (is_server_socket_already_connected(event)) {
//            case false:
////                set_reply();
//                return std::string("connection");
//            default:
//                return manage_event_already_connected(event);
//        }
//    }
//    catch (const std::exception& e){
//        std::cout << e.what() << std::endl;
//        return std::string("disconnection");//@todo to recheck
//    }
//}
//
//
//
//std::string http_request::manage_event_already_connected(epoll_event & event){
////    bloc_server &server= _config._bloc_http._vector_bloc_server.at(_config._bloc_http._map_client_socket.find(event.data.fd)->second);
//    if (recv_data_client(event.data.fd) == 0){
//        _content = "Webserv connected";
////        _connection = "close";
//        set_reply();
//        return _connection;
//    }
//    peg.setStringStream(_buffer);
//    //@todo set in try
//    while (!peg.check_is_empty()) {
//        peg.find_token(*this, _map_token_list_action_methode, 0);
//    }
//        //exec if necessary
//    set_reply();
//    return _connection;
//}
//
//ssize_t http_request::recv_data_client(int client_socket){
//    std::fill(_buffer.begin(), _buffer.end(), '\0');
//    char buffer[1024];
//    ssize_t bytes_received = recv(client_socket, buffer, 1024, 0);
////    _buffer.replace(0, bytes_received, buffer);
//    buffer[bytes_received] ='\0';
//    _buffer = buffer;
//    std::cout << " client  >> " << client_socket<< " recv >>> \n"  << buffer << _buffer.size()<<bytes_received<< "\n"<< std::endl;
//
//    if (bytes_received == -1 /*|| bytes_received == 0*/ || static_cast<unsigned long long>(bytes_received) == (1024))
//        throw http_request::http_request_exception(strerror(errno));
//    return bytes_received;
//}
//
//void http_request::send_data_client(int client_socket){
//    std::cout << " client  >> " << client_socket << " send >>> \n" << _buffer << _buffer.find('\0')<<  "\n"<<std::endl;
//
//    ssize_t bytes_send = send(client_socket, (void *)_buffer.data(), 764, 0);
//    if (bytes_send == -1) {
//        throw http_request::http_request_exception(strerror(errno));
//    }
//    for (std::vector<std::string>::iterator buffer = _vector_body_buffer_next.begin();
//         buffer != _vector_body_buffer_next.end(); ++buffer) {
//        bytes_send = send(client_socket, (void *)_buffer.data(), _buffer.size(), 0);
//        if (bytes_send == -1) {
//            throw http_request::http_request_exception(strerror(errno));
//        }
//    }
//}
//
//void http_request::set_reply() {
//    set_content();
//    set_header();
//    set_buffer();
//}
//
//std::string http_request::add_status_code() {
//    std::string code(_map_status_code.find(_status_code)->second);
//    code += "\r\n";
//    return code;
//}
//
//std::string http_request::add_content_info() {
//    if(_content.empty())
//        return std::string();
//    std::string info("Content-Type: ");
//    info += _map_content_type.find(_content_type)->second;
//    info += "\r\nContent-Length: ";
//    std::stringstream ss;
//    ss << _content.size();
//    info += ss.str();
//    info += "\r\n";
//    return info;
//}
//
//std::string http_request::add_connection() {
//    std::string connection("Connection: ");
//    connection += _connection;
//    return connection;
//}
//
//void http_request::set_header() {
//    std::string header_tmp;
//    header_tmp += "HTTP/1.1 ";
//    header_tmp += add_status_code();
//    header_tmp += add_content_info();
//    header_tmp += "Cache-Control: no-cache, no-store, must-revalidate\r\n"
//                  "Pragma: no-cache\r\n"
//                  "Expires: 0\r\n";
//    //@todo servername date expire Location Set-Cookie
////    header_tmp += add_connection();
//
//    header_tmp += "\r\n";
//
//    if (header_tmp.size() > 1024)//@todo update value
//        throw http_request::http_request_exception("headers to large");
////    std::fill(_header_buffer.begin(), _header_buffer.end(), '\0');
//    _header_buffer = header_tmp;
//}
//
//void http_request::set_content() {
////    std::fill(_body_buffer.begin(), _body_buffer.end(), '\0');
////    if (!_content.empty()) {
////        _body_buffer.replace(0, _content.size(), _content);
////    }
//}
//
//void http_request::set_buffer() {
//    _buffer = _header_buffer + _content;
////    std::fill(_buffer.begin(), _buffer.end(), '\0');
////    _buffer.replace(0, _header_buffer.find('\0'), _header_buffer);
////    if (!_content.empty()) {
////        _buffer.replace(_header_buffer.find('\0'), _body_buffer.find('\0'), _body_buffer);
////    }
//}
//
//
//
//void http_request::set_map_status_code() {
//
//    /**
//     * https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
//     */
//
//    /**
//     *  the server has received the client's request headers and is ready
//     * to receive the request body. It allows the client to proceed with sending the request.
//     */
//    _map_status_code[100] = "Continue";
//
//    /**
//     * the server agrees to switch to a different protocol, specified in the response's "Upgrade"
//     * header. For example, it can be used when a client requests an upgrade to the WebSocket protocol.
//     */
//    _map_status_code[101] = "Switching Protocols";
//
//    /**
//     * the server has received the client's request and is currently processing it, but the final
//     * response is not yet available.
//     */
//    _map_status_code[102] = "Processing";
//
//    /**
//     *  the client's request has been successfully processed, and the corresponding response is being returned.
//     */
//    _map_status_code[200] = "200 OK";
//
//    /**
//     * the request has been successfully processed and a new resource has been created as a result.
//     * For example, when a new record is created in a database.
//     */
//    _map_status_code[201] = "Created";
//
//    /**
//     * the request has been accepted for processing, but the processing is not yet complete.
//     * The final response may be returned later.
//     */
//    _map_status_code[202] = "Accepted";
//
//    /**
//     * the request has been successfully processed, but the response does not contain any content to be returned.
//     * For example, when a deletion request is successful but no additional response is needed.
//     */
//    _map_status_code[204] = "No Content";
//
//    /**
//     * the response contains only a portion of the requested resource. This typically occurs in
//     * the case of range requests, where the client requests only a specific part of the resource.
//     */
//    _map_status_code[206] = "Partial Content";
//
//    /**
//     * the response may contain multiple options, and the client needs to choose from them.
//     * For example, when a URL redirects to multiple other possible URLs.
//     */
//    _map_status_code[300] = "Multiple Choices";
//
//    /**
//     * the requested resource has been permanently moved to a new URL.
//     * The client is typically instructed to update its links and use the new URL.
//     */
//    _map_status_code[301] = "Moved Permanently";
//
//    /**
//     *  the requested resource has been temporarily moved to a different URL.
//     *  The client is typically instructed to follow the redirection.
//     */
//    _map_status_code[302] = "Found";
//
//    /**
//     * the requested resource has not been modified since the client's last request,
//     * and therefore the response is empty. The client can use the locally cached copy of the resource.
//     */
//    _map_status_code[304] = "Not Modified";
//
//    /**
//     *  the requested resource has been temporarily moved to a different URL.
//     *  The client is typically instructed to follow the redirection while maintaining
//     *  the original request method.
//     */
//    _map_status_code[307] = "Temporary Redirect";
//
//    /**
//     * the requested resource has been permanently moved to a new URL. The client is typically
//     * instructed to follow the redirection while maintaining the original request method.
//     */
//    _map_status_code[308] = "Permanent Redirect";
//
//    /**
//     * the client's request is incorrect or malformed and cannot be processed by the server.
//     */
//    _map_status_code[400] = "Bad Request";
//
//    /**
//     * authentication is required to access the requested resource, but the client has not
//     * provided valid credentials or is not authorized to access the resource.
//     */
//    _map_status_code[401] = " Unauthorized";
//
//    /**
//     * the client is not authorized to access the requested resource,
//     * even after successful authentication.
//     */
//    _map_status_code[403] = "Forbidden";
//
//    /**
//     * the requested resource could not be found on the server.
//     */
//    _map_status_code[404] = "Not Found";
//
//    /**
//     *  the request method used by the client is not allowed for the requested resource.
//     *  For example, if a client attempts to use a POST method for a resource accept only GET methode
//     */
//    _map_status_code[405] = "Method Not Allowed";
//
//    /**
//     * the request cannot be completed due to a conflict with the current state of the resource.
//     * For example, when there is a versioning conflict or a conflict between concurrent requests.
//     */
//    _map_status_code[409] = "Conflict";
//
//    /**
//     * the requested resource is no longer available on the server and there is no forwarding address.
//     * It is similar to a 404 error but indicates that the resource is permanently gone.
//     */
//    _map_status_code[410] = "Gone";
//
//    /**
//     * the client has sent too many requests within a given time frame and has exceeded the server's
//     * rate limiting policy. It is often used to prevent abuse or to ensure fair usage.
//     */
//    _map_status_code[429] = "Too Many Requests";
//
//    /**
//     * an unexpected error occurs on the server that prevents it from fulfilling the client's request.
//     * It indicates a server-side issue.
//     */
//    _map_status_code[500] = "Internal Server Error";
//
//    /**
//     * the server does not support the functionality required to fulfill the request.
//     * It typically indicates that the server lacks the capability to handle the requested method.
//     */
//    _map_status_code[501] = "Not Implemented";
//
//    /**
//     * the server acting as a gateway or proxy receives an invalid response from an upstream server.
//     */
//    _map_status_code[502] = "Bad Gateway";
//
//    /**
//     * the server is temporarily unable to handle the request due to being overloaded or undergoing maintenance.
//     * It indicates a temporary unavailability of the server.
//     */
//    _map_status_code[503] = "Service Unavailable";
//
//    /**
//     * the server acting as a gateway or proxy does not receive a timely response from an upstream server.
//     */
//    _map_status_code[504] = "Gateway Timeout";
//
//    /**
//     * the server does not support the HTTP protocol version used in the request.
//     */
//    _map_status_code[505] = "HTTP Version Not Supported";
//}
//
//void http_request::set_map_content_type() {
//    _map_content_type["plain"] = "text/plain";
//    _map_content_type["html"] = "text/html";
//    _map_content_type["css"] = "text/css";
//    _map_content_type["js"] = "text/javascript";
//    _map_content_type["json"] = "application/json";
//    _map_content_type["xml"] = "application/xml";
//    _map_content_type["pdf"] = "application/pdf";
//    _map_content_type["octet-stream"] = "application/octet-stream";
//    _map_content_type["jpeg"] = "image/jpeg";
//    _map_content_type["png"] = "image/png";
//    _map_content_type["gif"] = "image/gif";
//    _map_content_type["mpeg"] = "audio/mpeg";
//    _map_content_type["mp4"] = "video/mp4";
//    _map_content_type["form-data"] = "multipart/form-data";
//}
//
//void http_request::set_map_token_methode() {
//    _map_token_list_action_methode["GET"] = &http_request::get_methode;
//    _map_token_list_action_methode["POST"] = &http_request::post_methode;
//    _map_token_list_action_methode["DELETE"] = &http_request::delete_methode;
//}
//
//void http_request::set_map_token_information() {
//    _map_token_list_action_information["Host:"] = &http_request::extract_unused_information;
//    _map_token_list_action_information["User-Agent:"] = &http_request::extract_unused_information;
//    _map_token_list_action_information["Accept:"] = &http_request::extract_unused_information;
//    _map_token_list_action_information["Accept-Language:"] = &http_request::extract_unused_information;
//    _map_token_list_action_information["Accept-Encoding:"] = &http_request::extract_unused_information;
//    _map_token_list_action_information["Connection:"] = &http_request::connection_information;
//    _map_token_list_action_information["Upgrade-Insecure-Requests:"] = &http_request::extract_unused_information;
//    _map_token_list_action_information["Sec-Fetch-Dest:"] = &http_request::extract_unused_information;
//    _map_token_list_action_information["Sec-Fetch-Mode:"] = &http_request::extract_unused_information;
//    _map_token_list_action_information["Sec-Fetch-Site:"] = &http_request::extract_unused_information;
//    _map_token_list_action_information["Sec-Fetch-User:"] = &http_request::extract_unused_information;
//}
//
//std::string http_request::extract_unused_information() {
//    std::string http_version = peg.extract_data('\n');
//    return std::string();
//}
//
//std::string http_request::extract_location() {
//    return peg.extract_data(' ');
//}
//
//std::string http_request::extract_http_version() {
//    std::string http_version = peg.extract_data('\n');
//    http_version.resize(http_version.size() - 1);
//    if (http_version != "HTTP/1.1")
//        throw http_request::http_request_exception("error version");
//    return http_version;
//}
//
//std::string http_request::get_methode() {
//    std::string location = extract_location();
//    std::string http_version = extract_http_version();
//    while (!peg.check_is_empty()) {
//        peg.find_token(*this, _map_token_list_action_information, 0);
//    }
//    std::ifstream file("/usr/local/var/www/index.html");//location
//    if (!file) {
//        throw http_request::http_request_exception("error location");
//    }
//    file.seekg(0, std::ios::end); // Se positionner à la fin du fichier
//    _content.clear();
//    _content.reserve(file.tellg()); // Réserver l'espace dans la chaîne
//    file.seekg(0, std::ios::beg);
//    _content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
//    return std::string();
//}
//
//std::string http_request::post_methode() {
//    std::string location = extract_location();
//    std::string http_version = extract_http_version();
//    return std::string();
//}
//
//std::string http_request::delete_methode() {
//    std::string location = extract_location();
//    std::string http_version = extract_http_version();
//    return std::string();
//}
//
//std::string http_request::connection_information() {
//    std::string connection = peg.extract_data('\n');
//    _connection = connection.substr(0, connection.size() - 1);
////    _connection = "close";
//    return std::string();
//}
//
//
///*
//*====================================================================================
//*|                                  Member Expetion                                 |
//*====================================================================================
//*/
//
//http_request::http_request_exception::http_request_exception(const char * message) : _message(message) {}
//
//http_request::http_request_exception::~http_request_exception() throw() {}
//
//const char * http_request::http_request_exception::what() const throw() { return _message.c_str(); }
//
//http_request::http_request_exception::http_request_exception(const http_request::http_request_exception & other) : _message(other._message) {}
//
//http_request::http_request_exception &http_request::http_request_exception::operator=(const http_request::http_request_exception &rhs) {
//    this->_message = rhs._message;
//    return *this;
//}
//
//
//
//
//
