/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:31 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/31 21:54:51 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/server.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

server::server(config_webserv& config) : _config(config), _stat_of_server(false), _epoll_instance(),
                                         _number_max_events(config._bloc_events._worker_connections * config._worker_process),
                                         _number_triggered_events(), _webserv_event(),
                                         _server_events(new struct epoll_event[_number_max_events]),
                                         _map_client_socket(), _client_event(),
                                         _client_address(), _client_address_len(sizeof(_client_address)) {}

server::~server() {
    delete[] _server_events;
}

server::server(const server& other) :   _config(other._config), _stat_of_server(other._stat_of_server),
                                        _epoll_instance(other._epoll_instance),
                                        _number_max_events(other._number_max_events),
                                        _number_triggered_events(other._number_triggered_events),
                                        _webserv_event(other._webserv_event), _server_events(other._server_events),
                                        _map_client_socket(other._map_client_socket),
                                        _client_event(other._client_event), _client_address(other._client_address),
                                        _client_address_len(other._client_address_len){}

server& server::operator=(const server& rhs){
    this->_config = rhs._config;
    this->_epoll_instance = rhs._epoll_instance;
    this->_number_max_events = rhs._number_max_events;
    this->_number_triggered_events = rhs._number_triggered_events;
    this->_map_client_socket = rhs._map_client_socket;
    this->_client_event = rhs._client_event;
    this->_client_address = rhs._client_address;
    this->_client_address_len = rhs._client_address_len;
    return *this;
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

server::server_exception::server_exception(const char * message) : _message(message) {}

server::server_exception::~server_exception() throw() {}

const char * server::server_exception::what() const throw() { return _message.c_str(); }

server::server_exception::server_exception(const server::server_exception & other) : _message(other._message) {}

server::server_exception &server::server_exception::operator=(const server::server_exception &rhs) {
    this->_message = rhs._message;
    return *this;
}

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

config_webserv server::get_config_webserv() const {
    return _config;
}

/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

void server::launcher() {
    _stat_of_server = true;
    try {
        set_epoll();
        while(_stat_of_server) {
            set_epoll_wait();
            for (int i = 0; i < _number_triggered_events; ++i) {
                if (is_server_socket_already_conected(i))
                    manage_event_already_conected(i);
            }
        }
    }
    catch (const std::exception& e){//if necessary to save the socket in process
        std::cout << e.what() << std::endl;
    }
}

/*
*====================================================================================
*|                                 private utils function to launch                 |
*====================================================================================
*/

void server::set_epoll(){
    create_epoll();
    for (std::vector<bloc_server>::iterator server = _config._bloc_http._vector_bloc_server.begin();
    server != _config._bloc_http._vector_bloc_server.end(); ++server){
        for (std::vector<listen_data>::iterator vec_listen = server->_vector_listen.begin();
             vec_listen != server->_vector_listen.end(); ++vec_listen) {
            set_epoll_event(vec_listen->_server_socket, _webserv_event, EPOLLIN);
            set_epoll_ctl(EPOLL_CTL_ADD, vec_listen->_server_socket);
        }
    }
}

void server::create_epoll() {
    _epoll_instance = epoll_create(1);
    if (_epoll_instance == -1)
        throw server_exception(strerror(errno));
}

void server::set_epoll_event(int & server_socket, struct epoll_event & event, int events){
    event.data.fd = server_socket;
    event.events = events;
}

void server::set_epoll_ctl(int option, int server_socket) {
    if(epoll_ctl( _epoll_instance, option, server_socket, &_webserv_event) == -1){
        server_exception server_exception(strerror(errno));
        throw server_exception;
    }
}

void server::set_epoll_wait() {
    _number_triggered_events = epoll_wait(_epoll_instance, _server_events,_number_max_events, -1);//@todo manage limit connectiuon
    if (_number_triggered_events == -1)
        throw server::server_exception(strerror(errno));
}

bool server::is_server_socket_already_conected(int position){
    for (std::vector<bloc_server>::iterator server = _config._bloc_http._vector_bloc_server.begin();
         server != _config._bloc_http._vector_bloc_server.end(); ++server) {
        for (std::vector<listen_data>::iterator vec_listen = server->_vector_listen.begin();
             vec_listen != server->_vector_listen.end(); ++vec_listen) {
            if (vec_listen->_server_socket == _server_events[position].data.fd){
                accept_connection(_server_events[position].data.fd, *server);
                return false;//@todo add check server name and number of connection extract data client if necessary
            }
        }
    }
    return true;
}

void server::accept_connection(int new_client_socket, bloc_server &server) {
    new_client_socket = accept(new_client_socket, reinterpret_cast<struct sockaddr *>(&_client_address),
            &_client_address_len);
    if (new_client_socket == -1)
        throw server::server_exception(strerror(errno));
    accessor_socket_flag(new_client_socket, F_SETFL, O_NONBLOCK);
    set_epoll_event(new_client_socket, _webserv_event, EPOLLIN | EPOLLET);
    set_epoll_ctl(EPOLL_CTL_ADD, new_client_socket);
    _number_max_events--;
    _map_client_socket.insert(std::make_pair(new_client_socket, server));
    send_data_client(new_client_socket,
                     set_html_content(&set_headers_htm, "/usr/local/var/www/webserv.com/accueille.html"));//@todo set server html root
}

void server::manage_event_already_conected(int position){
    std::string data;
    recv_data_client(_server_events[position].data.fd);
    std::cout << data << std::endl;
    send_data_client(_server_events[position].data.fd, data);

//    close(_server_events[position].data.fd);

//    set_epoll_ctl(EPOLL_CTL_DEL, socket, NULL); for close socket unlonk
}

std::string server::recv_data_client(int client_socket){
    char buffer[1024];//@todo see if define in conf file
    ssize_t bytes_received;
    std::string data;

    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    std::cout << buffer << std::endl;
    data += buffer;
    if (bytes_received == -1) {
        server_exception server_exception(strerror(errno));
        throw server_exception;
    }
    return data;
}

void server::send_data_client(int client_socket, std::string content){
    ssize_t bytes_send;
    std::cout <<content <<std::endl;
    bytes_send = send(client_socket, content.c_str(), content.length(), 0);
    if (bytes_send == -1) {
        server_exception server_exception(strerror(errno));
        throw server_exception;
    }
}

std::string server::set_content(std::string (*f)(size_t), std::string path_file) {
    std::ifstream html(path_file.c_str());
    if (!html) {
        server_exception server_exception(strerror(errno));
        throw server_exception;
    }
    std::stringstream html_string;
    html_string << html.rdbuf();
    html.close();

    std::string content = f(html_string.str().length());
    content += "\r\n\r\n" + html_string.str();

    return content;
}

std::string server::set_headers_html(size_t content_length) {
    std::string headers(  "HTTP/1.1 200 OK\r\n"
                            "Content-Type: text/html\r\n"
                            "Content-Length: " );
    std::stringstream length;
    length << content_length;
    headers += length.str();
    return headers;
}

std::string server::set_headers_css(size_t content_length) {
    std::string headers(  "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/css\r\n"
                          "Content-Length: " );
    std::stringstream length;
    length << content_length;
    headers += length.str();
    return headers;
}



























void server::set_socket(int & server_socket) {
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == 0)
        throw server::server_exception(strerror(errno));
}

void server::set_socket_option(int & server_socket){
    int option_val = 1;
    if (setsockopt(server_socket, IPPROTO_TCP, SO_REUSEADDR,
                   &option_val, (socklen_t)sizeof(option_val)))
        throw server::server_exception(strerror(errno));
}

void server::set_bind(int & server_socket, sockaddr_in sock_address) {
    if (bind(server_socket, reinterpret_cast<struct sockaddr *>(&sock_address), sizeof(sock_address)) < 0)
        throw server::server_exception(strerror(errno));
}

void server::set_listen(int & server_socket, int backlog) {
    if (listen(server_socket, backlog) < 0)
        throw server::server_exception(strerror(errno));
}

int server::accessor_socket_flag(int & server_socket, int command, int flag){
    int return_flag = fcntl(server_socket, command, flag);
    if (return_flag < 0)
        throw server::server_exception(strerror(errno));
    return return_flag;
}
















//int data_server::fd_isopen() {
//    int ret = fcntl(getServerFd(), F_GETFL);
//    if (ret == -1) {
//        throw data_server::data_exception();
//    }
//    return 1;
//}
//
//int data_server::socket_isopen() {
//    int error;
//    socklen_t len = sizeof(error);
//    int ret = getsockopt(getServerFd(), SOL_SOCKET, SO_ERROR, &error, &len);
//    if (ret != 0 || error > 0) {i
//        throw data_server::data_exception();
//    }
//    return 1;
//}


