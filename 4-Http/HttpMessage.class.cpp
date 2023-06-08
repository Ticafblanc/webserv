/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMessage.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */


#include "HttpMessage.class.hpp"


/*
*==========================================================================================================
*|                                                  HttpMessage                                          |
*==========================================================================================================
*/

HttpMessage::HttpMessage(Socket& socket, Server& server)
: _socket(socket), _server(server), _status_code(200), _content_type("html"),
_buffer()
    set_map_status_code();
    set_map_content_type();
    set_map_token_information();
    set_map_token_methode();
}//@todo manage buffer

HttpMessage::~HttpMessage() {}

HttpMessage::HttpMessage(const HttpMessage & other) : _client(other._client), _status_code(other._status_code){}

HttpMessage &HttpMessage::operator=(const HttpMessage &rhs) {
    this->_client = rhs._client;
    this->_status_code = rhs._status_code;
    return *this;
}

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

void HttpMessage::manageRequest() {
    recvData();
    pegParser peg(_buffer);
    //@todo set in try
    while (!peg.checkIsEmpty()) {
        peg.findToken(*this, _mapTokenListActionMethode, 0);
    }
}

void HttpMessage::recvData(){
    char buffer[1024 + 1];//@todo update value
    _bytes_exchange = recv(_client.data.fd, buffer, 1024, 0);
    if (_bytes_exchange == 0 )//close connection
        throw HttpMessage::httpMessageException(strerror(errno));
    if (_bytes_exchange == -1)//bad request
        throw HttpMessage::httpMessageException(strerror(errno));
    if (_bytes_exchange > 1024)//check headrs befor throw
        throw HttpMessage::httpMessageException(strerror(errno));
    buffer[_bytes_exchange] ='\0';
    _buffer = buffer;
//    std::cout << " client  >> " << client_socket<< " recv >>> \n"  << buffer << _buffer.size()<<bytes_received<< "\n"<< std::endl;
}

void HttpMessage::send_data_client(int client_socket){
    std::cout << " client  >> " << client_socket << " send >>> \n" << _buffer << _buffer.find('\0')<<  "\n"<<std::endl;

    ssize_t bytes_send = send(client_socket, (void *)_buffer.data(), 764, 0);
    if (bytes_send == -1) {
        throw HttpMessage::httpMessageException(strerror(errno));
    }
    for (std::vector<std::string>::iterator buffer = _vector_body_buffer_next.begin();
         buffer != _vector_body_buffer_next.end(); ++buffer) {
        bytes_send = send(client_socket, (void *)_buffer.data(), _buffer.size(), 0);
        if (bytes_send == -1) {
            throw HttpMessage::httpMessageException(strerror(errno));
        }
    }
}

void HttpMessage::set_reply() {
    set_content();
    set_header();
    set_buffer();
}

std::string HttpMessage::add_status_code() {
    std::string code(_map_status_code.find(_status_code)->second);
    code += "\r\n";
    return code;
}

std::string HttpMessage::add_content_info() {
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

std::string HttpMessage::add_connection() {
    std::string connection("Connection: ");
    connection += _connection;
    return connection;
}

void HttpMessage::set_header() {
    std::string header_tmp;
    header_tmp +=  ";
    header_tmp += add_status_code();
    header_tmp += add_content_info();
    header_tmp += "Cache-Control: no-cache, no-store, must-revalidate\r\n"
                  "Pragma: no-cache\r\n"
                  "Expires: 0\r\n";
    //@todo servername date expire Location Set-Cookie
//    header_tmp += add_connection();

    header_tmp += "\r\n";

    if (header_tmp.size() > 1024)//@todo update value
        throw HttpMessage::httpMessageException("headers to large");
//    std::fill(_header_buffer.begin(), _header_buffer.end(), '\0');
    _header_buffer = header_tmp;
}

void HttpMessage::set_content() {
//    std::fill(_body_buffer.begin(), _body_buffer.end(), '\0');
//    if (!_content.empty()) {
//        _body_buffer.replace(0, _content.size(), _content);
//    }
}

void HttpMessage::set_buffer() {
    _buffer = _header_buffer + _content;
//    std::fill(_buffer.begin(), _buffer.end(), '\0');
//    _buffer.replace(0, _header_buffer.find('\0'), _header_buffer);
//    if (!_content.empty()) {
//        _buffer.replace(_header_buffer.find('\0'), _body_buffer.find('\0'), _body_buffer);
//    }
}
std::string HttpMessage::post_methode() {
    std::string location = extract_location();
    std::string http_version = extract_http_version();
    return std::string();
}

std::string HttpMessage::delete_methode() {
    std::string location = extract_location();
    std::string http_version = extract_http_version();
    return std::string();
}

std::string HttpMessage::connection_information() {
    std::string connection = peg.extract_data('\n');
    _connection = connection.substr(0, connection.size() - 1);
//    _connection = "close";
    return std::string();
}



std::string HttpMessage::get_methode() {
    std::string location = extract_location();
    std::string http_version = extract_http_version();
    while (!peg.check_is_empty()) {
        peg.find_token(*this, _map_token_list_action_information, 0);
    }
    std::ifstream file("/usr/local/var/www/index.html");//location
    if (!file) {
        throw HttpMessage::httpMessageException("error location");
    }
    file.seekg(0, std::ios::end); // Se positionner à la fin du fichier
    _content.clear();
    _content.reserve(file.tellg()); // Réserver l'espace dans la chaîne
    file.seekg(0, std::ios::beg);
    _content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    return std::string();
}

HttpMessage::HttpMessage(Socket &socket, Server &server) {

}


/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

HttpMessage::httpMessageException::httpMessageException(const char * message) : _message(message) {}

HttpMessage::httpMessageException::~httpMessageException() throw() {}

const char * HttpMessage::httpMessageException::what() const throw() { return _message.c_str(); }

HttpMessage::httpMessageException::httpMessageException(const HttpMessage::httpMessageException & other) : _message(other._message) {}

HttpMessage::httpMessageException &HttpMessage::httpMessageException::operator=(const HttpMessage::httpMessageException &rhs) {
    this->_message = rhs._message;
    return *this;
}





