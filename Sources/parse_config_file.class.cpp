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
                _bloc_config_file(), _webserv_config_file(path_config_file.c_str()),
                _buffer_line(), _token_list("{}; "), _flag_token(){
    if (!_webserv_config_file.is_open())
        throw parse_config_file::syntax_exception(*this, strerror(errno), __LINE__ );
    get_next_line();
    parse_bloc(_bloc_config_file, std::make_pair(std::string(), std::vector<std::string>()));
    _webserv_config_file.close();
}

parse_config_file::~parse_config_file() {}

parse_config_file::parse_config_file(const parse_config_file &other) :
                _bloc_config_file(other._bloc_config_file), _webserv_config_file(),
                _token_list(other._token_list), _flag_token(other._flag_token){}

parse_config_file &parse_config_file::operator=(const parse_config_file &rhs) {
    this->_bloc_config_file = rhs._bloc_config_file;
    this->_token_list = rhs._token_list;
    this->_flag_token = rhs._flag_token;
    return *this;
}

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

parse_config_file::syntax_exception::syntax_exception(parse_config_file & config, const char * message, int line) :
                _message(message), _config(config), _line(line){
    std::ostringstream oss;
    oss << line;
    _message += " line error => ";
    _message += oss.str();
}

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

bool parse_config_file::check_is_empty(){
    std::istringstream string_stream(_buffer_line);
    std::getline(string_stream >> std::ws, _buffer_line);
    return _buffer_line.empty();
}

void parse_config_file::delete_comments(){
    if (_buffer_line.find('#') != std::string::npos)
        _buffer_line = _buffer_line.substr(0, _buffer_line.find('#'));
}

bool parse_config_file::get_next_line(){
    _buffer_line.clear();
    while (check_is_empty() && std::getline(_webserv_config_file, _buffer_line))
        delete_comments();
    return !_buffer_line.empty();
}

void parse_config_file::parse_bloc(t_bloc & bloc, std::pair<std::string, std::vector<std::string> > info_line) {
    s_bloc new_bloc;
    log_error(info_line.first, info_line.second);
    while (parse_info(new_bloc));
    bloc.info_bloc.insert(std::make_pair(info_line, new_bloc));
}

bool parse_config_file::is_token(std::string& token){
    return (white_space != identify_token(token[0]) && token.length() == 1);
}

bool parse_config_file::identify_flag_token(char token){
    return (_flag_token == identify_token(token));
}

int parse_config_file::identify_token(char token){
    int flag_token;
    switch (token) {
        case '{' :
            flag_token = open_bracket;
            break;
        case '}' :
            flag_token = close_bracket;
            break;
        case ';' :
            flag_token = semicolon;
            break;
        default:
            flag_token = white_space;
            break;
    }
    return flag_token;
}

void parse_config_file::set_flag_token(char token){
   _flag_token = identify_token(token);
}

void parse_config_file::find_token(std::string & word){
    set_flag_token(_token_list[white_space]);
    for (std::size_t word_size = 0; word_size < word.length() ; ++word_size) {
        for (std::size_t token_list_size = 0; token_list_size < _token_list.length() ; ++token_list_size) {
            if (word[word_size] == _token_list[token_list_size]) {
                set_flag_token(word[token_list_size]);
                if(word_size == 0)
                    word += _token_list[token_list_size];
                word = word.substr(0, word_size);
            }
        }
    }
//    std::remove_if(_buffer_line.begin(), _buffer_line.end())
//    _buffer_line.erase(std::remove_if(result.begin(), result.end(), [](char c) {
//        return std::isspace(static_cast<unsigned char>(c));
//    }), result.end())
    _buffer_line = _buffer_line.substr(word.length());
    if (_buffer_line.empty())
        get_next_line();
}

bool parse_config_file::find_next_word(std::string & word){
    word.clear();
    std::istringstream string_stream(_buffer_line);
    string_stream >> word >> std::ws;
    size_t number_of_whit_space = string_stream.str().size();
    (void)number_of_whit_space;
    find_token(word);
    if(is_token(word) || word.empty())
        return false;
    return true;
}

bool parse_config_file::parse_info(t_bloc & bloc) {
    std::string key, tmp;
    std::vector<std::string> info;

    if (find_next_word(key)) {
        while (find_next_word(tmp))
            info.push_back(tmp);
        if (identify_flag_token('{')) {
            _indente_log += '\t';
            parse_bloc(bloc, std::make_pair(key, info));
            _indente_log.erase(_indente_log.end() - 1);
            return true;
        }
        else if (identify_flag_token('}')) {
            throw parse_config_file::syntax_exception(*this, "expected token", __LINE__ );
        }
        else if (identify_flag_token(';')) {
            log_error(key, info);
            bloc.info_line.insert(std::make_pair(key, info));
            return true;
        }
    }
    return false;
}

void parse_config_file::log_error(std::string & key, std::vector<std::string> & info){
    std::cout << _indente_log << "key = " << key << "info = ";
    for(std::vector<std::string>::iterator it = info.begin(); it != info.end(); ++it)
        std::cout << *it << " ";
    std::cout<<std::endl;
}

