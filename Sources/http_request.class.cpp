/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_request.class.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */


#include "../Include/http_request.class.hpp"


/*
*==========================================================================================================
*|                                                  http_request                                          |
*==========================================================================================================
*/

http_request::http_request(config_webserv &config)
: _config(config), _map_status_code(), _map_content_type(), _status_code(200), _content_type("html"),
  _connection("keep-alive"), _buffer(), _header_buffer(1024 + 1, '\0'), _body_buffer(1024 + 1, '\0') {
    set_map_status_code();
    set_map_content_type();
    set_map_token_information();
    set_map_token_methode();
}//@todo manage buffer client_header_buffer_size client_body_buffer_size client_max_body_size

http_request::~http_request() {}

http_request::http_request(const http_request & other) : _config(other._config), _status_code(other._status_code){}

http_request &http_request::operator=(const http_request &rhs) {
    this->_config = rhs._config;
    this->_status_code = rhs._status_code;
    return *this;
}

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

std::string http_request::manage_request(epoll_event & event) {//update to return int
    //@todo add reset value
    try {
        switch (is_server_socket_already_connected(event)) {
            case false:
                set_reply();
                return std::string("connection");
            default:
                return manage_event_already_connected(event);
        }
    }
    catch (const std::exception& e){
        std::cout << e.what() << std::endl;
        return std::string("disconnection");//@todo to recheck
    }
}

bool http_request::is_server_socket_already_connected(epoll_event & event){
    for (std::vector<bloc_server>::iterator server = _config._bloc_http._vector_bloc_server.begin();
         server != _config._bloc_http._vector_bloc_server.end(); ++server) {
        for (std::vector<listen_data>::iterator vec_listen = server->_vector_listen.begin();
             vec_listen != server->_vector_listen.end(); ++vec_listen) {
            if (vec_listen->_server_socket == event.data.fd){
                _config._bloc_http._select_bloc_server = std::distance(_config._bloc_http._vector_bloc_server.begin(), server);
                return false;
            }
        }
    }
    return true;
}

std::string http_request::manage_event_already_connected(epoll_event & event){
//    bloc_server &server= _config._bloc_http._vector_bloc_server.at(_config._bloc_http._map_client_socket.find(event.data.fd)->second);
    recv_data_client(event.data.fd);
    peg.setStringStream(_buffer);
    //@todo set in try
    while (!peg.check_is_empty()) {
        peg.find_token(*this, _map_token_list_action_methode, 0);
    }
        //exec if necessary
    set_reply();
    return _connection;
}

std::string http_request::recv_data_client(int client_socket){
    std::fill(_buffer.begin(), _buffer.end(), '\0');
    ssize_t bytes_received = recv(client_socket, (void *) _buffer.data(), _buffer.size(), 0);
    if (bytes_received == -1 || bytes_received == 0 || static_cast<unsigned long long>(bytes_received) == (_buffer.size() - 1))
        throw http_request::http_request_exception(strerror(errno));
    std::cout << _buffer << std::endl;
    return std::string(_buffer);
}

void http_request::send_data_client(int client_socket){
    ssize_t bytes_send = send(client_socket, (void *)_buffer.data(), _buffer.size(), 0);
    if (bytes_send == -1) {
        throw http_request::http_request_exception(strerror(errno));
    }
    for (std::vector<std::string>::iterator buffer = _vector_body_buffer_next.begin();
         buffer != _vector_body_buffer_next.end(); ++buffer) {
        bytes_send = send(client_socket, (void *)_buffer.data(), _buffer.size(), 0);
        if (bytes_send == -1) {
            throw http_request::http_request_exception(strerror(errno));
        }
    }
}

void http_request::set_reply() {
    set_content();
    set_header();
    set_buffer();
}

std::string http_request::add_status_code() {
    std::string code(_map_status_code.find(_status_code)->second);
    code += "\r\n";
    return code;
}

std::string http_request::add_content_info() {
    if(_body_buffer.empty())
        return std::string();
    std::string info("Content-Type: ");
    info += _map_content_type.find(_content_type)->second;
    info += "\r\n Content-Length: ";
    std::stringstream ss;
    ss << _body_buffer.size();
    info += ss.str();
    return info;
}

std::string http_request::add_connection() {
    std::string connection("Connection: ");
    connection += _connection;
    return connection;
}

void http_request::set_header() {
    std::string header_tmp;
    header_tmp += "HTTP/1.1 ";
    header_tmp += add_status_code();
    header_tmp += add_content_info();
    //@todo servername date expire Location Set-Cookie
    header_tmp += add_connection();

    header_tmp += "\r\n\r\n";

    if (header_tmp.size() > 1024)//@todo update value
        throw http_request::http_request_exception("headers to large");
    std::fill(_header_buffer.begin(), _header_buffer.end(), '\0');
    _header_buffer.replace(0, header_tmp.size(), header_tmp);
}

void http_request::set_content() {
    std::string connect("<html><body>Connected</body></html>");
    std::fill(_body_buffer.begin(), _body_buffer.end(), '\0');
    _body_buffer.replace(0, connect.size(), "<html><body>Connected</body></html>");
}
//std::string http_request::set_content() {
//    std::ifstream html(path_html_file.c_str());
//    if (!html) {
//        server_exception server_exception(strerror(errno));
//        throw server_exception;
//    }
//    std::stringstream html_string;
//    html_string << html.rdbuf();
//    html.close();
//
//    std::string content = set_headers(html_string.str().length());
//    content += "\r\n\r\n" + html_string.str();
//
//    return content;
//}

void http_request::set_buffer() {
    std::fill(_buffer.begin(), _buffer.end(), '\0');
    _buffer.replace(0, _header_buffer.size(), _header_buffer);
    _buffer.replace(_header_buffer.find('\0'), _body_buffer.size(), _body_buffer);
}



void http_request::set_map_status_code() {

    /**
     * https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
     */

    /**
     *  the server has received the client's request headers and is ready
     * to receive the request body. It allows the client to proceed with sending the request.
     */
    _map_status_code[100] = "Continue";

    /**
     * the server agrees to switch to a different protocol, specified in the response's "Upgrade"
     * header. For example, it can be used when a client requests an upgrade to the WebSocket protocol.
     */
    _map_status_code[101] = "Switching Protocols";

    /**
     * the server has received the client's request and is currently processing it, but the final
     * response is not yet available.
     */
    _map_status_code[102] = "Processing";

    /**
     *  the client's request has been successfully processed, and the corresponding response is being returned.
     */
    _map_status_code[200] = "200 OK";

    /**
     * the request has been successfully processed and a new resource has been created as a result.
     * For example, when a new record is created in a database.
     */
    _map_status_code[201] = "Created";

    /**
     * the request has been accepted for processing, but the processing is not yet complete.
     * The final response may be returned later.
     */
    _map_status_code[202] = "Accepted";

    /**
     * the request has been successfully processed, but the response does not contain any content to be returned.
     * For example, when a deletion request is successful but no additional response is needed.
     */
    _map_status_code[204] = "No Content";

    /**
     * the response contains only a portion of the requested resource. This typically occurs in
     * the case of range requests, where the client requests only a specific part of the resource.
     */
    _map_status_code[206] = "Partial Content";

    /**
     * the response may contain multiple options, and the client needs to choose from them.
     * For example, when a URL redirects to multiple other possible URLs.
     */
    _map_status_code[300] = "Multiple Choices";

    /**
     * the requested resource has been permanently moved to a new URL.
     * The client is typically instructed to update its links and use the new URL.
     */
    _map_status_code[301] = "Moved Permanently";

    /**
     *  the requested resource has been temporarily moved to a different URL.
     *  The client is typically instructed to follow the redirection.
     */
    _map_status_code[302] = "Found";

    /**
     * the requested resource has not been modified since the client's last request,
     * and therefore the response is empty. The client can use the locally cached copy of the resource.
     */
    _map_status_code[304] = "Not Modified";

    /**
     *  the requested resource has been temporarily moved to a different URL.
     *  The client is typically instructed to follow the redirection while maintaining
     *  the original request method.
     */
    _map_status_code[307] = "Temporary Redirect";

    /**
     * the requested resource has been permanently moved to a new URL. The client is typically
     * instructed to follow the redirection while maintaining the original request method.
     */
    _map_status_code[308] = "Permanent Redirect";

    /**
     * the client's request is incorrect or malformed and cannot be processed by the server.
     */
    _map_status_code[400] = "Bad Request";

    /**
     * authentication is required to access the requested resource, but the client has not
     * provided valid credentials or is not authorized to access the resource.
     */
    _map_status_code[401] = " Unauthorized";

    /**
     * the client is not authorized to access the requested resource,
     * even after successful authentication.
     */
    _map_status_code[403] = "Forbidden";

    /**
     * the requested resource could not be found on the server.
     */
    _map_status_code[404] = "Not Found";

    /**
     *  the request method used by the client is not allowed for the requested resource.
     *  For example, if a client attempts to use a POST method for a resource accept only GET methode
     */
    _map_status_code[405] = "Method Not Allowed";

    /**
     * the request cannot be completed due to a conflict with the current state of the resource.
     * For example, when there is a versioning conflict or a conflict between concurrent requests.
     */
    _map_status_code[409] = "Conflict";

    /**
     * the requested resource is no longer available on the server and there is no forwarding address.
     * It is similar to a 404 error but indicates that the resource is permanently gone.
     */
    _map_status_code[410] = "Gone";

    /**
     * the client has sent too many requests within a given time frame and has exceeded the server's
     * rate limiting policy. It is often used to prevent abuse or to ensure fair usage.
     */
    _map_status_code[429] = "Too Many Requests";

    /**
     * an unexpected error occurs on the server that prevents it from fulfilling the client's request.
     * It indicates a server-side issue.
     */
    _map_status_code[500] = "Internal Server Error";

    /**
     * the server does not support the functionality required to fulfill the request.
     * It typically indicates that the server lacks the capability to handle the requested method.
     */
    _map_status_code[501] = "Not Implemented";

    /**
     * the server acting as a gateway or proxy receives an invalid response from an upstream server.
     */
    _map_status_code[502] = "Bad Gateway";

    /**
     * the server is temporarily unable to handle the request due to being overloaded or undergoing maintenance.
     * It indicates a temporary unavailability of the server.
     */
    _map_status_code[503] = "Service Unavailable";

    /**
     * the server acting as a gateway or proxy does not receive a timely response from an upstream server.
     */
    _map_status_code[504] = "Gateway Timeout";

    /**
     * the server does not support the HTTP protocol version used in the request.
     */
    _map_status_code[505] = "HTTP Version Not Supported";
}

void http_request::set_map_content_type() {
    _map_content_type["plain"] = "text/plain";
    _map_content_type["html"] = "text/html";
    _map_content_type["css"] = "text/css";
    _map_content_type["js"] = "text/javascript";
    _map_content_type["json"] = "application/json";
    _map_content_type["xml"] = "application/xml";
    _map_content_type["pdf"] = "application/pdf";
    _map_content_type["octet-stream"] = "application/octet-stream";
    _map_content_type["jpeg"] = "image/jpeg";
    _map_content_type["png"] = "image/png";
    _map_content_type["gif"] = "image/gif";
    _map_content_type["mpeg"] = "audio/mpeg";
    _map_content_type["mp4"] = "video/mp4";
    _map_content_type["form-data"] = "multipart/form-data";
}

void http_request::set_map_token_methode() {
    _map_token_list_action_methode["GET"] = &http_request::get_methode;
    _map_token_list_action_methode["POST"] = &http_request::post_methode;
    _map_token_list_action_methode["DELETE"] = &http_request::delete_methode;
}

void http_request::set_map_token_information() {
    _map_token_list_action_information["Host:"] = &http_request::extract_unused_information;
    _map_token_list_action_information["User-Agent:"] = &http_request::extract_unused_information;
    _map_token_list_action_information["Accept:"] = &http_request::extract_unused_information;
    _map_token_list_action_information["Accept-Language:"] = &http_request::extract_unused_information;
    _map_token_list_action_information["Accept-Encoding:"] = &http_request::extract_unused_information;
    _map_token_list_action_information["Connection:"] = &http_request::connection_information;
    _map_token_list_action_information["Upgrade-Insecure-Requests:"] = &http_request::extract_unused_information;
    _map_token_list_action_information["Sec-Fetch-Dest:"] = &http_request::extract_unused_information;
    _map_token_list_action_information["Sec-Fetch-Mode:"] = &http_request::extract_unused_information;
    _map_token_list_action_information["Sec-Fetch-Site:"] = &http_request::extract_unused_information;
    _map_token_list_action_information["Sec-Fetch-User:"] = &http_request::extract_unused_information;
}

std::string http_request::extract_unused_information() {
    std::string http_version = peg.extract_data('\n');
    return std::string();
}

std::string http_request::extract_location() {
    return peg.extract_data(' ');
}

std::string http_request::extract_http_version() {
    std::string http_version = peg.extract_data('\n');
    http_version.resize(http_version.size() - 1);
    if (http_version != "HTTP/1.1")
        throw http_request::http_request_exception("error version");
    return http_version;
}

std::string http_request::get_methode() {
    std::string location = extract_location();
    std::string http_version = extract_http_version();
    while (!peg.check_is_empty()) {
        peg.find_token(*this, _map_token_list_action_information, 0);
    }
    return std::string();
}

std::string http_request::post_methode() {
    std::string location = extract_location();
    std::string http_version = extract_http_version();
    return std::string();
}

std::string http_request::delete_methode() {
    std::string location = extract_location();
    std::string http_version = extract_http_version();
    return std::string();
}

std::string http_request::connection_information() {
    std::string connection = peg.extract_data('\n');
    _connection = connection.substr(0, connection.size() - 1);
    return std::string();
}


/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

http_request::http_request_exception::http_request_exception(const char * message) : _message(message) {}

http_request::http_request_exception::~http_request_exception() throw() {}

const char * http_request::http_request_exception::what() const throw() { return _message.c_str(); }

http_request::http_request_exception::http_request_exception(const http_request::http_request_exception & other) : _message(other._message) {}

http_request::http_request_exception &http_request::http_request_exception::operator=(const http_request::http_request_exception &rhs) {
    this->_message = rhs._message;
    return *this;
}





