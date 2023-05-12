#include <Include/parse_config_file.class.hpp>

/*
*==========================================================================================================
*|                                                    t_bloc                                              |
*==========================================================================================================
*/

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

s_bloc::s_bloc() : info_line(), info_bloc() {}

s_bloc::~s_bloc() {}

s_bloc::s_bloc(const s_bloc &other)  : info_line(other.info_line), info_bloc(other.info_bloc) {}

s_bloc &s_bloc::operator=(const s_bloc &rhs) {
    this->info_bloc = rhs.info_bloc;
    this->info_line = rhs.info_line;
    return *this;
}

/*
*==========================================================================================================
*|                                                  parse_config_file                                     |
*==========================================================================================================
*/

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

parse_config_file::parse_config_file(std::string path_config_file) :
                _bloc_config_file(), _webserv_config_file(path_config_file.c_str()){
    std::string     line;
    if (!_webserv_config_file.is_open())
        throw parse_config_file::syntax_exception(*this, strerror(errno));
    while (get_next_line(line)){
        usleep(5000);
        parse_info(_bloc_config_file, line);
    }
    _webserv_config_file.close();
}

parse_config_file::~parse_config_file() {}

parse_config_file::parse_config_file(const parse_config_file &other) :
                _bloc_config_file(other._bloc_config_file), _webserv_config_file(){}

parse_config_file &parse_config_file::operator=(const parse_config_file &rhs) {
    this->_bloc_config_file = rhs._bloc_config_file;
    return *this;
}

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

parse_config_file::syntax_exception::syntax_exception(parse_config_file & config, const char * message) :
                _message(message), _config(config){}

parse_config_file::syntax_exception::syntax_exception(const parse_config_file::syntax_exception & other) :
                _message(other._message), _config(other._config){}

parse_config_file::syntax_exception &
parse_config_file::syntax_exception::operator=(const parse_config_file::syntax_exception &rhs) {
    this->_config = rhs._config;
    this->_message =rhs._message;
    return *this;
}

parse_config_file::syntax_exception::~syntax_exception() throw() {

}

const char *parse_config_file::syntax_exception::what() const throw() { return _message.c_str(); }

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

t_bloc &parse_config_file::get_bloc_config_file() { return _bloc_config_file; }

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/

bool parse_config_file::check_token(std::string & line, std::string token){
    if(line == token){
        line.clear();
        return true;
    }
    throw parse_config_file::syntax_exception(*this, "'{' syntax error");
}

std::string parse_config_file::check_semicolon(std::string & tmp, std::string & line){
    if(*(tmp.end() - 1) == ';' && line.empty()) {
        tmp.erase(tmp.end() - 1);
        return std::string(tmp);
    }
    throw parse_config_file::syntax_exception(*this, "';' syntax error");
}

bool parse_config_file::check_is_empty(std::string & line){
    std::istringstream string_stream(line);
    std::getline(string_stream >> std::ws, line);
    return line.empty();
}

void parse_config_file::delete_comments(std::string & line){
    if (line.find('#') != std::string::npos) {
        line = line.substr(0, line.find('#'));
    }
}

bool parse_config_file::get_next_line(std::string & line){
    while (line.empty() && std::getline(_webserv_config_file, line)){
        delete_comments(line);
        check_is_empty(line);
    }
    return !line.empty();
}

bool parse_config_file::parse_bloc(t_bloc & bloc, std::string & line, std::pair<std::string, std::vector<std::string> > info_line) {
    s_bloc new_bloc;

    do {
        if (line.find('}') != std::string::npos) {
            check_token(line, "}");
            bloc.info_bloc.insert(std::make_pair(info_line, new_bloc));
            return true;
        }
        parse_info(new_bloc, line);
    } while (get_next_line(line));
    return false;
}

void parse_config_file::parse_info(t_bloc & bloc, std::string & line) {
    std::string                 key, tmp;
    std::vector<std::string>    info;

    std::istringstream string_stream(line);
    string_stream >> key >> std::ws;
    string_stream >> tmp >> std::ws;
    while (!tmp.empty() && tmp.find(';') == std::string::npos){
        if((tmp.find('{') != std::string::npos) && check_token(tmp, "{")) {
            parse_bloc(bloc, line, std::make_pair(key, info));
            return;
        }
        info.push_back(tmp);
        string_stream >> tmp >> std::ws;
    }
    string_stream >> line >> std::ws;
    info.push_back(check_semicolon(tmp, line));
    bloc.info_line.insert(std::make_pair(key, info));
}

