//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/Execute.class.hpp>

Execute::Execute(HttpRequest& httpRequest, Config & config, Socket& client)
        : _httpRequest(httpRequest), _config(config), _mapMethode(), _client(client){
    buildMapMethode();
}

Execute::~Execute() {}

Execute::Execute(const Execute & other)
        : _httpRequest(other._httpRequest), _config(other._config), _client(other._client){}

Execute &Execute::operator=(const Execute &rhs) {
    this->_httpRequest = rhs._httpRequest;
    this->_config = rhs._config;
    this->_client = rhs._client;
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
    std::ifstream logfile("/webserv/var/www/default.com/index.html");
    if (!logfile.is_open())
        throw Execute::executeException(strerror(errno));
    std::string line;
    while (std::getline(logfile, line)) {
        _client.getclient()._content += line;
    }
    logfile.close();


    _client.getclient()._contentType = "text/html";
}

void Execute::POSTmethode() {
    std::string url = _httpRequest.getUrl();
    //todo find location
    //vald methode
    //execute request
    //build reponse
    _client.getclient()._content = "<!DOCTYPE html>\n"
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
    _client.getclient()._contentType = "text/html";

}

void Execute::DELETEmethode() {
    std::string url = _httpRequest.getUrl();
    //todo find location
    //vald methode
    //execute request

}

std::string Execute::getReponse() {
    return _client.getclient()._content;
}

std::string Execute::getContentType() {
    return _client.getclient()._contentType;
}




/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/


void Execute::executeRequest(std::string & tokenServer) {
    try {
        if (tokenServer.empty())
            throw 404;
        _tokenServer = tokenServer;
        selectMethode();
    }
    catch (int & error){
        _client.getclient()._content = "<!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
        "<title>"+ _config._code.getStatusCode(error) +"</title>\n"
        "<style>\n"
        "html { color-scheme: light dark; }\n"
        "body { width: 35em; margin: 0 auto;\n"
        "font-family: Tahoma, Verdana, Arial, sans-serif; }\n"
        "</style>\n"
        "</head>\n"
        "<body>\n"
        "<h1>" + _config._code.getStatusCode(error) + "</h1>\n"
        "<p>Sorry</p>\n"
        "</body>\n"
        "</html>";
        _client.getclient()._contentType = "text/html";
    }



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
