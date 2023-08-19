//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#ifndef WEBSERVER_TOKEN_CLASS_HPP
#define WEBSERVER_TOKEN_CLASS_HPP

#include <iostream>
#include <vector>
#include <cstdlib>

class Token {
private:
    std::vector<std::string>                      _vectorToken;
public:
    Token();

    virtual ~Token();

    Token(const Token& token);

    Token& operator=(const Token& token);

    const std::string & generateToken();
    void removeToken(const std::string &token);
    std::pair<bool, std::vector<std::string>::iterator> checkToken(const std::string & token);
};
#endif //WEBSERVER_TOKEN_CLASS_HPP
