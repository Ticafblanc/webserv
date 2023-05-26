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

http_request::http_request(std::string &path_config_file) : _peg_parser(path_config_file.c_str()){
    set_map_token();
    while (!_peg_parser.check_is_empty()) {
        _peg_parser.find_token(*this, _map_token_list_action, 0);
    }
    set_default_value();
}

http_request::~http_request() {}

http_request::http_request(http_request & other)
    : _peg_parser(other._peg_parser),_map_token_list_action(other._map_token_list_action),
    _worker_process(other._worker_process), _bloc_events(other._bloc_events), _bloc_http(other._bloc_http){

}

http_request &http_request::operator=(const http_request &rhs) {
    this->_peg_parser = rhs._peg_parser;
    this->_map_token_list_action = rhs._map_token_list_action;
    this->_worker_process = rhs._worker_process;
    return *this;
}


std::string http_request::parse_bloc_event() {
    _map_token_list_action.erase("events");
    std::string value = _peg_parser.extract_data('{');
    if (value.empty())
        value = _bloc_events.parse_bloc_events();
    return value;
}

std::string http_request::parse_bloc_http() {
    _map_token_list_action.erase("http");
    std::string value = _peg_parser.extract_data('{');
    if (value.empty())
        value = _bloc_http.parse_bloc_http();
//    std::cout << "_vector_bloc_server size:" << " " << _bloc_http._vector_bloc_server.size() << std::endl;
//    std::cout << "_vector_bloc_server 0:" << " " <<_ << std::endl;
    return value;
}

std::string http_request::set_worker_processes() {
    _map_token_list_action.erase("worker_processes");
    std::string value = _peg_parser.extract_data(';');
    char * end;//@todo to manage error
    const long val = std::strtol(value.c_str(), &end, 10);
    if (val < 1 || val > 4)
        return value;
    _worker_process = static_cast<int>(val);
    value.clear();
    return value;
}

std::string server::set_html_content(std::string path_html_file) {
    std::ifstream html(path_html_file.c_str());
    if (!html) {
        server_exception server_exception(strerror(errno));
        throw server_exception;
    }
    std::stringstream html_string;
    html_string << html.rdbuf();
    html.close();

    std::string content = set_headers(html_string.str().length());
    content += "\r\n\r\n" + html_string.str();

    return content;
}
std::string server::set_headers(int status_code, size_t content_length) {
    std::string headers("HTTP/1.1 ");
    headers += _status_code[status_code];               //200 OK\r\n"
    headers += _status_code[status_code];               //200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: " );
    headers += content_length;
    return headers;
}

void http_request::set_default_value() {
    std::map<std::string, std::string (http_request::*)()>::iterator it = _map_token_list_action.begin();
    for (;it != _map_token_list_action.end(); ++it) {
        if (it->first == "worker_processes") {
            _worker_process = 1;
        } else if (it->first == "events") {
            _bloc_events.set_default_value();
        } else if (it->first == "http"){
            _bloc_http.set_default_value();
        }
    }
}

void http_request::set_map_token() {
    _map_token_list_action["GET"] = &http_request::set_worker_processes;
    _map_token_list_action["POST"] = &http_request::parse_bloc_event;
    _map_token_list_action["DELETE"] = &http_request::parse_bloc_http;
}

std::string server::recv_data_client(int client_socket){
    char buffer[1024];//@todo see if define in conf file client_body_buffer_size
    ssize_t bytes_received;
    std::string data;

    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    data += buffer;
    if (bytes_received == -1) {
        server_exception server_exception(strerror(errno));
        throw server_exception;
    }
    return data;
}

void server::send_data_client(int client_socket, std::string & content){
    ssize_t bytes_send;

    bytes_send = send(client_socket, content.c_str(), content.length(), 0);
    if (bytes_send == -1) {
        server_exception server_exception(strerror(errno));
        throw server_exception;
    }
}





