#include "../Include/peg_parser.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

pegParser::pegParser() : _stringStream(), _lineCommentCharacter(){}

//pegParser::pegParser(const std::string lineCommentCharacter)
//    : _stringStream(), _lineCommentCharacter(lineCommentCharacter){}

pegParser::pegParser(const char * path_file) : _stringStream(), _lineCommentCharacter() {
    std::ifstream       fileToParse(path_file);

    if (!fileToParse.is_open())
        throw syntaxException(strerror(errno));
    std::copy(std::istreambuf_iterator<char>(fileToParse),
              std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(_stringStream));
    std::cout << _stringStream.str() << std::endl;
    fileToParse.close();
}

pegParser::pegParser(const char *path_file , const std::string lineCommentCharacter)
    : _stringStream(), _lineCommentCharacter(lineCommentCharacter) {
    std::ifstream       fileToParse(path_file);

    if (!fileToParse.is_open())
        throw syntaxException(strerror(errno));
    std::copy(std::istreambuf_iterator<char>(fileToParse),
              std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(_stringStream));
    fileToParse.close();
}

pegParser::pegParser(const std::string & stringToParse)
    : _stringStream(stringToParse), _lineCommentCharacter(){}

pegParser::pegParser(const string & stringToParse, const std::string lineCommentCharacter)
    : _stringStream(stringToParse), _lineCommentCharacter(lineCommentCharacter){

}

pegParser::~pegParser() { }

pegParser::pegParser(pegParser & other) : _stringStream(){
    *this = other;
}

pegParser &pegParser::operator=(const pegParser & rhs) {
    this->_stringStream.str() = rhs._stringStream.str();
    this->_lineCommentCharacter = rhs._lineCommentCharacter;
    return *this;
}


/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

std::string pegParser::extractData(char control_operator) {
    std::string data;

    if (!deleteComments())
        return data;

    if (control_operator == 0)
        _stringStream >> data >> std::ws;
    else
        std::getline(_stringStream >> std::ws, data, control_operator);

    if (_stringStream.eof() && data.find_first_not_of('\0') != std::string::npos) {
        syntaxException exception(data.c_str());
        exception.setErrorMessage("find end of file in ");
        throw exception;
    }
    return data;
}

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

pegParser::syntaxException::syntaxException(const char * message) :
                _message(message){}

pegParser::syntaxException::syntaxException(const pegParser::syntaxException & other) :
                _message(other._message) {}

pegParser::syntaxException &
pegParser::syntaxException::operator=(const pegParser::syntaxException &rhs) {
    this->_message =rhs._message;
    return *this;
}

pegParser::syntaxException::~syntaxException() throw() { }

const char *pegParser::syntaxException::what() const throw() { return _message.c_str(); }

void pegParser::syntaxException::setErrorMessage(const std::string &errorMessage) {
    _message = errorMessage + _message;
}

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/
bool pegParser::checkIsEmpty() {
    return _stringStream.eof();
}

bool pegParser::checkIsEndOfBloc(char endOfBlocCharacter) {
    std::string check= _stringStream.str();
    std::streampos init = _stringStream.tellg();
    check = extractData(endOfBlocCharacter);

    if (check.empty() && check.find(endOfBlocCharacter))
        return true;

    _stringStream.seekg(init);
    return false;
}


bool pegParser::deleteComments() {
    if (!_lineCommentCharacter.empty()){
        std::string line = _lineCommentCharacter;
        std::streampos init;
        while (line.substr(0, _lineCommentCharacter.length()) == _lineCommentCharacter
            && !_stringStream.eof()) {
            init = _stringStream.tellg();
            std::getline(_stringStream >> std::ws, line, '\n');
        }

        if (line.substr(0, _lineCommentCharacter.length()) != _lineCommentCharacter
            && !checkIsEmpty()) {
            _stringStream.seekg(init);
            return true;
        }
        return false;
    }
    return true;
}

const std::stringstream &pegParser::getStringStream() const {
    return _stringStream;
}

void pegParser::setStringStream(const std::string &string) {
    _stringStream.str(string);
    _stringStream.seekg(0);
}

const string &pegParser::getLineCommentCharacter() const {
    return _lineCommentCharacter;
}

void pegParser::setLineCommentCharacter(const string &lineCommentCharacter) {
    _lineCommentCharacter = lineCommentCharacter;
}
