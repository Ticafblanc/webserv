/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_server.class.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <Include/config_server.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

config_server::config_server(std::string path_config_file) : _max_events(), _number_of_server(),
                                                               _vector_config_servers() {

}

config_server::~config_server() {}

config_server::config_server(const config_server &other) : _max_events(other._max_events), _number_of_server(other._number_of_server),
                                                              _vector_config_servers(other._vector_config_servers){}

config_server &config_server::operator=(const config_server &rhs) {
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

config_server::config_exception::config_exception(config_server &config, const char *message) :
        std::exception(), _message(message), _config(config) {}

config_server::config_exception::config_exception(const config_server::config_exception &other) :
        std::exception(), _message(other._message), _config(other._config){}

config_server::config_exception &
config_server::config_exception::operator=(const config_server::config_exception &rhs) {
    this->_message = rhs._message;
    this->_config = rhs._config;
    return *this;
}

config_server::config_exception::~config_exception() throw() {}

const char *config_server::config_exception::what() const throw() { return _message.c_str(); }

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

int config_server::get_max_events() const {
    return _max_events;
}

int config_server::get_number_of_server() const {
    return _number_of_server;
}

std::vector<config_server> config_server::get_vector_config_servers() const {
    return _vector_config_servers;
}

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/