//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include <Source_Code/2-Engin/Includes/Token.hpp>

const std::string &Token::generateToken() {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int length = 10;
    std::string token;

     do {
        srand(time(NULL));

        for (int i = 0; i < length; ++i) {
            int index = rand() % characters.length();
            token += characters[index];
        }
    }while(!checkToken(token).first);
    _vectorToken.push_back(token);
    return _vectorToken.back();
}

std::pair<bool, std::vector<std::string>::iterator> Token::checkToken(const std::string &token) {
    for(std::vector<std::string>::iterator it = _vectorToken.begin();
    it != _vectorToken.end(); ++it){
        if (*it == token)
            return std::make_pair(false, it);
    }
    return std::make_pair(true, _vectorToken.end());
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

void Token::removeToken(const std::string &token) {
    std::pair<bool, std::vector<std::string>::iterator> check = checkToken(token);
    if (!check.first)
        _vectorToken.erase(check.second);
}