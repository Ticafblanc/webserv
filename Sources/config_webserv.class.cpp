/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_webserv.class.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/config_webserv.class.hpp"


/*
*==========================================================================================================
*|                                                  Bloc location                                         |
*==========================================================================================================
*/


bloc_location::bloc_location(config_webserv& config)
        : _config(config), _map_token_list_action(), _root(), _index() {
    set_map_token();
}

bloc_location::~bloc_location() {}

bloc_location::bloc_location(const bloc_location& other)
        : _config(other._config), _root(other._root), _index(other._index) {}

bloc_location &bloc_location::operator=(const bloc_location & rhs) {
    this->_config = rhs._config;
    this->_root = rhs._root;
    this->_index = rhs._index;
    return *this;
}


std::string bloc_location::parse_bloc_location() {
    while (!_config._peg_parser.check_is_end_of_bloc('}'))
        _config._peg_parser.find_token(*this, _map_token_list_action, 0);
    set_default_value();
    return std::string("");
}

std::string bloc_location::set_root(){
    _map_token_list_action.erase("root");
    _root = _config._peg_parser.extract_data(';');
    //@todo manage error
    return std::string("");

}

std::string bloc_location::add_index() {
    _map_token_list_action.erase("index");
    std::string index = _config._peg_parser.extract_data(';');
    _index.push_back(index);
    return std::string("");

}

void bloc_location::set_map_token() {
    _map_token_list_action["root"] =  &bloc_location::set_root;
    _map_token_list_action["index"] = &bloc_location::add_index;
}

void bloc_location::set_default_value() {

}

/*
*==========================================================================================================
*|                                                listen data                                             |
*==========================================================================================================
*/


listen_data::listen_data(config_webserv& config, std::string & input)
    : _config(config), _input(input), _sockaddress(){}

listen_data::listen_data(config_webserv& config, std::string default_input)
    : _config(config), _input(default_input), _sockaddress(){
    parse_listen_data();
    set_sockaddr_in();
    set_socket();
    set_socket_option();
    set_bind();
    set_listen();
    set_socket_flag();
}

listen_data::~listen_data() {}
//todo manage close fd at end of programme
/*check if file descriptor is open
 * if process fail throw server::socket_exception();
 */
//    int fd_isopen();

/*check if socket  is open
 * if process fail throw server::socket_exception();
 */
//    int socket_isopen();

listen_data::listen_data(const listen_data& other)
    : _config(other._config), _input(other._input.str()), _ip_address(other._ip_address),
    _port(other._port), _server_socket(other._server_socket), _sockaddress(other._sockaddress){}

listen_data &listen_data::operator=(const listen_data & rhs) {
    this->_config = rhs._config;
    this->_input.str() = rhs._input.str();
    this->_ip_address = rhs._ip_address;
    this->_port = rhs._port;
    this->_server_socket = rhs._server_socket;
    this->_sockaddress = rhs._sockaddress;
    return *this;
}

std::string listen_data::parse_listen_data() {
    std::string port;
    std::getline(_input >> std::ws, _ip_address, ':');
    _input >> port >> std::ws;
    _port = std::atoi(port.c_str());
    //@todo check port and ip
    return std::string("");
}

void listen_data::set_sockaddr_in(){
    _sockaddress.sin_family = AF_INET;
    _sockaddress.sin_addr.s_addr = inet_addr(_ip_address.c_str());
    _sockaddress.sin_port = htons(_port);
}

std::string listen_data::set_socket() {
    _server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_server_socket == 0)
        return std::string(strerror(errno));
    return std::string();
}

std::string listen_data::set_socket_option(){
    int option_val = 1;
    if (setsockopt(_server_socket, IPPROTO_TCP, SO_REUSEADDR,
                   &option_val, (socklen_t)sizeof(option_val))){
        close(_server_socket);
        return std::string(strerror(errno));
    }
    return std::string();
}

std::string listen_data::set_bind() {
    if (bind(_server_socket, reinterpret_cast<struct sockaddr *>(&_sockaddress), sizeof(_sockaddress)) < 0){
        close(_server_socket);
        return std::string(strerror(errno));
    }
    return std::string();
}

std::string listen_data::set_listen() {
    if (listen(_server_socket, _config._bloc_events._worker_connections) < 0){
        close(_server_socket);
        return std::string(strerror(errno));
    }
    return std::string();
}

std::string listen_data::set_socket_flag(){
    int flag = fcntl(_server_socket, F_SETFL, O_NONBLOCK );
    if (flag < 0){
        close(_server_socket);
        return std::string(strerror(errno));
    }
    return std::string();
}


/*
*==========================================================================================================
*|                                                  Bloc server                                             |
*==========================================================================================================
*/


bloc_server::bloc_server(config_webserv&  config)
        : _config(config), _vector_listen(), _vector_server_name(),
        _root(), _map_bloc_location() {
    set_map_token();
}

bloc_server::~bloc_server() {}

bloc_server::bloc_server(const bloc_server& other)
        : _config(other._config), _vector_listen(other._vector_listen),
        _vector_server_name(), _root(), _map_bloc_location() {}

bloc_server &bloc_server::operator=(const bloc_server & rhs) {
    this->_config = rhs._config;
    this->_vector_listen = rhs._vector_listen;
    this->_vector_server_name = rhs._vector_server_name;
    this->_root = rhs._root;
    this->_map_bloc_location = rhs._map_bloc_location;
    return *this;
}

std::string bloc_server::parse_bloc_server() {
    while (!_config._peg_parser.check_is_end_of_bloc('}'))
        _config._peg_parser.find_token(*this, _map_token_list_action, 0);
    set_default_value();
    return std::string("");
}

std::string bloc_server::add_vector_listen(){
    _map_token_list_action.erase("listen");
    std::string value = _config._peg_parser.extract_data(';');
    if (value.empty())
        return std::string("empty");

    value.clear();
    return value;
}

std::string bloc_server::add_vector_server_name(){
    std::string server_name = _config._peg_parser.extract_data(';');
    _vector_server_name.push_back(server_name);
    return std::string("");
}

std::string bloc_server::set_root(){
    _map_token_list_action.erase("root");
    _root = _config._peg_parser.extract_data(';');
    //@todo manage error
    return std::string("");
}

std::string bloc_server::add_map_bloc_location() {
    std::string path = _config._peg_parser.extract_data('{');
    //@todo check path ....
    bloc_location bloc_location(_config);
    bloc_location.parse_bloc_location();
    _map_bloc_location.insert(std::make_pair(path, bloc_location));
    path.clear();
    return path;
}

void bloc_server::set_default_value() {
    if (_vector_listen.empty())
        _vector_listen.push_back(listen_data(_config, "127.0.0.1:8080"));
//    if(_vector_server_name.empty() )
//        _vector_server_name.push_back("default_server.com");
//    if(_root.empty())
//        _root = "/usr/local/var/www";
}

void bloc_server::set_map_token() {
    _map_token_list_action["listen"] =  &bloc_server::add_vector_listen;
    _map_token_list_action["server_name"] =  &bloc_server::add_vector_server_name;
    _map_token_list_action["root"] =  &bloc_server::set_root;
    _map_token_list_action["location"] =  &bloc_server::add_map_bloc_location;
}

/*
*==========================================================================================================
*|                                                  Bloc http                                             |
*==========================================================================================================
*/


bloc_http::bloc_http(config_webserv& config) : _config(config), _map_token_list_action(), _vector_bloc_server() {
    set_map_token();
}

bloc_http::~bloc_http() {}

bloc_http::bloc_http(bloc_http &other)
    : _config(other._config), _map_token_list_action(other._map_token_list_action), _vector_bloc_server(other._vector_bloc_server){}

bloc_http &bloc_http::operator=(const bloc_http &rhs) {
    this->_config = rhs._config;
    this->_vector_bloc_server = rhs._vector_bloc_server;
    this->_map_token_list_action = rhs._map_token_list_action;
    return *this;
}

std::string bloc_http::parse_bloc_http() {
    while (!_config._peg_parser.check_is_end_of_bloc('}'))
        _config._peg_parser.find_token(*this, _map_token_list_action, 0);
    set_default_value();
    return std::string("");
}

std::string bloc_http::add_vector_bloc_server() {
    std::string value = _config._peg_parser.extract_data('{');
    if (value.empty()) {
        bloc_server build_bloc_server(_config);
        value = build_bloc_server.parse_bloc_server();
        _vector_bloc_server.push_back(build_bloc_server);
    }
    return value;
}

void bloc_http::set_default_value() {
    if (_vector_bloc_server.empty()) {
        bloc_server bloc_server(_config);
        bloc_server.set_default_value();
        _vector_bloc_server.push_back(bloc_server);
    }
}

void bloc_http::set_map_token() {
    _map_token_list_action["server"]= &bloc_http::add_vector_bloc_server;
}


/*
*==========================================================================================================
*|                                                  Bloc events                                           |
*==========================================================================================================
*/

bloc_events::bloc_events(config_webserv& config)
    : _config(config), _map_token_list_action(), _worker_connections(){
    set_map_token();
}

bloc_events::~bloc_events() {}

bloc_events::bloc_events(bloc_events &other)
: _config(other._config), _map_token_list_action(other._map_token_list_action), _worker_connections(other._worker_connections) {}


bloc_events &bloc_events::operator=(const bloc_events &rhs) {
   this->_config = rhs._config;
   this->_map_token_list_action = rhs._map_token_list_action;
   this->_worker_connections = rhs._worker_connections;
    return *this;
}


std::string bloc_events::parse_bloc_events() {
    while (!_config._peg_parser.check_is_end_of_bloc('}'))
        _config._peg_parser.find_token(*this, _map_token_list_action, 0);
    set_default_value();
    return std::string("");
}

std::string bloc_events::set_worker_connections() {
    _map_token_list_action.erase("worker_connections");
    std::string value = _config._peg_parser.extract_data(';');
    char * end;//@todo to manage error
    const long val = std::strtol(value.c_str(), &end, 10);
    if (val < 10 || val > 20)
        return value;
    _worker_connections = static_cast<int>(val);
    value.clear();
    return value;
}

void bloc_events::set_default_value() {
    if (_map_token_list_action.size() == 1)
        _worker_connections = 10;
}

void bloc_events::set_map_token() {
    _map_token_list_action["worker_connections"] = &bloc_events::set_worker_connections;
}


/*
*==========================================================================================================
*|                                                  Config server                                         |
*==========================================================================================================
*/

config_webserv::config_webserv() : _peg_parser(),_map_token_list_action(), _worker_process(),
                            _bloc_events(*this), _bloc_http(*this) {
    set_map_token();
    set_default_value();
}

config_webserv::config_webserv(std::string &path_config_file) : _peg_parser(path_config_file.c_str(), "#"),
                                    _map_token_list_action(), _worker_process(), _bloc_events(*this), _bloc_http(*this) {
    set_map_token();
    while (!_peg_parser.check_is_empty()) {
        _peg_parser.find_token(*this, _map_token_list_action, 0);
    }
    set_default_value();
}

config_webserv::~config_webserv() {}

config_webserv::config_webserv(config_webserv & other)
    : _peg_parser(other._peg_parser),_map_token_list_action(other._map_token_list_action),
    _worker_process(other._worker_process), _bloc_events(other._bloc_events), _bloc_http(other._bloc_http){

}

config_webserv &config_webserv::operator=(const config_webserv &rhs) {
    this->_peg_parser = rhs._peg_parser;
    this->_map_token_list_action = rhs._map_token_list_action;
    this->_worker_process = rhs._worker_process;
    this->_bloc_events = rhs._bloc_events;
    this->_bloc_http = rhs._bloc_http;
    return *this;
}


std::string config_webserv::parse_bloc_event() {
    _map_token_list_action.erase("events");
    std::string value = _peg_parser.extract_data('{');
    if (value.empty())
        value = _bloc_events.parse_bloc_events();
    return value;
}

std::string config_webserv::parse_bloc_http() {
    _map_token_list_action.erase("http");
    std::string value = _peg_parser.extract_data('{');
    if (value.empty())
        value = _bloc_http.parse_bloc_http();
//    std::cout << "_vector_bloc_server size:" << " " << _bloc_http._vector_bloc_server.size() << std::endl;
//    std::cout << "_vector_bloc_server 0:" << " " <<_ << std::endl;
    return value;
}

std::string config_webserv::set_worker_processes() {
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

void config_webserv::set_default_value() {
    std::map<std::string, std::string (config_webserv::*)()>::iterator it = _map_token_list_action.begin();
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

void config_webserv::set_map_token() {
    _map_token_list_action["worker_processes"] = &config_webserv::set_worker_processes;
    _map_token_list_action["events"] = &config_webserv::parse_bloc_event;
    _map_token_list_action["http"] = &config_webserv::parse_bloc_http;
}





