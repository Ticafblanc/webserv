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


bloc_location::bloc_location(peg_parser&  peg_parser)
        : _peg_parser(peg_parser), _map_token_list_action(), _root(), _index() {
    _map_token_list_action["root"] =  &bloc_location::set_root;
    _map_token_list_action["index"] =  &bloc_location::add_index;
}

bloc_location::~bloc_location() {}

bloc_location::bloc_location(const bloc_location & other)
        : _peg_parser(other._peg_parser), _root(other._root), _index(other._index) {}

bloc_location &bloc_location::operator=(const bloc_location & rhs) {
    this->_peg_parser = rhs._peg_parser;
    this->_root = rhs._root;
    this->_index = rhs._index;
    return *this;
}


std::string bloc_location::parse_bloc_location() {
    while (!_peg_parser.check_is_end_of_bloc('}'))
        _peg_parser.find_token(*this, _map_token_list_action, 0);
//    set_default_value();
    return std::string("");
}

std::string bloc_location::set_root(){
    _map_token_list_action.erase("root");
    _root = _peg_parser.extract_data(';');
    //@todo manage error
    return std::string("");

}

std::string bloc_location::add_index() {
    std::cout << "add index" << std::endl;
    _map_token_list_action.erase("index");
    std::string index = _peg_parser.extract_data(';');
    _index.push_back(index);
    return std::string("");
}

/*
*==========================================================================================================
*|                                                  Bloc server                                             |
*==========================================================================================================
*/


bloc_server::bloc_server(peg_parser&  peg_parser)
        : _peg_parser(peg_parser), _multimap_listen(), _vector_server_name(),
        _root(), _map_bloc_location() {
    _map_token_list_action["listen"] =  &bloc_server::add_multimap_listen;
    _map_token_list_action["server_name"] =  &bloc_server::add_multimap_listen;
    _map_token_list_action["root"] =  &bloc_server::set_root;
    _map_token_list_action["location"] =  &bloc_server::add_map_bloc_location;
}

bloc_server::~bloc_server() {}

bloc_server::bloc_server(const bloc_server & other)
        : _peg_parser(other._peg_parser), _multimap_listen(other._multimap_listen),
        _vector_server_name(), _root(), _map_bloc_location() {}

bloc_server &bloc_server::operator=(const bloc_server & rhs) {
    this->_peg_parser = rhs._peg_parser;
    this->_multimap_listen = rhs._multimap_listen;
    this->_vector_server_name = rhs._vector_server_name;
    this->_root = rhs._root;
    this->_map_bloc_location = rhs._map_bloc_location;
    return *this;
}

std::string bloc_server::parse_bloc_server() {
    while (!_peg_parser.check_is_end_of_bloc('}'))
        _peg_parser.find_token(*this, _map_token_list_action, 0);
    set_default_value();
    return std::string("");
}

std::string bloc_server::add_multimap_listen(){
    _map_token_list_action.erase("listen");
    std::string value = _peg_parser.extract_data(';');
    if (value.empty())
        return std::string("empty");
    std::string ip, port;
    std::stringstream listen(value);
    while (!listen.eof()) {
        std::getline(listen >> std::ws, ip, ':');
        listen >> port >> std::ws;
        //@todo check port and ip
    }
    value.clear();
    return value;
}

std::string bloc_server::add_vector_server_name(){
    std::cout << "add vector server name" << std::endl;
    std::string server_name;
    _vector_server_name.push_back(server_name);
    return std::string("");
}

std::string bloc_server::set_root(){
    _map_token_list_action.erase("root");
    _root = _peg_parser.extract_data(';');
    //@todo manage error
    return std::string("");
}

std::string bloc_server::add_map_bloc_location() {
    std::string path = _peg_parser.extract_data('{');
    //@todo check path ....
    bloc_location bloc_location(_peg_parser);
    bloc_location.parse_bloc_location();
    _map_bloc_location.insert(std::make_pair(path, bloc_location));
    path.clear();
    return path;
}

void bloc_server::set_default_value() {
    if (_multimap_listen.size() == 0)
        _multimap_listen.insert(std::make_pair(std::string("127.0.0.1"), 8080));
    if(_vector_server_name.size() == 0 )
        _vector_server_name.push_back("default_server.com");
    if(_root.empty())
        _root = "/usr/local/var/www";
}

/*
*==========================================================================================================
*|                                                  Bloc http                                             |
*==========================================================================================================
*/


bloc_http::bloc_http(peg_parser&  peg_parser) : _peg_parser(peg_parser), _map_token_list_action(), _vector_bloc_server() {
    _map_token_list_action["server"]= &bloc_http::add_vector_bloc_server;
}

bloc_http::~bloc_http() {}

std::string bloc_http::parse_bloc_http() {
    while (!_peg_parser.check_is_end_of_bloc('}')) {
        _peg_parser.find_token(*this, _map_token_list_action, 0);
    }
    set_default_value();
    return std::string("");
}

std::string bloc_http::add_vector_bloc_server() {
    std::string value = _peg_parser.extract_data('{');
    if (value.empty()) {
        bloc_server build_bloc_server(_peg_parser);
        value = build_bloc_server.parse_bloc_server();
        _vector_bloc_server.push_back(build_bloc_server);
    }
    return value;
}

void bloc_http::set_default_value() {
    if (_vector_bloc_server.size() == 0) {
        bloc_server bloc_server(_peg_parser);
        bloc_server.set_default_value();
        _vector_bloc_server.push_back(bloc_server);
    }
}

/*
*==========================================================================================================
*|                                                  Bloc events                                           |
*==========================================================================================================
*/

bloc_events::bloc_events(peg_parser&  peg_parser)
    : _peg_parser(peg_parser), _map_token_list_action(), _worker_connections(){
    _map_token_list_action["worker_connections"] = &bloc_events::set_worker_connections;
}

bloc_events::~bloc_events() {}


std::string bloc_events::parse_bloc_events() {
    while (!_peg_parser.check_is_end_of_bloc('}'))
        _peg_parser.find_token(*this, _map_token_list_action, 0);
    set_default_value();
    return std::string("");
}

std::string bloc_events::set_worker_connections() {
    _map_token_list_action.erase("worker_connections");
    std::string value = _peg_parser.extract_data(';');
    int val = std::atoi(value.c_str());
    if (val < 10 || val > 20)
        return value;
    _worker_connections = val;
    value.clear();
    return value;
}

void bloc_events::set_default_value() {
    if (_map_token_list_action.size() == 1)
        _worker_connections = 10;
}


/*
*==========================================================================================================
*|                                                  Config server                                         |
*==========================================================================================================
*/

config_webserv::config_webserv(std::string &path_config_file) : _peg_parser(path_config_file.c_str(), "#"),
                                    _map_token_list_action(), _bloc_events(_peg_parser), _bloc_http(_peg_parser) {

    _map_token_list_action["worker_processes"] = &config_webserv::set_worker_processes;
    _map_token_list_action["events"] = &config_webserv::parse_bloc_event;
    _map_token_list_action["http"] = &config_webserv::parse_bloc_http;

    while (!_peg_parser.check_is_empty()) {
        _peg_parser.find_token(*this, _map_token_list_action, 0);
    }
    set_default_value();
}

config_webserv::~config_webserv() {}

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
    return value;
}

std::string config_webserv::set_worker_processes() {
    _map_token_list_action.erase("worker_processes");
    std::string value = _peg_parser.extract_data(';');
    int val = std::atoi(value.c_str());
    if (val < 1 || val > 4)
        return value;
    _work_process = val;
    value.clear();
    return value;
}

void config_webserv::set_default_value() {
    std::map<std::string, std::string (config_webserv::*)()>::iterator it = _map_token_list_action.begin();
    for (;it != _map_token_list_action.end(); ++it) {
        if (it->first == "worker_processes") {
            _work_process = 1;
        } else if (it->first == "events") {
            _bloc_events.set_default_value();
        } else {
            _bloc_http.set_default_value();
        }
    }
}


