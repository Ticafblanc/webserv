#include <Include/peg_parser.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

peg_parser::peg_parser() {}

peg_parser::peg_parser(std::string & path_config_file) {
    std::ifstream       file_to_parse(path_config_file.c_str());

    if (!file_to_parse.is_open())
        throw peg_parser::syntax_exception(strerror(errno), __LINE__ );
    std::copy(std::istreambuf_iterator<char>(file_to_parse),
              std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(_string_stream));
    file_to_parse.close();
}

peg_parser::~peg_parser() { }

/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

bool peg_parser::parse(std::map<std::string, std::string (*)(std::stringstream &)> & map_token_list_action) {
    (void)map_token_list_action;
    std::cout << _string_stream.str() << std::endl;
    map_token_list_action.find("events")->second(_string_stream);
    map_token_list_action.find("http")->second(_string_stream);

    return false;
}

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

peg_parser::syntax_exception::syntax_exception(const char * message, int line) :
                _message(message){
    std::ostringstream oss;
    oss << line;
    _message += " line error => ";
    _message += oss.str();
}

peg_parser::syntax_exception::syntax_exception(const peg_parser::syntax_exception & other) :
                _message(other._message) {}

peg_parser::syntax_exception &
peg_parser::syntax_exception::operator=(const peg_parser::syntax_exception &rhs) {
    this->_message =rhs._message;
    return *this;
}

peg_parser::syntax_exception::~syntax_exception() throw() { }

const char *peg_parser::syntax_exception::what() const throw() { return _message.c_str(); }

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/

bool peg_parser::check_is_empty(std::string & buffer_line){
    _string_stream.str(buffer_line);
    std::getline(_string_stream >> std::ws, buffer_line);
    return buffer_line.empty();
}

void peg_parser::delete_comments(std::string & buffer_line){
    if (buffer_line.find('#') != std::string::npos)
        buffer_line = buffer_line.substr(0, buffer_line.find('#'));
}

bool peg_parser::get_next_line(){
    std::string         buffer_line;

//    while (check_is_empty(buffer_line) && std::getline(_webserv_config_file, buffer_line))
//        delete_comments(buffer_line);

    return !buffer_line.empty();
}

void peg_parser::parse_bloc(std::pair<std::string, std::vector<std::string> > info_line) {
//    s_bloc new_bloc;
    log_error(info_line.first, info_line.second);
//    while (parse_info(new_bloc));
//    bloc.info_bloc.insert(std::make_pair(info_line, new_bloc));
}

bool peg_parser::is_token(std::string& token){
    (void)token;
//    return (white_space != identify_token(token[0]) && token.length() == 1);
    return true;
}

bool peg_parser::identify_flag_token(char token){
    (void)token;
//    return (_flag_token == identify_token(token));
    return true;
}

int peg_parser::identify_token(char token){
    (void)token;
    int flag_token = 0;
//    switch (token) {
//        case '{' :
//            flag_token = open_bracket;
//            break;
//        case '}' :
//            flag_token = close_bracket;
//            break;
//        case ';' :
//            flag_token = semicolon;
//            break;
//        default:
//            flag_token = white_space;
//            break;
//    }
    return flag_token;
}

void peg_parser::set_flag_token(char token){
    (void)token;
//   _flag_token = identify_token(token);
}

void peg_parser::find_token(std::string & word){
    (void)word;//    set_flag_token(_token_list[white_space]);
//    for (std::size_t word_size = 0; word_size < word.length() ; ++word_size) {
//        for (std::size_t token_list_size = 0; token_list_size < _token_list.length() ; ++token_list_size) {
//            if (word[word_size] == _token_list[token_list_size]) {
//                set_flag_token(word[token_list_size]);
//                if(word_size == 0)
//                    word += _token_list[token_list_size];
//                word = word.substr(0, word_size);
//            }
//        }
//    }
//    std::remove_if(_buffer_line.begin(), _buffer_line.end())
//    _buffer_line.erase(std::remove_if(result.begin(), result.end(), [](char c) {
//        return std::isspace(static_cast<unsigned char>(c));
//    }), result.end())
//    _buffer_line = _buffer_line.substr(word.length());
//    if (_buffer_line.empty())
//        get_next_line();
}

bool peg_parser::find_next_word(std::string & word){
    word.clear();
    if (static_cast<unsigned long>(_string_stream.tellg()) == _string_stream.str().size())
        get_next_line();
//    std::istringstream string_stream(_buffer_line);
//    string_stream >> word >> std::ws;
//    size_t number_of_whit_space = string_stream.str().size();
//    (void)number_of_whit_space;
    find_token(word);
    if(is_token(word) || word.empty())
        return false;
    return true;
}

bool peg_parser::parse_info() {
    std::string key, tmp;
    std::vector<std::string> info;

//    if (find_next_word(key)) {
//        while (find_next_word(tmp))
//            info.push_back(tmp);
//        if (identify_flag_token('{')) {
//            _indente_log += '\t';
//            parse_bloc(bloc, std::make_pair(key, info));
//            _indente_log.erase(_indente_log.end() - 1);
//            return true;
//        }
//        else if (identify_flag_token('}')) {
//            throw peg_parser::syntax_exception(*this, "expected token", __LINE__ );
//        }
//        else if (identify_flag_token(';')) {
//            log_error(key, info);
//            bloc.info_line.insert(std::make_pair(key, info));
//            return true;
//        }
//    }
    return false;
}

void peg_parser::log_error(std::string & key, std::vector<std::string> & info){
    (void)key;
//    std::cout << _indente_log << "key = " << key << "info = ";
    for(std::vector<std::string>::iterator it = info.begin(); it != info.end(); ++it)
        std::cout << *it << " ";
    std::cout<<std::endl;
}











///*
//*==========================================================================================================
//*|                                                    t_bloc                                              |
//*==========================================================================================================
//*/
//
///*
//*====================================================================================
//*|                                  Member Fonction                                 |
//*====================================================================================
//*/
//
//s_bloc::s_bloc() : info_line(), info_bloc() {}
//
//s_bloc::~s_bloc() {}
//
//s_bloc::s_bloc(const s_bloc &other)  : info_line(other.info_line), info_bloc(other.info_bloc) {}
//
//s_bloc &s_bloc::operator=(const s_bloc &rhs) {
//    this->info_bloc = rhs.info_bloc;
//    this->info_line = rhs.info_line;
//    return *this;
//}
//
///*
//*==========================================================================================================
//*|                                                  parse_config_file                                     |
//*==========================================================================================================
//*/
//
///*
//*====================================================================================
//*|                                  Member Fonction                                 |
//*====================================================================================
//*/
//
//parse_config_file::parse_config_file(std::string path_config_file) :
//                _bloc_config_file(), _string_stream(), _token_list(), _flag_token(){
//    std::ifstream       webserv_config_file(path_config_file.c_str());
//    if (!webserv_config_file.is_open())
//        throw parse_config_file::syntax_exception(*this, strerror(errno), __LINE__ );
//    std::copy(std::istreambuf_iterator<char>(webserv_config_file),
//            std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(_string_stream));
//    parse_bloc(_bloc_config_file, std::make_pair(std::string(), std::vector<std::string>()));
//    webserv_config_file.close();
//}
//
//parse_config_file::~parse_config_file() {}
//
//parse_config_file::parse_config_file(const parse_config_file &other) :
//                _bloc_config_file(other._bloc_config_file)
//                _token_list(other._token_list), _flag_token(other._flag_token){}
//
//parse_config_file &parse_config_file::operator=(const parse_config_file &rhs) {
//    this->_bloc_config_file = rhs._bloc_config_file;
//    this->_token_list = rhs._token_list;
//    this->_flag_token = rhs._flag_token;
//    return *this;
//}
//
///*
//*====================================================================================
//*|                                  Member Exception                                 |
//*====================================================================================
//*/
//
//parse_config_file::syntax_exception::syntax_exception(parse_config_file & config, const char * message, int line) :
//                _message(message), _config(config), _line(line){
//    std::ostringstream oss;
//    oss << line;
//    _message += " line error => ";
//    _message += oss.str();
//}
//
//parse_config_file::syntax_exception::syntax_exception(const parse_config_file::syntax_exception & other) :
//                _message(other._message), _config(other._config){}
//
//parse_config_file::syntax_exception &
//parse_config_file::syntax_exception::operator=(const parse_config_file::syntax_exception &rhs) {
//    this->_config = rhs._config;
//    this->_message =rhs._message;
//    return *this;
//}
//
//parse_config_file::syntax_exception::~syntax_exception() throw() {
//
//}
//
//const char *parse_config_file::syntax_exception::what() const throw() { return _message.c_str(); }
//
///*
//*====================================================================================
//*|                                  Element access                                 |
//*====================================================================================
//*/
//
//t_bloc &parse_config_file::get_bloc_config_file() { return _bloc_config_file; }
//
///*
//*====================================================================================
//*|                                  private fonction utils                          |
//*====================================================================================
//*/
//
//bool parse_config_file::check_is_empty(std::string & buffer_line){
//    _string_stream.str(buffer_line);
//    std::getline(_string_stream >> std::ws, buffer_line);
//    return buffer_line.empty();
//}
//
//void parse_config_file::delete_comments(std::string & buffer_line){
//    if (buffer_line.find('#') != std::string::npos)
//        buffer_line = buffer_line.substr(0, buffer_line.find('#'));
//}
//
//bool parse_config_file::get_next_line(){
//    std::string         buffer_line;
//
//    while (check_is_empty(buffer_line) && std::getline(_webserv_config_file, buffer_line))
//        delete_comments(buffer_line);
//
//    return !buffer_line.empty();
//}
//
//void parse_config_file::parse_bloc(t_bloc & bloc, std::pair<std::string, std::vector<std::string> > info_line) {
//    s_bloc new_bloc;
//    log_error(info_line.first, info_line.second);
//    while (parse_info(new_bloc));
//    bloc.info_bloc.insert(std::make_pair(info_line, new_bloc));
//}
//
//bool parse_config_file::is_token(std::string& token){
//    return (white_space != identify_token(token[0]) && token.length() == 1);
//}
//
//bool parse_config_file::identify_flag_token(char token){
//    return (_flag_token == identify_token(token));
//}
//
//int parse_config_file::identify_token(char token){
//    int flag_token;
//    switch (token) {
//        case '{' :
//            flag_token = open_bracket;
//            break;
//        case '}' :
//            flag_token = close_bracket;
//            break;
//        case ';' :
//            flag_token = semicolon;
//            break;
//        default:
//            flag_token = white_space;
//            break;
//    }
//    return flag_token;
//}
//
//void parse_config_file::set_flag_token(char token){
//   _flag_token = identify_token(token);
//}
//
//void parse_config_file::find_token(std::string & word){
//    set_flag_token(_token_list[white_space]);
//    for (std::size_t word_size = 0; word_size < word.length() ; ++word_size) {
//        for (std::size_t token_list_size = 0; token_list_size < _token_list.length() ; ++token_list_size) {
//            if (word[word_size] == _token_list[token_list_size]) {
//                set_flag_token(word[token_list_size]);
//                if(word_size == 0)
//                    word += _token_list[token_list_size];
//                word = word.substr(0, word_size);
//            }
//        }
//    }
////    std::remove_if(_buffer_line.begin(), _buffer_line.end())
////    _buffer_line.erase(std::remove_if(result.begin(), result.end(), [](char c) {
////        return std::isspace(static_cast<unsigned char>(c));
////    }), result.end())
//    _buffer_line = _buffer_line.substr(word.length());
//    if (_buffer_line.empty())
//        get_next_line();
//}
//
//bool parse_config_file::find_next_word(std::string & word){
//    word.clear();
//    if (static_cast<unsigned long>(_string_stream.tellg()) == _string_stream.str().size())
//        get_next_line();
//    std::istringstream string_stream(_buffer_line);
//    string_stream >> word >> std::ws;
//    size_t number_of_whit_space = string_stream.str().size();
//    (void)number_of_whit_space;
//    find_token(word);
//    if(is_token(word) || word.empty())
//        return false;
//    return true;
//}
//
//bool parse_config_file::parse_info(t_bloc & bloc) {
//    std::string key, tmp;
//    std::vector<std::string> info;
//
//    if (find_next_word(key)) {
//        while (find_next_word(tmp))
//            info.push_back(tmp);
//        if (identify_flag_token('{')) {
//            _indente_log += '\t';
//            parse_bloc(bloc, std::make_pair(key, info));
//            _indente_log.erase(_indente_log.end() - 1);
//            return true;
//        }
//        else if (identify_flag_token('}')) {
//            throw parse_config_file::syntax_exception(*this, "expected token", __LINE__ );
//        }
//        else if (identify_flag_token(';')) {
//            log_error(key, info);
//            bloc.info_line.insert(std::make_pair(key, info));
//            return true;
//        }
//    }
//    return false;
//}
//
//void parse_config_file::log_error(std::string & key, std::vector<std::string> & info){
//    std::cout << _indente_log << "key = " << key << "info = ";
//    for(std::vector<std::string>::iterator it = info.begin(); it != info.end(); ++it)
//        std::cout << *it << " ";
//    std::cout<<std::endl;
//}
//
//
