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
    PegParser(PegParser & other)
    : _stringStream(other._stringStream.str()),_lineCommentCharacter(other._lineCommentCharacter) {
        _stringStream.seekg(other._stringStream.tellg());
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
 *   const std::stringstream &getStringStream() const;
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    const std::string getStr(){
        return _stringStream.str().substr(_stringStream.tellg());
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
*|                                  Set map Token                                   |
*====================================================================================
*/

    void setMapTokenFile() {
        clearMapToken();
        setMapToken("worker_processes", &T::setWorkerProcesses);
        setMapToken("client_body_buffer_size", &T::setClientBodyBufferSize);
        setMapToken("client_header_buffer_size", &T::setClientHeaderBufferSize);
        setMapToken("client_max_body_size", &T::setClientMaxBodySize);
        setMapToken("events", &T::blocToken);
        setMapToken("http", &T::blocToken);
        setMapToken("server", &T::blocToken);
    }

    void setMapTokenEvents() {
        clearMapToken();
        setMapToken("worker_connections", &T::setWorkerConnections);
    }

    void setMapTokenHttp() {
        clearMapToken();
        setMapToken("listen", &T::addVectorListen);
        setMapToken("server_name", &T::addVectorServerName);
        setMapToken("root", &T::setRoot);
        setMapToken("index", &T::addIndex);
        setMapToken("error_page", &T::setErrorPage);
        setMapToken("autoindex", &T::setAutoIndex);
        setMapToken("allowed_methods", &T::setAllowMethods);
        setMapToken("server", &T::blocToken);
    }

    void setMapTokenServer() {
        clearMapToken();
        setMapToken("listen", &T::addVectorListen);
        setMapToken("server_name", &T::addVectorServerName);
        setMapToken("root", &T::setRoot);
        setMapToken("index", &T::addIndex);
        setMapToken("error_page", &T::setErrorPage);
        setMapToken("autoindex", &T::setAutoIndex);
        setMapToken("allowed_methods", &T::setAllowMethods);
        setMapToken("server", &T::blocToken);
        setMapToken("location", &T::blocToken);
    }

    void setMapTokenLocation() {
        setMapToken("return", &T::setReturn);
        setMapToken("add_header", &T::addMapAddHeader);
        setMapToken("cgi_pass", &T::setCgiPass);
    }

    void setMapTokenHeaderStartLine() {
       setMapToken("GET", &T::methodeGET);
       setMapToken("POST", &T::methodePOST);
       setMapToken("DELETE", &T::methodeDELETE);
    }

    void setMapTokenHeadersInformation() {
        setMapToken("Accept:", &T::addToMapHttpHeader);
        setMapToken("Accept-Charset:", &T::addToMapHttpHeader);
        setMapToken("Accept-Datetime:", &T::addToMapHttpHeader);
        setMapToken("Accept-Encoding:", &T::addToMapHttpHeader);
        setMapToken("Accept-Language:", &T::addToMapHttpHeader);
        setMapToken("Accept-Patch:", &T::addToMapHttpHeader);
        setMapToken("Accept-Ranges:", &T::addToMapHttpHeader);
        setMapToken("Access-Control-Allow-Credentials:", &T::addToMapHttpHeader);
        setMapToken("Access-Control-Allow-Headers:", &T::addToMapHttpHeader);
        setMapToken("Access-Control-Allow-Methods:", &T::addToMapHttpHeader);
        setMapToken("Access-Control-Allow-Origin:", &T::addToMapHttpHeader);
        setMapToken("Access-Control-Expose-Headers:", &T::addToMapHttpHeader);
        setMapToken("Access-Control-Max-Age:", &T::addToMapHttpHeader);
        setMapToken("Access-Control-Request-Method:", &T::addToMapHttpHeader);
        setMapToken("Access-Control-Request-Headers:", &T::addToMapHttpHeader);
        setMapToken("Age:", &T::addToMapHttpHeader);
        setMapToken("Allow:", &T::addToMapHttpHeader);
        setMapToken("Alt-Svc:", &T::addToMapHttpHeader);
        setMapToken("Authorization:", &T::addToMapHttpHeader);
        setMapToken("Cache-Control:", &T::addToMapHttpHeader);
        setMapToken("Connection:", &T::addToMapHttpHeader);
        setMapToken("Content-Disposition:", &T::addToMapHttpHeader);
        setMapToken("Content-Encoding:", &T::addToMapHttpHeader);
        setMapToken("Content-Language:", &T::addToMapHttpHeader);
        setMapToken("Content-Length:", &T::ContentLength);
        setMapToken("Content-Location:", &T::addToMapHttpHeader);
        setMapToken("Content-MD5:", &T::addToMapHttpHeader);
        setMapToken("Content-Range:", &T::addToMapHttpHeader);
        setMapToken("Content-Type:", &T::addToMapHttpHeader);
        setMapToken("Cookie:", &T::addToMapHttpHeader);
        setMapToken("DASL:", &T::addToMapHttpHeader);
        setMapToken("Date:", &T::addToMapHttpHeader);
        setMapToken("DAV:", &T::addToMapHttpHeader);
        setMapToken("Depth:", &T::addToMapHttpHeader);
        setMapToken("Destination:", &T::addToMapHttpHeader);
        setMapToken("DNT (Do Not Track):", &T::addToMapHttpHeader);
        setMapToken("ETag:", &T::addToMapHttpHeader);
        setMapToken("Expect:", &T::addToMapHttpHeader);
        setMapToken("Expires:", &T::addToMapHttpHeader);
        setMapToken("Forwarded:", &T::addToMapHttpHeader);
        setMapToken("From:", &T::addToMapHttpHeader);
        setMapToken("Host:", &T::Host);
        setMapToken("If:", &T::addToMapHttpHeader);
        setMapToken("If-Match:", &T::addToMapHttpHeader);
        setMapToken("If-Modified-Since:", &T::addToMapHttpHeader);
        setMapToken("If-None-Match:", &T::addToMapHttpHeader);
        setMapToken("If-Range:", &T::addToMapHttpHeader);
        setMapToken("If-Unmodified-Since:", &T::addToMapHttpHeader);
        setMapToken("IM (Instance Manipulation):", &T::addToMapHttpHeader);
        setMapToken("Last-Modified:", &T::addToMapHttpHeader);
        setMapToken("Link:", &T::addToMapHttpHeader);
        setMapToken("Location:", &T::addToMapHttpHeader);
        setMapToken("Lock-Token:", &T::addToMapHttpHeader);
        setMapToken("Max-Forwards:", &T::addToMapHttpHeader);
        setMapToken("MIME-Version:", &T::addToMapHttpHeader);
        setMapToken("Origin:", &T::addToMapHttpHeader);
        setMapToken("Overwrite:", &T::addToMapHttpHeader);
        setMapToken("P3P (Platform for Privacy Preferences):", &T::addToMapHttpHeader);
        setMapToken("Pragma:", &T::addToMapHttpHeader);
        setMapToken("Prefer:", &T::addToMapHttpHeader);
        setMapToken("Preference-Applied:", &T::addToMapHttpHeader);
        setMapToken("Proxy-Authenticate:", &T::addToMapHttpHeader);
        setMapToken("Proxy-Authorization:", &T::addToMapHttpHeader);
        setMapToken("Proxy-Connection:", &T::addToMapHttpHeader);
        setMapToken("Range:", &T::addToMapHttpHeader);
        setMapToken("Referer:", &T::addToMapHttpHeader);
        setMapToken("Retry-After:", &T::addToMapHttpHeader);
        setMapToken("Server:", &T::addToMapHttpHeader);
        setMapToken("Set-Cookie:", &T::addToMapHttpHeader);
        setMapToken("Sec-Fetch-Dest:", &T::addToMapHttpHeader);
        setMapToken("Sec-Fetch-Mode:", &T::addToMapHttpHeader);
        setMapToken("Sec-Fetch-Site:", &T::addToMapHttpHeader);
        setMapToken("Sec-Fetch-User:", &T::addToMapHttpHeader);
        setMapToken("SLUG:", &T::addToMapHttpHeader);
        setMapToken("SOAPAction:", &T::addToMapHttpHeader);
        setMapToken("Status-URI:", &T::addToMapHttpHeader);
        setMapToken("Strict-Transport-Security:", &T::addToMapHttpHeader);
        setMapToken("TE:", &T::addToMapHttpHeader);
        setMapToken("Timeout:", &T::addToMapHttpHeader);
        setMapToken("Trailer:", &T::addToMapHttpHeader);
        setMapToken("Transfer-Encoding:", &T::TransfereEncoding);
        setMapToken("Upgrade:", &T::addToMapHttpHeader);
        setMapToken("User-Agent:", &T::addToMapHttpHeader);
        setMapToken("Upgrade-Insecure-Requests:", &T::addToMapHttpHeader);
        setMapToken("Variant-Vary:", &T::addToMapHttpHeader);
        setMapToken("Vary:", &T::addToMapHttpHeader);
        setMapToken("Via:", &T::addToMapHttpHeader);
        setMapToken("WWW-Authenticate:", &T::addToMapHttpHeader);
        setMapToken("X-Forwarded-For:", &T::addToMapHttpHeader);
        setMapToken("X-Forwarded-Proto:", &T::addToMapHttpHeader);
        setMapToken("X-Frame-Options:", &T::addToMapHttpHeader);
        setMapToken("X-XSS-Protection:", &T::addToMapHttpHeader);
        setMapToken("\r\n\r\n", &T::endHeader);
    }
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
         * @returns  const char * store in private std::string _request
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
