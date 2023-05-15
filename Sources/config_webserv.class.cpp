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
*|                                                  Config server                                         |
*==========================================================================================================
*/



/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

config_webserv::config_webserv(std::string &path_config_file) : _peg_parser(path_config_file) {
    std::map<std::string, string (*)(std::stringstream &)>  map_token_list_action;
    map_token_list_action.insert(std::make_pair(std::string("events"), &set_bloc_event));
    map_token_list_action.insert(std::make_pair(std::string("http"), &set_bloc_http));
    _peg_parser.parse(map_token_list_action);
}

config_webserv::~config_webserv() {}



/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

std::string set_bloc_event(std::stringstream & string_stream) {
    (void)string_stream;
    std::cout << "in parse events" << std::endl;

    std::cout << string_stream.str() << std::endl;

    return std::string("");
}

std::string set_bloc_http(std::stringstream& string_stream) {
    (void)string_stream;
    std::cout << "in parse http" << std::endl;
    std::cout << string_stream.str() << std::endl;

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
