//
// Created by Matthis DoQuocBao on 2023-05-31.
//

#include "Include/client.class.hpp"

client::client(char stateFlag, blocServer &server) : _stateFlag(stateFlag), _server(server) {}

client::~client() {

}

