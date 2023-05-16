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
 * peg_parser(std::string & path_config_file);
 *
 * @param   string_stream& is a buffer to parse
 * @throw   none
 **/
    peg_parser();

/*
 * Constructor of peg_parser.class
 *
 * peg_parser(const char *path_file);
 *
 * @param   string_stream& is a buffer to parse
 * @throw   none
 **/
    peg_parser(const char *);


/**
 * Constructor of peg_parser.class
 *
 * peg_parser(std::string & string_to_parse);
 *
 * @param   string_stream& is a buffer to parse
 * @throw   none
 **/
    peg_parser(std::string &);

    //@todo add constructor with stringstream arg

/**
* Destructor of peg_parser.class
*
* peg_parser.class.class();
*
* @throw   none
**/
    ~peg_parser();

/**
 * Constructor of peg_parser.class
 *
 * warning loss the position after copy
 *
 * peg_parser(const peg_parser & other);
 *
 * @param   string_stream& is a buffer to parse
 * @throw   none
 **/
    peg_parser(const peg_parser &);

/**
 * Constructor of peg_parser.class
 *
 * warning loss the position after copy
 *
 * peg_parser(const peg_parser & rhs);
 *
 * @param   string_stream& is a buffer to parse
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

        typename std::map<std::string, std::string (T::*)()>::iterator it = map_token_list_action.find(token);
        if (it == map_token_list_action.end()) {
            std::string error("error token in ");
            error += token;
            throw syntax_exception(error.c_str());
        }
        std::string result = (base.*(it->second))();

        std::cout << "Token: " << token << ", Action: " << result << std::endl;
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
 *  bool check_isempty(std::string & buffer_line);
 *
 * @returns     bool if it's empty
 * @param       buffer_line is string to check if is empty
 * @throw       syntaxe_exception
 */
    bool check_is_empty(std::string&);

/**
 * Public methode of peg_parser.class
 *
 * void delete_comments(std::string & buffer_line);
 *
 * @returns     void
 * @param       buffer_line is a string to remove comment
 * @throw       syntaxe_exception
 */
    void delete_comments(std::string&);

/**
 * Public methode of peg_parser.class
 *
 * bool get_next_line(std::string & buffer_line);
 *
 * @returns     bool true if he find new line or false is not
 * @param       void
 * @throw       syntaxe_exception
 */
    bool get_next_line();

/**
 * Public methode of peg_parser.class
 *
 * void parse_bloc(t_bloc&, std::string&, std::pair<std::string, std::vector<std::string> >& info_line);
 *
 * @returns     void
 * @param       bloc is refer to parent
 *              infoline is a token of bloc
 * @throw       syntax_exception
 */
    void parse_bloc(std::pair<std::string, std::vector<std::string> >);

/**
 * Public methode of peg_parser.class
 *
 *  bool is_token(std::string&);
 *
 * @returns     void
 * @param       token is a token to identify
 * @throw       none
 */
    bool is_token(std::string&);

/**
 * Public methode of peg_parser.class
 *
 *  int identify_token(char);
 *
 * @returns     void
 * @param       token is a token to identify
 * @throw       none
 */
    int identify_token(char);

/**
 * Public methode of peg_parser.class
 *
 *  bool identify_flag_token(char&);
 *
 * @returns     true if _flag_token is equal to token
 * @param       token is a token to check
 * @throw       none
 */
    bool identify_flag_token(char);

/**
 * Public methode of peg_parser.class
 *
 *  void set_flag_token(char&);
 *
 * @returns     void
 * @param       token is a token to set
 * @throw       none
 */
    void set_flag_token(char);
/**
 * Public methode of peg_parser.class
 *
 *  bool find_bracket(std::string&);
 *
 * @returns     int position of token
 * @param       word is string to find token
 * @throw       none
 */
    void find_toke(std::string&);

/**
 * Public methode of peg_parser.class
 *
 * bool find_next_word(std::string & word);
 *
 * @returns     bool true if he find new word or false is not
 * @param       word is string to store nex word
 * @throw       syntaxe_exception
 */
    bool find_next_word(std::string&);

/**
 * Public methode of peg_parser.class
 *
 * bool parse_info(t_bloc & bloc);
 *
 * @returns     bool return true else false if }
 * @param       bloc is a bloc where are this info
 * @throw       syntaxe_exception
 */
    bool parse_info();

/**
 * Public methode of peg_parser.class
 *
 * void log_error();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void log_error(std::string&, std::vector<std::string>&);

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    std::stringstream   _string_stream;
};

#endif