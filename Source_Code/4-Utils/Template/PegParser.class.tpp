#pragma once

#ifndef WEBSERV_PEGPARSER_TPP
#define WEBSERV_PEGPARSER_TPP

#include <Source_Code/0-Main/Includes/Headers.hpp>

template <class T>
class PegParser {

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of 6-PegParser.class
 *
 * 6-PegParser();
 *
 * @param   void
 * @throw   none
 **/
    PegParser() : _stringStream(), _lineCommentCharacter() {};

/**
 * Constructor of 6-PegParser.class
 *
 * 6-PegParser(const char *pathFile);
 *
 * @param   pathFile is a path of file to parse
 * @throw   syntaxException if can't open th file
 **/
    explicit PegParser(const char * path_file) : _stringStream(), _lineCommentCharacter() {
        if (path_file == NULL || strlen(path_file) == 0)
            return;
        std::ifstream       fileToParse(path_file);

        if (!fileToParse.is_open())
            throw syntaxException(strerror(errno));
        std::copy(std::istreambuf_iterator<char>(fileToParse),
                  std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(_stringStream));
//    std::cout << _stringStream.str() << std::endl;
        fileToParse.close();
    };

/**
 * Constructor of 6-PegParser.class
 *
 * 6-PegParser(const char *pathFile, std::string lineCommentCharacter);
 *
 * @param   pathFile is a path of file to parse
 * @param   lineCommentCharacter is a line character indicates the line not to be processed
 * @throw   syntaxException if can't open th file
 **/
    PegParser(const char *path_file , const std::string & lineCommentCharacter)
            : _stringStream(), _lineCommentCharacter(lineCommentCharacter) {
        if (path_file == NULL || strlen(path_file) == 0)
            return;
        std::ifstream       fileToParse(path_file);
        std::cerr << path_file << fileToParse.is_open() <<std::endl;

        if (!fileToParse.is_open())
            throw syntaxException(strerror(errno));
        std::copy(std::istreambuf_iterator<char>(fileToParse),
                  std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(_stringStream));
        fileToParse.close();
    };

/**
 * Constructor of 6-PegParser.class
 *
 * 6-PegParser(std::string & stringToParse);
 *
 * @param   stringToParse
 * @throw   none
 **/
    explicit PegParser(const std::string & stringToParse)
            : _stringStream(stringToParse), _lineCommentCharacter(){};

/**
 * Constructor of 6-PegParser.class
 *
 * 6-PegParser(std::string & stringToParse);
 *
 * @param   stringStream& is a buffer to parse
 * @param   lineCommentCharacter is a line character indicates the line not to be processed
 * @throw   none
 **/
    PegParser(const std::string & stringToParse, const std::string & lineCommentCharacter)
            : _stringStream(stringToParse), _lineCommentCharacter(lineCommentCharacter){};
/**
* Destructor of 6-PegParser.class
*
* 6-PegParser);
*
* @throw   none
**/
    ~PegParser() {};

/**
 * Constructor of 6-PegParser.class
 *
 *  6-PegParser(6-PegParser & other);
 *
 * @param   other is 6-PegParser to copy
 * @throw   none
 **/
    PegParser(const PegParser & other) : _stringStream(){
        *this = other;
    };

/**
 * Constructor of 6-PegParser.class
 *
 * warning loss the position after copy
 *
 * 6-PegParser& operator=(6-PegParser & rhs);
 *
 * @param   rhs is 6-PegParser at right position of = operator to copy
 * @throw   none
 **/
    PegParser& operator=(const PegParser& rhs){
       if ( this != &rhs) {
           this->_stringStream.str() = rhs._stringStream.str();
           this->_lineCommentCharacter = rhs._lineCommentCharacter;
           this->_mapTokenListAction = rhs._mapTokenListAction;
       }
    return *this;
};


/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

/**
 * Public methode of 6-PegParser.class
 *
 *   template<class T>
    void findToken( std::map<std::string , std::string (T::*)()>&, char controlOperator);
 *
 * @returns     void
 * @param       mapTokenListAction is a std::map key = token (string),
 *              data = action to do (std::string (*)(std::stringstream&))
 * @param       controlOperator delimit the end of data to extract 0 = white space
 * @throw       syntaxException
 */

    void findToken(T& base, char controlOperator) {
        std::string token = extractData(controlOperator);
        if (token.find_first_not_of('\0') ==  std::string::npos)
            return;
        typename std::map<std::string, std::string (T::*)(std::string&)>::iterator it = _mapTokenListAction.find(token);
        if (it == _mapTokenListAction.end() && !checkIsEmpty()) {
            syntaxException exception(token.c_str());
            exception.setErrorMessage("error token in ");
            throw exception;
        }

        std::string result = (base.*(it->second))(token);

        if (!result.empty()) {
            syntaxException exception(result.c_str());
            exception.setErrorMessage("value invalid in ");
            throw exception;
        }
    }

/**
 * Public methode of 6-PegParser.class
 *
 *   void parse(char controlOperator);
 *
 * @returns     std::string data extracted befor the control operator
 * @param       controlOperator delimit the end of data to extract 0 = white space
 * @throw       syntaxException
 */
    std::string extractData(char control_operator) {
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
    };

/**
 * Public methode of 6-PegParser.class
 *
 *  bool checkIsEmpty();
 *
 * @returns     bool true if it's empty
 * @param       void
 * @throw       syntaxException
 */
    bool checkIsEmpty(){
        return _stringStream.eof();
    };

/**
 * Public methode of 6-PegParser.class
 *
 *  bool checkIsEndOfBloc(char endOfBlocCharacter);
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    bool checkIsEndOfBloc(char endOfBlocCharacter) {
        std::string check= _stringStream.str();
        std::streampos init = _stringStream.tellg();
        check = extractData(endOfBlocCharacter);

        if (check.empty() && check.find(endOfBlocCharacter))
            return true;

        _stringStream.seekg(init);
        return false;
    };

/**
 * Public methode of 6-PegParser.class
 *
 *   const std::stringstream &getStringStream() const;
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    const std::stringstream &getStringStream() const {
        return _stringStream;
    };

/**
 * Public methode of 6-PegParser.class
 *
 *  void setStringStream(const std::stringstream &stringStream);
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    void setStringStream(const std::string &string) {
        _stringStream.str(string);
        _stringStream.seekg(0);
    };

/**
 * Public methode of 6-PegParser.class
 *
 *  const string &getLineCommentCharacter() const;
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    const std::string &getLineCommentCharacter() const {
        return _lineCommentCharacter;
    };

/**
 * Public methode of 6-PegParser.class
 *
 *   void setLineCommentCharacter(const string &lineCommentCharacter);
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    void setLineCommentCharacter(const std::string &lineCommentCharacter) {
        _lineCommentCharacter = lineCommentCharacter;
    };

/**
 * Public methode of 6-PegParser.class
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken(const std::string & token, std::string (T::*f)(std::string&)) {
        _mapTokenListAction[token] = f;
    };

/**
 * Public methode of 6-PegParser.class
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void deleteMapToken(const std::string & token) {
        if (_mapTokenListAction.find(token) != _mapTokenListAction.end())
            _mapTokenListAction.erase(token);
    };

/**
 * Public methode of 6-PegParser.class
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void clearMapToken() {
        _mapTokenListAction.clear();
    };

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

/**
 * Class exception of 6-PegParser class
 *
 * class syntaxException;
 *
 * @inherit std::exception
 **/
    class syntaxException: public std::exception
    {
    public:

        /**
         * Constructor of syntaxException class
         *
         * syntaxException(6-PegParser & config, const char* message);
         *
         * @param   message to store const char*
         * @throw   none
         **/
        explicit syntaxException(const char * message) :_message(message){};

        /**
         * Copy constructor of syntaxException class
         *
         * syntaxException(syntaxException &);
         *
         * @param   syntaxException instance to build the syntaxException
         * @throw   none
         **/
        syntaxException(const syntaxException &other) : _message(other._message) {};

        /**
         * Operator overload= of syntaxException class
         *
         * operator=(const syntaxException&);
         *
         * @param   syntaxException instance const to copy the syntaxException
         * @throw   none
         **/
        syntaxException& operator=(const PegParser::syntaxException &rhs) {
            this->_message =rhs._message;
            return *this;
        };

        /**
        * Destructor of syntaxException class
        *
        * virtual ~syntaxException() throw();
        *
        * @throw   none
        **/
        virtual ~syntaxException() throw() {};

        /**
         * Public methode of syntaxException
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "7-Socket error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw(){ return _message.c_str(); };

        /**
         * Public methode of syntaxException
         *
         *  void set_error( std::string error_message)
         *
         * @returns void
         * @param    error_message to set befor the initial message
         * @throw   none
         **/
         void setErrorMessage(const std::string &errorMessage) {
            _message = errorMessage + _message;
        };

    private:
        std::string         _message;
    };

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

/**
 * Public methode of 6-PegParser.class
 *
 * bool deleteComments();
 *
 * @returns     void
 * @param       buffer_line is a string to remove comment
 * @throw       syntaxException
 */
    bool deleteComments() {
        if (!_lineCommentCharacter.empty()) {
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
    };

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    std::stringstream                                           _stringStream;
    std::string                                                 _lineCommentCharacter;
    std::map<std::string, std::string (T::*)(std::string&)>     _mapTokenListAction;
};

#endif
