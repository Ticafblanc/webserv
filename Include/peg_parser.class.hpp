#ifndef WEBSERV_PEG_PARSER_HPP
#define WEBSERV_PEG_PARSER_HPP

#include "../Include/header.hpp"

class pegParser {

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of pegParser.class
 *
 * pegParser();
 *
 * @param   void
 * @throw   none
 **/
    pegParser();

/**
 * Constructor of pegParser.class
 *
 * pegParser(std::string lineCommentCharacter);
 *
 * @param   lineCommentCharacter is a line character indicates the line not to be processed
 * @throw   none
 **/
//    pegParser(const std::string);

/**
 * Constructor of pegParser.class
 *
 * pegParser(const char *pathFile);
 *
 * @param   pathFile is a path of file to parse
 * @throw   syntaxException if can't open th file
 **/
    pegParser(const char *);

/**
 * Constructor of pegParser.class
 *
 * pegParser(const char *pathFile, std::string lineCommentCharacter);
 *
 * @param   pathFile is a path of file to parse
 * @param   lineCommentCharacter is a line character indicates the line not to be processed
 * @throw   syntaxException if can't open th file
 **/
    pegParser(const char *, std::string);

/**
 * Constructor of pegParser.class
 *
 * pegParser(std::string & stringToParse);
 *
 * @param   stringToParse
 * @throw   none
 **/
    pegParser(const std::string &);

/**
 * Constructor of pegParser.class
 *
 * pegParser(std::string & stringToParse);
 *
 * @param   stringStream& is a buffer to parse
 * @param   lineCommentCharacter is a line character indicates the line not to be processed
 * @throw   none
 **/
    pegParser(const std::string &, const std::string);

/**
* Destructor of pegParser.class
*
* pegParser);
*
* @throw   none
**/
    ~pegParser();

/**
 * Constructor of pegParser.class
 *
 *  pegParser(pegParser & other);
 *
 * @param   other is pegParser to copy
 * @throw   none
 **/
    pegParser(pegParser &);

/**
 * Constructor of pegParser.class
 *
 * warning loss the position after copy
 *
 * pegParser& operator=(pegParser & rhs);
 *
 * @param   rhs is pegParser at right position of = operator to copy
 * @throw   none
 **/
    pegParser& operator=(const pegParser&);


/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

/**
 * Public methode of pegParser.class
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

    template<class T>
    void findToken(T& base, std::map<std::string, std::string (T::*)()> & mapTokenListAction, char controlOperator) {
        std::string token = extractData(controlOperator);
        if (token.find_first_not_of('\0') ==  std::string::npos)
            return;
        typename std::map<std::string, std::string (T::*)()>::iterator it = mapTokenListAction.find(token);
        if (it == mapTokenListAction.end() && !checkIsEmpty()) {
            syntaxException exception(token.c_str());
            exception.setErrorMessage("error token in ");
            throw exception;
        }

        std::string result = (base.*(it->second))();

        if (!result.empty()) {
            syntaxException exception(result.c_str());
            exception.setErrorMessage("value invalid in ");
            throw exception;
        }
    }

/**
 * Public methode of pegParser.class
 *
 *   void parse(char controlOperator);
 *
 * @returns     std::string data extracted befor the control operator
 * @param       controlOperator delimit the end of data to extract 0 = white space
 * @throw       syntaxException
 */
    std::string extractData(char controlOperator);

/**
 * Public methode of pegParser.class
 *
 *  bool checkIsEmpty();
 *
 * @returns     bool true if it's empty
 * @param       void
 * @throw       syntaxException
 */
    bool checkIsEmpty();

/**
 * Public methode of pegParser.class
 *
 *  bool checkIsEndOfBloc(char endOfBlocCharacter);
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    bool checkIsEndOfBloc(char);

/**
 * Public methode of pegParser.class
 *
 *   const std::stringstream &getStringStream() const;
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    const std::stringstream &getStringStream() const;

/**
 * Public methode of pegParser.class
 *
 *  void setStringStream(const std::stringstream &stringStream);
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    void setStringStream(const std::string &string);

/**
 * Public methode of pegParser.class
 *
 *  const string &getLineCommentCharacter() const;
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    const string &getLineCommentCharacter() const;

/**
 * Public methode of pegParser.class
 *
 *   void setLineCommentCharacter(const string &lineCommentCharacter);
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    void setLineCommentCharacter(const string &lineCommentCharacter);

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

/**
 * Class exception of pegParser class
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
         * syntaxException(pegParser & config, const char* message);
         *
         * @param   message to store const char*
         * @throw   none
         **/
        syntaxException(const char *);

        /**
         * Copy constructor of syntaxException class
         *
         * syntaxException(syntaxException &);
         *
         * @param   syntaxException instance to build the syntaxException
         * @throw   none
         **/
        syntaxException(const syntaxException &);

        /**
         * Operator overload= of syntaxException class
         *
         * operator=(const syntaxException&);
         *
         * @param   syntaxException instance const to copy the syntaxException
         * @throw   none
         **/
        syntaxException& operator=(const syntaxException &);

        /**
        * Destructor of syntaxException class
        *
        * virtual ~syntaxException() throw();
        *
        * @throw   none
        **/
        virtual ~syntaxException() throw();

        /**
         * Public methode of syntaxException
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "socket error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

        /**
         * Public methode of syntaxException
         *
         *  void set_error( std::string error_message)
         *
         * @returns void
         * @param    error_message to set befor the initial message
         * @throw   none
         **/
         void setErrorMessage(const std::string &);

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
 * Public methode of pegParser.class
 *
 * bool deleteComments();
 *
 * @returns     void
 * @param       buffer_line is a string to remove comment
 * @throw       syntaxException
 */
    bool deleteComments();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    std::stringstream   _stringStream;
    std::string         _lineCommentCharacter;
};

#endif
