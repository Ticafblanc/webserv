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
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

config_webserv::config_webserv(std::string path_config_file) : _max_events(), _number_of_server(),
                                                                _vector_config_servers() {

}

config_webserv::~config_webserv() {}

config_webserv::config_webserv(const config_webserv &other) : _max_events(other._max_events), _number_of_server(other._number_of_server),
                                                              _vector_config_servers(other._vector_config_servers){}

config_webserv &config_webserv::operator=(const config_webserv &rhs) {
    _max_events = rhs._max_events;
    _number_of_server = rhs._number_of_server;
    _vector_config_servers = rhs._vector_config_servers;
    return *this;
}

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

config_webserv::config_exception::config_exception(config_webserv &config, const char *message) :
                                        std::exception(), _message(message), _config(config) {}

config_webserv::config_exception::config_exception(const config_webserv::config_exception &other) :
                                std::exception(), _message(other._message), _config(other._config){}

config_webserv::config_exception &
config_webserv::config_exception::operator=(const config_webserv::config_exception &rhs) {
    this->_message = rhs._message;
    this->_config = rhs._config;
    return *this;
}

config_webserv::config_exception::~config_exception() throw() {}

const char *config_webserv::config_exception::what() const throw() { return _message.c_str(); }

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

int config_webserv::get_max_events() const {
    return _max_events;
}

int config_webserv::get_number_of_server() const {
    return _number_of_server;
}

std::vector<config_server> config_webserv::get_vector_config_servers() const {
    return _vector_config_servers;
}

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/






