/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpRequest.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */


#include "4-Http/Includes/httpRequest.class.hpp"


/*
*==========================================================================================================
*|                                                  httpRequest                                          |
*==========================================================================================================
*/

httpRequest::httpRequest(clientSocket & client)
: _client(client), _map_status_code(), _map_content_type(), _status_code(200), _content_type("html"),
_buffer(){
    set_map_status_code();
    set_map_content_type();
    set_map_token_information();
    set_map_token_methode();
}//@todo manage buffer client_header_buffer_size client_body_buffer_size client_max_body_size

httpRequest::~httpRequest() {}

httpRequest::httpRequest(const httpRequest & other) : _client(other._client),  _status_code(other._status_code){}

httpRequest &httpRequest::operator=(const httpRequest &rhs) {
    this->_client = rhs._client;
    this->_status_code = rhs._status_code;
    return *this;
}

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

void httpRequest::manageRequest() {
    recvData();
    pegParser peg(_buffer);
    //@todo set in try
    while (!peg.checkIsEmpty()) {
        peg.findToken(*this, _mapTokenListActionMethode, 0);
    }
}

void httpRequest::recvData(){
    char buffer[1024 + 1];//@todo update value
    _bytes_exchange = recv(_client.data.fd, buffer, 1024, 0);
    if (_bytes_exchange == 0 )//close connection
        throw httpRequest::httpRequestException(strerror(errno));
    if (_bytes_exchange == -1)//bad request
        throw httpRequest::httpRequestException(strerror(errno));
    if (_bytes_exchange > 1024)//check headrs befor throw
        throw httpRequest::httpRequestException(strerror(errno));
    buffer[_bytes_exchange] ='\0';
    _buffer = buffer;
//    std::cout << " client  >> " << client_socket<< " recv >>> \n"  << buffer << _buffer.size()<<bytes_received<< "\n"<< std::endl;
}

void httpRequest::send_data_client(int client_socket){
    std::cout << " client  >> " << client_socket << " send >>> \n" << _buffer << _buffer.find('\0')<<  "\n"<<std::endl;

    ssize_t bytes_send = send(client_socket, (void *)_buffer.data(), 764, 0);
    if (bytes_send == -1) {
        throw httpRequest::httpRequestException(strerror(errno));
    }
    for (std::vector<std::string>::iterator buffer = _vector_body_buffer_next.begin();
         buffer != _vector_body_buffer_next.end(); ++buffer) {
        bytes_send = send(client_socket, (void *)_buffer.data(), _buffer.size(), 0);
        if (bytes_send == -1) {
            throw httpRequest::httpRequestException(strerror(errno));
        }
    }
}

void httpRequest::set_reply() {
    set_content();
    set_header();
    set_buffer();
}

std::string httpRequest::add_status_code() {
    std::string code(_map_status_code.find(_status_code)->second);
    code += "\r\n";
    return code;
}

std::string httpRequest::add_content_info() {
    if(_content.empty())
        return std::string();
    std::string info("Content-Type: ");
    info += _map_content_type.find(_content_type)->second;
    info += "\r\nContent-Length: ";
    std::stringstream ss;
    ss << _content.size();
    info += ss.str();
    info += "\r\n";
    return info;
}

std::string httpRequest::add_connection() {
    std::string connection("Connection: ");
    connection += _connection;
    return connection;
}

void httpRequest::set_header() {
    std::string header_tmp;
    header_tmp += "HTTP/1.1 ";
    header_tmp += add_status_code();
    header_tmp += add_content_info();
    header_tmp += "Cache-Control: no-cache, no-store, must-revalidate\r\n"
                  "Pragma: no-cache\r\n"
                  "Expires: 0\r\n";
    //@todo servername date expire Location Set-Cookie
//    header_tmp += add_connection();

    header_tmp += "\r\n";

    if (header_tmp.size() > 1024)//@todo update value
        throw httpRequest::httpRequestException("headers to large");
//    std::fill(_header_buffer.begin(), _header_buffer.end(), '\0');
    _header_buffer = header_tmp;
}

void httpRequest::set_content() {
//    std::fill(_body_buffer.begin(), _body_buffer.end(), '\0');
//    if (!_content.empty()) {
//        _body_buffer.replace(0, _content.size(), _content);
//    }
}

void httpRequest::set_buffer() {
    _buffer = _header_buffer + _content;
//    std::fill(_buffer.begin(), _buffer.end(), '\0');
//    _buffer.replace(0, _header_buffer.find('\0'), _header_buffer);
//    if (!_content.empty()) {
//        _buffer.replace(_header_buffer.find('\0'), _body_buffer.find('\0'), _body_buffer);
//    }
}



void httpRequest::set_map_status_code() {

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

void httpRequest::set_map_content_type() {
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

void httpRequest::set_map_token_methode() {
    _mapTokenListActionMethode["GET"] = &httpRequest::get_methode;
    _mapTokenListActionMethode["POST"] = &httpRequest::post_methode;
    _mapTokenListActionMethode["DELETE"] = &httpRequest::delete_methode;
}

void httpRequest::set_map_token_information() {
    _map_token_list_action_information["Host:"] = &httpRequest::extract_unused_information;
    _map_token_list_action_information["User-Agent:"] = &httpRequest::extract_unused_information;
    _map_token_list_action_information["Accept:"] = &httpRequest::extract_unused_information;
    _map_token_list_action_information["Accept-Language:"] = &httpRequest::extract_unused_information;
    _map_token_list_action_information["Accept-Encoding:"] = &httpRequest::extract_unused_information;
    _map_token_list_action_information["Connection:"] = &httpRequest::connection_information;
    _map_token_list_action_information["Upgrade-Insecure-Requests:"] = &httpRequest::extract_unused_information;
    _map_token_list_action_information["Sec-Fetch-Dest:"] = &httpRequest::extract_unused_information;
    _map_token_list_action_information["Sec-Fetch-Mode:"] = &httpRequest::extract_unused_information;
    _map_token_list_action_information["Sec-Fetch-Site:"] = &httpRequest::extract_unused_information;
    _map_token_list_action_information["Sec-Fetch-User:"] = &httpRequest::extract_unused_information;
}

std::string httpRequest::extract_unused_information() {
    std::string http_version = peg.extract_data('\n');
    return std::string();
}

std::string httpRequest::extract_location() {
    return peg.extract_data(' ');
}

std::string httpRequest::extract_http_version() {
    std::string http_version = peg.extract_data('\n');
    http_version.resize(http_version.size() - 1);
    if (http_version != "HTTP/1.1")
        throw httpRequest::httpRequestException("error version");
    return http_version;
}

std::string httpRequest::get_methode() {
    std::string location = extract_location();
    std::string http_version = extract_http_version();
    while (!peg.check_is_empty()) {
        peg.find_token(*this, _map_token_list_action_information, 0);
    }
    std::ifstream file("/usr/local/var/www/index.html");//location
    if (!file) {
        throw httpRequest::httpRequestException("error location");
    }
    file.seekg(0, std::ios::end); // Se positionner à la fin du fichier
    _content.clear();
    _content.reserve(file.tellg()); // Réserver l'espace dans la chaîne
    file.seekg(0, std::ios::beg);
    _content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    return std::string();
}

std::string httpRequest::post_methode() {
    std::string location = extract_location();
    std::string http_version = extract_http_version();
    return std::string();
}

std::string httpRequest::delete_methode() {
    std::string location = extract_location();
    std::string http_version = extract_http_version();
    return std::string();
}

std::string httpRequest::connection_information() {
    std::string connection = peg.extract_data('\n');
    _connection = connection.substr(0, connection.size() - 1);
//    _connection = "close";
    return std::string();
}




/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

httpRequest::httpRequestException::httpRequestException(const char * message) : _message(message) {}

httpRequest::httpRequestException::~httpRequestException() throw() {}

const char * httpRequest::httpRequestException::what() const throw() { return _message.c_str(); }

httpRequest::httpRequestException::httpRequestException(const httpRequest::httpRequestException & other) : _message(other._message) {}

httpRequest::httpRequestException &httpRequest::httpRequestException::operator=(const httpRequest::httpRequestException &rhs) {
    this->_message = rhs._message;
    return *this;
}





