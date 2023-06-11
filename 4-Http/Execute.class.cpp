//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include "Execute.class.hpp"

Execute::Execute(HttpRequest& httpRequest, Config & config)
        : _httpRequest(httpRequest), _config(config), _mapMethode(), _reponse(), _contentType(){
    buildMapMethode();
}

Execute::~Execute() {}

Execute::Execute(const Execute & other)
        : _httpRequest(other._httpRequest), _config(other._config){}

Execute &Execute::operator=(const Execute &rhs) {
    this->_httpRequest = rhs._httpRequest;
    this->_config = rhs._config;
    return *this;
}

void Execute::buildMapMethode(){
    _mapMethode["GET"] = &Execute::GETmethode;
    _mapMethode["POST"] = &Execute::POSTmethode;
    _mapMethode["DELETE"] = &Execute::DELETEmethode;
}


void Execute::selectMethode() {
    (this->*_mapMethode[_httpRequest.getMethode()])();
}

void Execute::selectLocation() {
}

void Execute::GETmethode() {
   std::string url = _httpRequest.getUrl();
   selectLocation();
   //todo find location
   //vald methode"/usr/local/var/www/index.html"
   //build _reponse
   _reponse = "<!DOCTYPE html>\n"
              "<html>\n"
              "<head>\n"
              "<title>Welcome to nginx!</title>\n"
              "<style>\n"
              "html { color-scheme: light dark; }\n"
              "body { width: 35em; margin: 0 auto;\n"
              "font-family: Tahoma, Verdana, Arial, sans-serif; }\n"
              "</style>\n"
              "</head>\n"
              "<body>\n"
              "<h1>Welcome to nginx!</h1>\n"
              "<p>If you see this page, the nginx web serverSocket is successfully installed and\n"
              "working. Further configuration is required.</p>\n"
              "\n"
              "<p>For online documentation and support please refer to\n"
              "<a href=\"http://nginx.org/\">nginx.org</a>.<br/>\n"
              "Commercial support is available at\n"
              "<a href=\"http://nginx.com/\">nginx.com</a>.</p>\n"
              "\n"
              "<p><em>Thank you for using nginx.</em></p>\n"
              "</body>\n"
              "</html>";
    _contentType = "text/html";
}

void Execute::POSTmethode() {
    std::string url = _httpRequest.getUrl();
    //todo find location
    //vald methode
    //execute request
    //build reponse
    _reponse = "<!DOCTYPE html>\n"
               "<html>\n"
               "<head>\n"
               "<title>Welcome to nginx!</title>\n"
               "<style>\n"
               "html { color-scheme: light dark; }\n"
               "body { width: 35em; margin: 0 auto;\n"
               "font-family: Tahoma, Verdana, Arial, sans-serif; }\n"
               "</style>\n"
               "</head>\n"
               "<body>\n"
               "<h1>Welcome to nginx!</h1>\n"
               "<p>If you see this page, the nginx web serverSocket is successfully installed and\n"
               "working. Further configuration is required.</p>\n"
               "\n"
               "<p>For online documentation and support please refer to\n"
               "<a href=\"http://nginx.org/\">nginx.org</a>.<br/>\n"
               "Commercial support is available at\n"
               "<a href=\"http://nginx.com/\">nginx.com</a>.</p>\n"
               "\n"
               "<p><em>Thank you for using nginx.</em></p>\n"
               "</body>\n"
               "</html>";
    _contentType = "text/html";

}

void Execute::DELETEmethode() {
    std::string url = _httpRequest.getUrl();
    //todo find location
    //vald methode
    //execute request

}

std::string Execute::getReponse() {
    return _reponse;
}

std::string Execute::getContentType() {
    return _contentType;
}




/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/


void Execute::executeRequest(std::string & tokenServer) {
    _tokenServer = tokenServer;
    selectMethode();

}


/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

Execute::executeException::executeException(const char * message) : _message(message) {}

Execute::executeException::~executeException() throw() {}

const char * Execute::executeException::what() const throw() { return _message.c_str(); }

Execute::executeException::executeException(const Execute::executeException & other) : _message(other._message) {}

Execute::executeException &Execute::executeException::operator=(const Execute::executeException &rhs) {
    this->_message = rhs._message;
    return *this;
}
