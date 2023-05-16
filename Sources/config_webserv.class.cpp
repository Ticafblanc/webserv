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
        : _peg_parser(peg_parser), _root(), _index() {}

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
    std::cout << "in parse location" << std::endl;
    std::map<std::string, std::string (bloc_location::*)()>  map_token_list_action;
    map_token_list_action["root"] =  &bloc_location::set_root;
    map_token_list_action["index"] =  &bloc_location::add_index;
//    _peg_parser.find_token<bloc_location>(map_token_list_action, 0);

    return std::string("");
}

std::string bloc_location::set_root(){
    std::cout << "set root" << std::endl;
    std::string root;
    _root = root;
    return std::string("");

}

std::string bloc_location::add_index() {
    std::cout << "add index" << std::endl;
    std::string index;
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
        _root(), _vector_bloc_location() {}

bloc_server::~bloc_server() {}

bloc_server::bloc_server(const bloc_server & other)
        : _peg_parser(other._peg_parser), _multimap_listen(other._multimap_listen),
        _vector_server_name(), _root(), _vector_bloc_location() {}

bloc_server &bloc_server::operator=(const bloc_server & rhs) {
    this->_peg_parser = rhs._peg_parser;
    this->_multimap_listen = rhs._multimap_listen;
    this->_vector_server_name = rhs._vector_server_name;
    this->_root = rhs._root;
    this->_vector_bloc_location = rhs._vector_bloc_location;
    return *this;
}

std::string bloc_server::parse_bloc_server() {
    std::cout << "in parse server" << std::endl;
    //todo find {
    std::map<std::string, std::string (bloc_server::*)()>  map_token_list_action;
    map_token_list_action["listen"] =  &bloc_server::add_multimap_listen;
    map_token_list_action["server_name"] =  &bloc_server::add_multimap_listen;
    map_token_list_action["root"] =  &bloc_server::set_root;
//    _peg_parser.find_token<bloc_server>(map_token_list_action, 0);

    return std::string("");
}

std::string bloc_server::add_multimap_listen(){
    std::cout << "add multimap listen" << std::endl;
    std::pair<std::string, int> listen;
    _multimap_listen.insert(listen);
    return std::string("");

}

std::string bloc_server::add_vector_server_name(){
    std::cout << "add vector server name" << std::endl;
    std::string server_name;
    _vector_server_name.push_back(server_name);
    return std::string("");
}

std::string bloc_server::set_root(){
    std::cout << "set root" << std::endl;
    std::string root;
    _root = root;
    return std::string("");
}

std::string bloc_server::add_vector_bloc_location() {
    std::cout << "add vector bloc location" << std::endl;
    bloc_location bloc_location(_peg_parser);
    _vector_bloc_location.push_back(bloc_location);
    return std::string("");

}

/*
*==========================================================================================================
*|                                                  Bloc http                                             |
*==========================================================================================================
*/


bloc_http::bloc_http(peg_parser&  peg_parser) : _peg_parser(peg_parser), _vector_bloc_server() {}

bloc_http::~bloc_http() {}

std::string bloc_http::parse_bloc_http() {
    std::cout << "in parse http" << std::endl;
    std::map<std::string, std::string (bloc_http::*)()>  map_token_list_action;
    map_token_list_action["server"]= &bloc_http::add_vector_bloc_server;
//    _peg_parser.find_token<bloc_http>(map_token_list_action, 0);

    return std::string("");
}

std::string bloc_http::add_vector_bloc_server() {
    std::cout << "in parse bloc server" << std::endl;
    bloc_server build_bloc_server(_peg_parser);
    build_bloc_server.parse_bloc_server();
    _vector_bloc_server.push_back(build_bloc_server);
    return std::string("");
}


/*
*==========================================================================================================
*|                                                  Bloc events                                           |
*==========================================================================================================
*/

bloc_events::bloc_events(peg_parser&  peg_parser) : _peg_parser(peg_parser), _work_connection(){}

bloc_events::~bloc_events() {}


std::string bloc_events::parse_bloc_events() {
    std::cout << "in parse events" << std::endl;
    std::map<std::string, std::string (bloc_events::*)()>  map_token_list_action;
    map_token_list_action["work_connection"] = &bloc_events::set_work_connection;
//    _peg_parser.find_token(map_token_list_action, 0);
    return std::string("");
}

std::string bloc_events::set_work_connection() {
    std::cout << "in parse work connection" << std::endl;

    return std::string("");
}


/*
*==========================================================================================================
*|                                                  Config server                                         |
*==========================================================================================================
*/


config_webserv::config_webserv(std::string &path_config_file) : _peg_parser(path_config_file),
                                    _bloc_events(_peg_parser), _bloc_http(_peg_parser) {
    std::map<std::string, std::string (config_webserv::*)()>  map_token_list_action;
    map_token_list_action["events"] = &config_webserv::parse_bloc_event;
    map_token_list_action["http"] = &config_webserv::parse_bloc_http;
    _peg_parser.find_token(map_token_list_action, 0);
//    _peg_parser.extract_data('c');
}

config_webserv::~config_webserv() {}

std::string config_webserv::parse_bloc_event() {
//    _bloc_events.parse_bloc_events();
    return std::string("in parse events fonction ");
}

std::string config_webserv::parse_bloc_http() {
//    _bloc_http.parse_bloc_http();
    return std::string("in parse http fonction ");
}


