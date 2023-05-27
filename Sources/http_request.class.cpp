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
: _config(config), _map_status_code(), _status_code(200), _map_content_type(), _content_type("html"),
_header_buffer(1024 + 1, '\0'), _body_buffer(1024 + 1, '\0') {
    //@todo set map
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
                return false;
            }
        }
    }
    return true;
}

std::string http_request::manage_event_already_connected(epoll_event & event){
    std::map<int, bloc_server&>::iterator  it = _config._bloc_http._map_client_socket.find(event.data.fd);
    if ( it != _config._bloc_http._map_client_socket.end()) {
        recv_data_client(event.data.fd);
    }
    return std::string("");
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

void http_request::set_header() {
    std::string header_tmp;
    header_tmp += "HTTP/1.1 ";
    header_tmp += _map_status_code.find(_status_code)->second;
    header_tmp += "\r\n";
    header_tmp += "Content-Type: ";
    header_tmp += _map_content_type.find(_content_type)->second;
    header_tmp += "\r\n";
    header_tmp += "Content-Length: ";
    std::stringstream ss;
    ss << _body_buffer.size();
    header_tmp += ss.str();
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

void http_request::set_buffer() {
    std::fill(_buffer.begin(), _buffer.end(), '\0');
    _buffer.replace(0, _header_buffer.size(), _header_buffer);

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


//void http_request::set_default_value() {
//    std::map<std::string, std::string (http_request::*)()>::iterator it = _map_token_list_action.begin();
//    for (;it != _map_token_list_action.end(); ++it) {
//        if (it->first == "worker_processes") {
//            _worker_process = 1;
//        } else if (it->first == "events") {
//            _bloc_events.set_default_value();
//        } else if (it->first == "http"){
//            _bloc_http.set_default_value();
//        }
//    }
//}
//
//void http_request::set_map_token() {
//    _map_token_list_action["GET"] = &http_request::set_worker_processes;
//    _map_token_list_action["POST"] = &http_request::parse_bloc_event;
//    _map_token_list_action["DELETE"] = &http_request::parse_bloc_http;
//}
//
//
//
//


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





