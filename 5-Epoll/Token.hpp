//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#ifndef WEBSERVER_TOKEN_HPP
#define WEBSERVER_TOKEN_HPP

#include "0-Main/Includes/Headers.hpp"

class Token {
private:
    std::vector<std::string> _vectorToken;
public:
    Token();

    virtual ~Token();

    Token(const Token& token);

    Token& operator=(const Token& token);

    const std::string & generateToken();
    bool checkToken(const std::string & token);
};
#endif //WEBSERVER_TOKEN_HPP
