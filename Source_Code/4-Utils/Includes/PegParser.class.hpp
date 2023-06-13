#pragma once

#ifndef WEBSERV_PEGPARSER_HPP
#define WEBSERV_PEGPARSER_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>

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
    PegParser();

/**
 * Constructor of 6-PegParser.class
 *
 * 6-PegParser(std::string lineCommentCharacter);
 *
 * @param   lineCommentCharacter is a line character indicates the line not to be processed
 * @throw   none
 **/
//    6-PegParser(const std::string);

/**
 * Constructor of 6-PegParser.class
 *
 * 6-PegParser(const char *pathFile);
 *
 * @param   pathFile is a path of file to parse
 * @throw   syntaxException if can't open th file
 **/
    PegParser(const char *);

/**
 * Constructor of 6-PegParser.class
 *
 * 6-PegParser(const char *pathFile, std::string lineCommentCharacter);
 *
 * @param   pathFile is a path of file to parse
 * @param   lineCommentCharacter is a line character indicates the line not to be processed
 * @throw   syntaxException if can't open th file
 **/
    PegParser(const char *, std::string);

/**
 * Constructor of 6-PegParser.class
 *
 * 6-PegParser(std::string & stringToParse);
 *
 * @param   stringToParse
 * @throw   none
 **/
    PegParser(const std::string &);

/**
 * Constructor of 6-PegParser.class
 *
 * 6-PegParser(std::string & stringToParse);
 *
 * @param   stringStream& is a buffer to parse
 * @param   lineCommentCharacter is a line character indicates the line not to be processed
 * @throw   none
 **/
    PegParser(const std::string &, const std::string);

/**
* Destructor of 6-PegParser.class
*
* 6-PegParser);
*
* @throw   none
**/
    ~PegParser();

/**
 * Constructor of 6-PegParser.class
 *
 *  6-PegParser(6-PegParser & other);
 *
 * @param   other is 6-PegParser to copy
 * @throw   none
 **/
    PegParser(const PegParser &);

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
    PegParser& operator=(const PegParser&);


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

    template<class T>
    void findToken(T& base, std::map<std::string, std::string (T::*)(std::string&)> & mapTokenListAction, char controlOperator) {
        std::string token = extractData(controlOperator);
        if (token.find_first_not_of('\0') ==  std::string::npos)
            return;
        typename std::map<std::string, std::string (T::*)(std::string&)>::iterator it = mapTokenListAction.find(token);
        if (it == mapTokenListAction.end() && !checkIsEmpty()) {
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
    std::string extractData(char controlOperator);

/**
 * Public methode of 6-PegParser.class
 *
 *  bool checkIsEmpty();
 *
 * @returns     bool true if it's empty
 * @param       void
 * @throw       syntaxException
 */
    bool checkIsEmpty();

/**
 * Public methode of 6-PegParser.class
 *
 *  bool checkIsEndOfBloc(char endOfBlocCharacter);
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    bool checkIsEndOfBloc(char);

/**
 * Public methode of 6-PegParser.class
 *
 *   const std::stringstream &getStringStream() const;
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    const std::stringstream &getStringStream() const;

/**
 * Public methode of 6-PegParser.class
 *
 *  void setStringStream(const std::stringstream &stringStream);
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    void setStringStream(const std::string &string);

/**
 * Public methode of 6-PegParser.class
 *
 *  const string &getLineCommentCharacter() const;
 *
 * @returns     bool true if find endOfBlocCharacter
 * @param       endOfBlocCharacter define the end of bloc
 * @throw       syntaxException
 */
    const string &getLineCommentCharacter() const;

/**
 * Public methode of 6-PegParser.class
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
         *          at the construction defaut constructor "7-Socket error"
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
 * Public methode of 6-PegParser.class
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
