///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   config_webserv.class.cpp                           :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
///*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
///*                                                                            */
///* ************************************************************************** */
//
//#include <Include/config_webserv.class.hpp>
//
//
//
///*
//*==========================================================================================================
//*|                                                  Config server                                         |
//*==========================================================================================================
//*/
//
//
//
///*
//*====================================================================================
//*|                                  Member Fonction                                 |
//*====================================================================================
//*/
////@todo if necessarty to store file and webserv i think no
//
//config_server::config_server(std::ifstream &file, config_webserv& webserv) :
//                            _vector_server_name(), _vector_sock_address(), _backlog(){
//    //@todo add parser config to add config server to _vector_config_server
//    //@todo if possible
//    //@todo if key  config_server(file, this);
//
//}
//
//config_server::~config_server() {}
//
//config_server::config_server(const config_server &other) : _max_events(other._max_events), _number_of_server(other._number_of_server),
//                                                           _vector_config_servers(other._vector_config_servers){}
//
//config_server &config_server::operator=(const config_server &rhs) {
//    _max_events = rhs._max_events;
//    _number_of_server = rhs._number_of_server;
//    _vector_config_servers = rhs._vector_config_servers;
//    return *this;
//}
//
///*
//*====================================================================================
//*|                                  Member Exception                                 |
//*====================================================================================
//*/
//
//config_server::config_exception::config_exception(config_server &config, const char *message) :
//        std::exception(), _message(message), _config(config) {}
//
//config_server::config_exception::config_exception(const config_server::config_exception &other) :
//        std::exception(), _message(other._message), _config(other._config){}
//
//config_server::config_exception &
//config_server::config_exception::operator=(const config_server::config_exception &rhs) {
//    this->_message = rhs._message;
//    this->_config = rhs._config;
//    return *this;
//}
//
//config_server::config_exception::~config_exception() throw() {}
//
//const char *config_server::config_exception::what() const throw() { return _message.c_str(); }
//
///*
//*====================================================================================
//*|                                  Element access                                 |
//*====================================================================================
//*/
//
//int config_server::get_max_events() const {
//    return _max_events;
//}
//
//int config_server::get_number_of_server() const {
//    return _number_of_server;
//}
//
//std::vector<config_server> config_server::get_vector_config_servers() const {
//    return _vector_config_servers;
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
//                                                                _vector_config_servers() {
//    std::ifstream file(path_config_file.c_str());
//    //@todo add parser config to add config server to _vector_config_server
//    //@todo if possible to set [0] server local ?
//    //@todo if key server config_server(file, this);
//}
//
//config_webserv::~config_webserv() {}
//
//config_webserv::config_webserv(const config_webserv &other) : _max_events(other._max_events), _number_of_server(other._number_of_server),
//                                                              _vector_config_servers(other._vector_config_servers){}
//
//config_webserv &config_webserv::operator=(const config_webserv &rhs) {
//    _max_events = rhs._max_events;
//    _number_of_server = rhs._number_of_server;
//    _vector_config_servers = rhs._vector_config_servers;
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
//std::vector<config_server> config_webserv::get_vector_config_servers() const {
//    return _vector_config_servers;
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
