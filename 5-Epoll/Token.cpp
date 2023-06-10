//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include "Token.hpp"

const std::string &Token::generateToken() {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int length = 10;
    std::string token = _vectorToken[0];

    while(checkToken(token)) {
        srand(time(NULL));

        for (int i = 0; i < length; ++i) {
            int index = rand() % characters.length();
            token += characters[index];
        }
    }
    _vectorToken.push_back(token);
    return _vectorToken.back();
}

bool Token::checkToken(const string &token) {
    for(std::vector<std::string>::iterator it = _vectorToken.begin();
    it != _vectorToken.end(); ++it){
        if (*it == token)
            return false;
    }
    return true;
}

Token::Token() : _vectorToken() {}

Token::~Token() {}

Token::Token(const Token &other) : _vectorToken(other._vectorToken){}

Token &Token::operator=(const Token &rhs) {
    if (this != &rhs) {
        this->_vectorToken = rhs._vectorToken;
    }
    return *this;
}
