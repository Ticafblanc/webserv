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

#include <Include/config_webserv.class.hpp>

/*
*==========================================================================================================
*|                                                  Bloc server                                             |
*==========================================================================================================
*/


bloc_server::bloc_server() {}

bloc_server::~bloc_server() {}

std::string bloc_server::parse_bloc_server(peg_parser & peg) {
    (void)peg;
    std::cout << "in parse server" << std::endl;
    std::map<std::string, string (*)(peg_parser &)>  map_token_list_action;
    map_token_list_action.insert(std::make_pair(std::string("server"), &add_vector_bloc_server));
    peg.parse(map_token_list_action);

    return std::string("");
}

//std::string add_vector_bloc_server(peg_parser & peg) {
//    (void)peg;
//    std::cout << "in parse bloc server" << std::endl;
//
//    return std::string("");
//}


/*
*==========================================================================================================
*|                                                  Bloc http                                             |
*==========================================================================================================
*/


bloc_http::bloc_http() : _vector_bloc_server() {}

bloc_http::~bloc_http() {}

std::string parse_bloc_http(peg_parser & peg) {
    (void)peg;
    std::cout << "in parse http" << std::endl;
    std::map<std::string, string (*)(peg_parser &)>  map_token_list_action;
    map_token_list_action.insert(std::make_pair(std::string("server"), &add_vector_bloc_server));
    peg.parse(map_token_list_action);

    return std::string("");
}

std::string add_vector_bloc_server(peg_parser & peg) {
    (void)peg;
    std::cout << "in parse bloc server" << std::endl;
    this->
    _veparse_bloc_server(peg);
    return std::string("");
}


/*
*==========================================================================================================
*|                                                  Bloc events                                           |
*==========================================================================================================
*/


bloc_events::bloc_events() : _work_connection(){}

bloc_events::~bloc_events() {}

std::string parse_bloc_events(peg_parser & peg) {
    (void)peg;
    std::cout << "in parse events" << std::endl;
    std::map<std::string, string (*)(peg_parser &)>  map_token_list_action;
    map_token_list_action.insert(std::make_pair(std::string("work_connection"), &set_work_connection));
    peg.parse(map_token_list_action);

    return std::string("");
}

std::string set_work_connection(peg_parser & peg) {
    (void)peg;
    std::cout << "in parse work connection" << std::endl;


    return std::string("");
}


/*
*==========================================================================================================
*|                                                  Config server                                         |
*==========================================================================================================
*/


config_webserv::config_webserv(std::string &path_config_file) : _peg_parser(path_config_file),
                                    _bloc_events(), _bloc_http() {
    std::map<std::string, string (*)(peg_parser&)>  map_token_list_action;
    map_token_list_action.insert(std::make_pair(std::string("events"), &set_bloc_event));
    map_token_list_action.insert(std::make_pair(std::string("http"), &set_bloc_http));
    _peg_parser.parse(map_token_list_action);
}

config_webserv::~config_webserv() {}

std::string set_bloc_event(config_webserv& webserv, peg_parser & peg) {
    (void)peg;
    std::cout << "in parse events" << std::endl;
    parse_bloc_events(peg);
    (void)webserv._peg_parser;
    return std::string("");
}

std::string set_bloc_http(config_webserv& webserv, peg_parser & peg) {
    (void)peg;
    std::cout << "in parse http" << std::endl;
    (void)webserv;
    parse_bloc_http(peg);
    return std::string("");
}










































//
///*
//*====================================================================================
//*|                                  private fonction utils                          |
//*====================================================================================
//*/
//
//
//
//
///*
//*==========================================================================================================
//*|                                                  Config Webserv                                        |
//*==========================================================================================================
//*/
//
//
//
//
//
///*
//*====================================================================================
//*|                                  Member Fonction                                 |
//*====================================================================================
//*/
//
//config_webserv::config_webserv(std::string path_config_file) : _max_events(), _number_of_server(),
//                                                                _vector_config_webservs() {
//    std::ifstream file(path_config_file.c_str());
//    //@todo add parser config to add config server to _vector_config_webserv
//    //@todo if possible to set [0] server local ?
//    //@todo if key server config_webserv(file, this);
//}
//
//config_webserv::~config_webserv() {}
//
//config_webserv::config_webserv(const config_webserv &other) : _max_events(other._max_events), _number_of_server(other._number_of_server),
//                                                              _vector_config_webservs(other._vector_config_webservs){}
//
//config_webserv &config_webserv::operator=(const config_webserv &rhs) {
//    _max_events = rhs._max_events;
//    _number_of_server = rhs._number_of_server;
//    _vector_config_webservs = rhs._vector_config_webservs;
//    return *this;
//}
//
///*
//*====================================================================================
//*|                                  Member Exception                                 |
//*====================================================================================
//*/
//
//config_webserv::config_exception::config_exception(config_webserv &config, const char *message) :
//                                        std::exception(), _message(message), _config(config) {}
//
//config_webserv::config_exception::config_exception(const config_webserv::config_exception &other) :
//                                std::exception(), _message(other._message), _config(other._config){}
//
//config_webserv::config_exception &
//config_webserv::config_exception::operator=(const config_webserv::config_exception &rhs) {
//    this->_message = rhs._message;
//    this->_config = rhs._config;
//    return *this;
//}
//
//config_webserv::config_exception::~config_exception() throw() {}
//
//const char *config_webserv::config_exception::what() const throw() { return _message.c_str(); }
//
///*
//*====================================================================================
//*|                                  Element access                                 |
//*====================================================================================
//*/
//
//int config_webserv::get_max_events() const {
//    return _max_events;
//}
//
//int config_webserv::get_number_of_server() const {
//    return _number_of_server;
//}
//
//std::vector<config_webserv> config_webserv::get_vector_config_webservs() const {
//    return _vector_config_webservs;
//}
//
///*
//*====================================================================================
//*|                                  private fonction utils                          |
//*====================================================================================
//*/
//
//
//
//
//
//
