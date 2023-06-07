#include "PegParser.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

PegParser::PegParser() : _stringStream(), _lineCommentCharacter(){}

//6-PegParser::6-PegParser(const std::string lineCommentCharacter)
//    : _stringStream(), _lineCommentCharacter(lineCommentCharacter){}

PegParser::PegParser(const char * path_file) : _stringStream(), _lineCommentCharacter() {
    if (path_file == NULL || strlen(path_file) == 0)
        return;
    std::ifstream       fileToParse(path_file);

    if (!fileToParse.is_open())
        throw syntaxException(strerror(errno));
    std::copy(std::istreambuf_iterator<char>(fileToParse),
              std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(_stringStream));
    std::cout << _stringStream.str() << std::endl;
    fileToParse.close();
}

PegParser::PegParser(const char *path_file , const std::string lineCommentCharacter)
    : _stringStream(), _lineCommentCharacter(lineCommentCharacter) {
    if (path_file == NULL || strlen(path_file) == 0)
        return;
    std::ifstream       fileToParse(path_file);

    if (!fileToParse.is_open())
        throw syntaxException(strerror(errno));
    std::copy(std::istreambuf_iterator<char>(fileToParse),
              std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(_stringStream));
    fileToParse.close();
}

PegParser::PegParser(const std::string & stringToParse)
    : _stringStream(stringToParse), _lineCommentCharacter(){}

PegParser::PegParser(const string & stringToParse, const std::string lineCommentCharacter)
    : _stringStream(stringToParse), _lineCommentCharacter(lineCommentCharacter){

}

PegParser::~PegParser() { }

PegParser::PegParser(PegParser & other) : _stringStream(){
    *this = other;
}

PegParser &PegParser::operator=(const PegParser & rhs) {
    this->_stringStream.str() = rhs._stringStream.str();
    this->_lineCommentCharacter = rhs._lineCommentCharacter;
    return *this;
}


/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

std::string PegParser::extractData(char control_operator) {
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

PegParser::syntaxException::syntaxException(const char * message) :
                _message(message){}

PegParser::syntaxException::syntaxException(const PegParser::syntaxException & other) :
                _message(other._message) {}

PegParser::syntaxException &
PegParser::syntaxException::operator=(const PegParser::syntaxException &rhs) {
    this->_message =rhs._message;
    return *this;
}

PegParser::syntaxException::~syntaxException() throw() { }

const char *PegParser::syntaxException::what() const throw() { return _message.c_str(); }

void PegParser::syntaxException::setErrorMessage(const std::string &errorMessage) {
    _message = errorMessage + _message;
}

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/
bool PegParser::checkIsEmpty() {
    return _stringStream.eof();
}

bool PegParser::checkIsEndOfBloc(char endOfBlocCharacter) {
    std::string check= _stringStream.str();
    std::streampos init = _stringStream.tellg();
    check = extractData(endOfBlocCharacter);

    if (check.empty() && check.find(endOfBlocCharacter))
        return true;

    _stringStream.seekg(init);
    return false;
}


bool PegParser::deleteComments() {
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

const std::stringstream &PegParser::getStringStream() const {
    return _stringStream;
}

void PegParser::setStringStream(const std::string &string) {
    _stringStream.str(string);
    _stringStream.seekg(0);
}

const string &PegParser::getLineCommentCharacter() const {
    return _lineCommentCharacter;
}

void PegParser::setLineCommentCharacter(const string &lineCommentCharacter) {
    _lineCommentCharacter = lineCommentCharacter;
}
