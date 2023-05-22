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
    std::string check= _string_stream.str();
    std::streampos init = _string_stream.tellg();
    check = extract_data(end_of_bloc_character);

    if (check.empty() && check.find(end_of_bloc_character))
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
            && !check_is_empty()) {
            _string_stream.seekg(init);
            return true;
        }
        return false;
    }
    return true;
}
