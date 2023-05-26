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

http_request::http_request(epoll_event & event, server & server) :_event(event), _server(server) {
    //@todo see if necessary to check data event
    try {
        switch (is_server_socket_already_connected()) {
            case false:
                _server.connect_new_client(_event.data.fd);
                break;
            default:
                manage_event_already_connected(_event.data.fd);
                break;
        }
    }
    catch (const std::exception& e){
        std::cout << e.what() << std::endl;

    }
}

http_request::~http_request() {}


http_request &http_request::operator=(const http_request &rhs) {
    return *this;
}

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

bool http_request::is_server_socket_already_connected(){
    for (std::vector<bloc_server>::iterator server = _server.get_http()._vector_bloc_server.begin();
         server != _server.get_http()._vector_bloc_server.end(); ++server) {
        for (std::vector<listen_data>::iterator vec_listen = server->_vector_listen.begin();
             vec_listen != server->_vector_listen.end(); ++vec_listen) {
            if (vec_listen->_server_socket == _event.data.fd){
                return false;
            }
        }
    }
    return true;
}

void http_request::manage_event_already_connected(int client_socket){
    std::map<int, bloc_server&>::iterator  it = _server.get_http()._map_client_socket.find(client_socket);
    if ( it != _server.get_http()._map_client_socket.end()) {
        //@todo parse ....
    }
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





