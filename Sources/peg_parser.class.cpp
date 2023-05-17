#include "../Include/peg_parser.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

peg_parser::peg_parser() : _string_stream(), _line_comment_character(){}

peg_parser::peg_parser(const std::string line_comment_character)
    : _string_stream(), _line_comment_character(line_comment_character){}

peg_parser::peg_parser(const char * path_file) : _string_stream(), _line_comment_character() {
    std::ifstream       file_to_parse(path_file);

    if (!file_to_parse.is_open())
        throw syntax_exception(strerror(errno));
    std::copy(std::istreambuf_iterator<char>(file_to_parse),
              std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(_string_stream));
    std::cout << _string_stream.str() << std::endl;
    file_to_parse.close();
}

peg_parser::peg_parser(const char *path_file , const std::string line_comment_character)
    : _string_stream(), _line_comment_character(line_comment_character) {
    std::ifstream       file_to_parse(path_file);

    if (!file_to_parse.is_open())
        throw syntax_exception(strerror(errno));
    std::copy(std::istreambuf_iterator<char>(file_to_parse),
              std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(_string_stream));
    std::cout << _string_stream.str() << std::endl;
    file_to_parse.close();
}

peg_parser::peg_parser(const std::string & string_to_parse)
    : _string_stream(string_to_parse), _line_comment_character(){}

peg_parser::peg_parser(const string & string_to_parse, const std::string line_comment_character)
    : _string_stream(string_to_parse), _line_comment_character(line_comment_character){

}

peg_parser::~peg_parser() { }

peg_parser::peg_parser(peg_parser & other) : _string_stream(){
    *this = other;
}

peg_parser &peg_parser::operator=(peg_parser & rhs) {
    this->_string_stream.str() = rhs._string_stream.str();
    this->_string_stream.seekg(rhs._string_stream.tellg());
    this->_line_comment_character = rhs._line_comment_character;
    return *this;
}


/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

std::string peg_parser::extract_data(char control_operator) {
    std::string data;

    if (!delete_comments())
        return data;

    if (control_operator == 0)
        _string_stream >> data >> std::ws;
    else
        std::getline(_string_stream >> std::ws, data, control_operator);

    std::cout << "Data: " << data << std::endl;
//    std::string to_print = _string_stream.str();
//    to_print = to_print.substr(_string_stream.tellg(), to_print.length() - _string_stream.tellg());
//    std::cout << to_print << std::endl;


    if (_string_stream.eof()) {
        syntax_exception exception(data.c_str());
        exception.set_error_message("find end of file in ");
        throw exception;
    }
    return data;
}

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

peg_parser::syntax_exception::syntax_exception(const char * message) :
                _message(message){}

peg_parser::syntax_exception::syntax_exception(const peg_parser::syntax_exception & other) :
                _message(other._message) {}

peg_parser::syntax_exception &
peg_parser::syntax_exception::operator=(const peg_parser::syntax_exception &rhs) {
    this->_message =rhs._message;
    return *this;
}

peg_parser::syntax_exception::~syntax_exception() throw() { }

const char *peg_parser::syntax_exception::what() const throw() { return _message.c_str(); }

void peg_parser::syntax_exception::set_error_message( std::string error_message) {
    _message = error_message + _message;
}

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/
bool peg_parser::check_is_empty() {
    return _string_stream.eof();
}

bool peg_parser::check_is_end_of_bloc(char end_of_bloc_character) {
    std::string check;
    std::streampos init = _string_stream.tellg();
    check = extract_data(end_of_bloc_character);

    if (check.empty())
        return true;

    _string_stream.seekg(init);
    return false;
}


bool peg_parser::delete_comments() {
    if (!_line_comment_character.empty()){
        std::string line = _line_comment_character;
        std::streampos init;
        while (line.substr(0, _line_comment_character.length()) == _line_comment_character
            && !_string_stream.eof()) {
            init = _string_stream.tellg();
            std::getline(_string_stream >> std::ws, line, '\n');
        }

        if (line.substr(0, _line_comment_character.length()) != _line_comment_character
            && _string_stream.eof()) {
            syntax_exception exception(line.c_str());
            exception.set_error_message("find end of file in ");
            throw exception;
        }

        if (line.substr(0, _line_comment_character.length()) != _line_comment_character
            && !_string_stream.eof()) {
            _string_stream.seekg(init);
            return true;
        }
        return false;
    }
    return true;
}


















//bool peg_parser::check_is_empt(std::string & buffer_line){
//    _string_stream.str(buffer_line);
//    std::getline(_string_stream >> std::ws, buffer_line);
//    return buffer_line.empty();
//}

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

void peg_parser::find_toke(std::string & word){
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
    find_toke(word);
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








