#ifndef WEBSERV_PEG_PARSER_HPP
#define WEBSERV_PEG_PARSER_HPP

#include "../Include/header.hpp"

class peg_parser {

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of peg_parser.class
 *
 * peg_parser();
 *
 * @param   void
 * @throw   none
 **/
    peg_parser();

/**
 * Constructor of peg_parser.class
 *
 * peg_parser(std::string line_comment_character);
 *
 * @param   line_comment_character is a line character indicates the line not to be processed
 * @throw   none
 **/
//    peg_parser(const std::string);

/**
 * Constructor of peg_parser.class
 *
 * peg_parser(const char *path_file);
 *
 * @param   path_file is a path of file to parse
 * @throw   syntax_exception if can't open th file
 **/
    peg_parser(const char *);

/**
 * Constructor of peg_parser.class
 *
 * peg_parser(const char *path_file, std::string line_comment_character);
 *
 * @param   path_file is a path of file to parse
 * @param   line_comment_character is a line character indicates the line not to be processed
 * @throw   syntax_exception if can't open th file
 **/
    peg_parser(const char *, std::string);

/**
 * Constructor of peg_parser.class
 *
 * peg_parser(std::string & string_to_parse);
 *
 * @param   string_to_parse
 * @throw   none
 **/
    peg_parser(const std::string &);

/**
 * Constructor of peg_parser.class
 *
 * peg_parser(std::string & string_to_parse);
 *
 * @param   string_stream& is a buffer to parse
 * @param   line_comment_character is a line character indicates the line not to be processed
 * @throw   none
 **/
    peg_parser(const std::string &, const std::string);

/**
* Destructor of peg_parser.class
*
* ~peg_parser();
*
* @throw   none
**/
    ~peg_parser();

/**
 * Constructor of peg_parser.class
 *
 *  peg_parser(peg_parser & other);
 *
 * @param   other is peg_parser to copy
 * @throw   none
 **/
    peg_parser(peg_parser &);

/**
 * Constructor of peg_parser.class
 *
 * warning loss the position after copy
 *
 * peg_parser& operator=(peg_parser & rhs);
 *
 * @param   rhs is peg_parser at right position of = operator to copy
 * @throw   none
 **/
    peg_parser& operator=(const peg_parser&);


/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

/**
 * Public methode of peg_parser.class
 *
 *   template<class T>
    void find_token( std::map<std::string , std::string (T::*)()>&, char control_operator);
 *
 * @returns     void
 * @param       map_token_list_action is a std::map key = token (string),
 *              data = action to do (std::string (*)(std::stringstream&))
 * @param       control_operator delimit the end of data to extract 0 = white space
 * @throw       syntaxe_exception
 */

    template<class T>
    void find_token(T& base, std::map<std::string, std::string (T::*)()> & map_token_list_action, char control_operator) {
        std::string token = extract_data(control_operator);
        if (token.empty())
            return;
        typename std::map<std::string, std::string (T::*)()>::iterator it = map_token_list_action.find(token);
        if (it == map_token_list_action.end() && !check_is_empty()) {
            syntax_exception exception(token.c_str());
            exception.set_error_message("error token in ");
            throw exception;
        }

        std::string result = (base.*(it->second))();

        if (!result.empty()) {
            syntax_exception exception(result.c_str());
            exception.set_error_message("value invalid in ");
            throw exception;
        }
    }

/**
 * Public methode of peg_parser.class
 *
 *   void parse(char control_operator);
 *
 * @returns     std::string data extracted befor the control operator
 * @param       control_operator delimit the end of data to extract 0 = white space
 * @throw       syntaxe_exception
 */
    std::string extract_data(char control_operator);

/**
 * Public methode of peg_parser.class
 *
 *  bool check_is_empty();
 *
 * @returns     bool true if it's empty
 * @param       void
 * @throw       syntaxe_exception
 */
    bool check_is_empty();

/**
 * Public methode of peg_parser.class
 *
 *  bool check_is_end_of_bloc(char end_of_bloc_character);
 *
 * @returns     bool true if find end_of_bloc_character
 * @param       end_of_bloc_character define the end of bloc
 * @throw       syntaxe_exception
 */
    bool check_is_end_of_bloc(char);

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

/**
 * Class exception of peg_parser class
 *
 * class syntax_exception;
 *
 * @inherit std::exception
 **/
    class syntax_exception: public std::exception
    {
    public:

        /**
         * Constructor of syntax_exception class
         *
         * syntax_exception(peg_parser & config, const char* message);
         *
         * @param   message to store const char*
         * @throw   none
         **/
        syntax_exception(const char *);

        /**
         * Copy constructor of syntax_exception class
         *
         * syntax_exception(syntax_exception &);
         *
         * @param   syntax_exception instance to build the syntax_exception
         * @throw   none
         **/
        syntax_exception(const syntax_exception &);

        /**
         * Operator overload= of syntax_exception class
         *
         * operator=(const syntax_exception&);
         *
         * @param   syntax_exception instance const to copy the syntax_exception
         * @throw   none
         **/
        syntax_exception& operator=(const syntax_exception &);

        /**
        * Destructor of syntax_exception class
        *
        * virtual ~syntax_exception() throw();
        *
        * @throw   none
        **/
        virtual ~syntax_exception() throw();

        /**
         * Public methode of syntax_exception
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
         * Public methode of syntax_exception
         *
         *  void set_error( std::string error_message)
         *
         * @returns void
         * @param    error_message to set befor the initial message
         * @throw   none
         **/
         void set_error_message(std::string);

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
 * Public methode of peg_parser.class
 *
 * bool delete_comments();
 *
 * @returns     void
 * @param       buffer_line is a string to remove comment
 * @throw       syntaxe_exception
 */
    bool delete_comments();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    std::stringstream   _string_stream;
    std::string         _line_comment_character;
};

#endif
