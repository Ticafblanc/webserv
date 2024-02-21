//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include "../Includes/Token.class.hpp"

const string &Token::generateToken() {
  const string characters =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  const int length = 10;
  std::string token;

  do {
    srand(time(NULL));

    for (int i = 0; i < length; ++i) {
      int index = rand() % characters.length();
      token += characters[index];
    }
  } while (!checkToken(token).first);
  _vectorToken.push_back(token);
  return _vectorToken.back();
}

pair<bool, vecStrIt> Token::checkToken(const string &token) {
  for (vecStrIt it = _vectorToken.begin(); it != _vectorToken.end(); ++it) {
    if (*it == token)
      return std::make_pair(false, it);
  }
  return make_pair(true, _vectorToken.end());
}

Token::Token() : _vectorToken() {}

Token::~Token() {}

Token::Token(const Token &other) : _vectorToken(other._vectorToken) {}

Token &Token::operator=(const Token &rhs) {
  if (this != &rhs) {
    this->_vectorToken = rhs._vectorToken;
  }
  return *this;
}

void Token::removeToken(const std::string &token) {
  pair<bool, vecStrIt> check = checkToken(token);
  if (!check.first)
    _vectorToken.erase(check.second);
}
