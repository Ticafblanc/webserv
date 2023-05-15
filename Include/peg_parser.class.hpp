#ifndef WEBSERV_PEG_PARSER_HPP
#define WEBSERV_PEG_PARSER_HPP

#include <Include/header.hpp>

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

/**
 * Constructor of peg_parser.class
 *
 * peg_parser(std::string & path_config_file);
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

/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

/**
 * Public methode of peg_parser.class
 *
 *  bool parse( std::map<std::string , std::string (*)(std::stringstream &)>& map_token_list_action);
 *
 * @returns     bool if it's empty
 * @param       map_token_list_action is a std::map key = token (string), data = action to do (std::string (*)(std::stringstream&))
 * @throw       syntaxe_exception
 */
    bool parse( std::map<std::string , std::string (*)(std::stringstream &)>&);


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
         * syntax_exception(peg_parser & config, const char* message, int line);
         *
         * @param   peg_parser is a parse_syntax_file reference to set the private _config
         *          to manage the close of parse_syntax_file class
         *          message to store const char*
         * @throw   none
         **/
        syntax_exception(const char *, int);

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
    void find_token(std::string&);

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




































//typedef struct s_bloc {
//
///**
// * Constructor of s_bloc.class
// *
// * s_bloc.class();
// *
// * @param   void
// * @throw   none
// **/
//    s_bloc();
//
///**
//* Destructor of s_bloc.class
//*
//* s_bloc.class.class();
//*
//* @throw   none
//**/
//    ~s_bloc();
//
///**
//* Constructor of s_bloc.class class
//*
//* s_bloc.class(const s_bloc.class& other);
//*
//* @param   void
//* @throw   none
//**/
//    s_bloc(const s_bloc& other);
//
///**
// * Constructor of s_bloc.class class
// *
// * s_bloc.class& operator=(const s_bloc.class& rhs);
// *
// * @returns     s_bloc.class&
// * @param       const s_bloc.class&
// * @throw       none
// */
//    s_bloc& operator=(const s_bloc& rhs);
//
///**
//* Struct s_bloc of s_bloc.class
//* @param    info is std::multimap<std::string, std::vector<std::string> >
// *          contain a list of information associated with their key
// *
// *          bloc is std::multimap<std::multimap<std::string, std::vector<std::string> >, s_bloc>
// *          contain a list of bloc associated with their key who is a info line
//**/
//    std::multimap<std::string, std::vector<std::string> >                     info_line;
//    std::multimap<std::pair<std::string, std::vector<std::string> >, s_bloc>  info_bloc;
//
//} t_bloc;
//
//struct parse_config_file {
//
///*>********************************public section**********************************/
//
//public:
//
///*
//*====================================================================================
//*|                                  Member Fonction                                 |
//*====================================================================================
//*/
//
///**
// * Constructor of parse_config_file.class
// *
// * parse_config_file.class(std::string path_config_file);
// *
// * @param   path_config_file is a std::string contain the path of config file
// * @throw   none
// **/
//    parse_config_file(std::string path_config_file);
//
///**
//* Destructor of parse_config_file.class
//*
//* parse_config_file.class.class();
//*
//* @throw   none
//**/
//    ~parse_config_file();
//
///**
//* Constructor of parse_config_file.class class
//*
//* parse_config_file.class(const parse_config_file.class& other);
//*
//* @param   void
//* @throw   none
//**/
//    parse_config_file(const parse_config_file& other);
//
///**
// * Constructor of parse_config_file.class class
// *
// * parse_config_file.class& operator=(const parse_config_file.class& rhs);
// *
// * @returns     parse_config_file.class&
// * @param       const parse_config_file.class&
// * @throw       none
// */
//    parse_config_file& operator=(const parse_config_file& rhs);
//
///*
//*====================================================================================
//*|                                  Member Exception                                 |
//*====================================================================================
//*/
//
///**
// * Class exception of parse_config_file class
// *
// * class syntax_exception;
// *
// * @inherit std::exception
// **/
//    class syntax_exception: public std::exception
//    {
//    public:
//
//        /**
//         * Constructor of syntax_exception class
//         *
//         * syntax_exception(parse_config_file & config, const char* message, int line);
//         *
//         * @param   parse_config_file is a parse_syntax_file reference to set the private _config
//         *          to manage the close of parse_syntax_file class
//         *          message to store const char*
//         * @throw   none
//         **/
//        syntax_exception(parse_config_file&, const char *, int);
//
//        /**
//         * Copy constructor of syntax_exception class
//         *
//         * syntax_exception(syntax_exception &);
//         *
//         * @param   syntax_exception instance to build the syntax_exception
//         * @throw   none
//         **/
//        syntax_exception(const syntax_exception &);
//
//        /**
//         * Operator overload= of syntax_exception class
//         *
//         * operator=(const syntax_exception&);
//         *
//         * @param   syntax_exception instance const to copy the syntax_exception
//         * @throw   none
//         **/
//        syntax_exception& operator=(const syntax_exception &);
//
//        /**
//        * Destructor of syntax_exception class
//        *
//        * virtual ~syntax_exception() throw();
//        *
//        * @throw   none
//        **/
//        virtual ~syntax_exception() throw();
//
//        /**
//         * Public methode of syntax_exception
//         *
//         * virtual const char * what() const throw();
//         *
//         * @returns  const char * store in private std::string _message
//         *          at the construction defaut constructor "socket error"
//         * @param   void
//         * @throw   none
//         **/
//        virtual const char * what() const throw();
//
//    private:
//        std::string         _message;
//        parse_config_file & _config;
//        int                 _line;
//    };
//
//
///*
//*====================================================================================
//*|                                  Element access                                 |
//*====================================================================================
//*/
//
///**
// * Public methode of parse_config_file.class
// *
// * t_bloc &get_bloc_config_file() const;
// *
// * @returns     std::vector<std::string>& contain all names of server
// * @param       void
// * @throw       none
// */
//    t_bloc &get_bloc_config_file() ;
//
///*>*******************************private section**********************************/
//
//private:
//
///*
//*====================================================================================
//*|                                      Methode                                     |
//*====================================================================================
//*/
//
///**
// * Public methode of parse_config_file.class
// *
// *  bool check_isempty(std::string & buffer_line);
// *
// * @returns     bool if it's empty
// * @param       buffer_line is string to check if is empty
// * @throw       syntaxe_exception
// */
//    bool check_is_empty(std::string&);
//
///**
// * Public methode of parse_config_file.class
// *
// * void delete_comments(std::string & buffer_line);
// *
// * @returns     void
// * @param       buffer_line is a string to remove comment
// * @throw       syntaxe_exception
// */
//    void delete_comments(std::string&);
//
///**
// * Public methode of parse_config_file.class
// *
// * bool get_next_line(std::string & buffer_line);
// *
// * @returns     bool true if he find new line or false is not
// * @param       void
// * @throw       syntaxe_exception
// */
//    bool get_next_line();
//
///**
// * Public methode of parse_config_file.class
// *
// * void parse_bloc(t_bloc&, std::string&, std::pair<std::string, std::vector<std::string> >& info_line);
// *
// * @returns     void
// * @param       bloc is refer to parent
// *              infoline is a token of bloc
// * @throw       syntax_exception
// */
//    void parse_bloc(t_bloc&, std::pair<std::string, std::vector<std::string> >);
//
///**
// * Public methode of parse_config_file.class
// *
// *  bool is_token(std::string&);
// *
// * @returns     void
// * @param       token is a token to identify
// * @throw       none
// */
//    bool is_token(std::string&);
//
///**
// * Public methode of parse_config_file.class
// *
// *  int identify_token(char);
// *
// * @returns     void
// * @param       token is a token to identify
// * @throw       none
// */
//    int identify_token(char);
//
///**
// * Public methode of parse_config_file.class
// *
// *  bool identify_flag_token(char&);
// *
// * @returns     true if _flag_token is equal to token
// * @param       token is a token to check
// * @throw       none
// */
//    bool identify_flag_token(char);
//
///**
// * Public methode of parse_config_file.class
// *
// *  void set_flag_token(char&);
// *
// * @returns     void
// * @param       token is a token to set
// * @throw       none
// */
//    void set_flag_token(char);
///**
// * Public methode of parse_config_file.class
// *
// *  bool find_bracket(std::string&);
// *
// * @returns     int position of token
// * @param       word is string to find token
// * @throw       none
// */
//    void find_token(std::string&);
//
///**
// * Public methode of parse_config_file.class
// *
// * bool find_next_word(std::string & word);
// *
// * @returns     bool true if he find new word or false is not
// * @param       word is string to store nex word
// * @throw       syntaxe_exception
// */
//    bool find_next_word(std::string&);
//
///**
// * Public methode of parse_config_file.class
// *
// * bool parse_info(t_bloc & bloc);
// *
// * @returns     bool return true else false if }
// * @param       bloc is a bloc where are this info
// * @throw       syntaxe_exception
// */
//    bool parse_info(t_bloc &);
//
///**
// * Public methode of parse_config_file.class
// *
// * void log_error();
// *
// * @returns     void
// * @param       void
// * @throw       none
// */
//    void log_error(std::string&, std::vector<std::string>&);
//
///*
//*====================================================================================
//*|                                     Member                                       |
//*====================================================================================
//*/
//    enum {open_bracket, close_bracket, semicolon, white_space};
//    t_bloc                      _bloc_config_file;
//    std::stringstream           _string_stream;
//    std::map<std::string, >     _token_list;
//    int                         _flag_token;
//    std::string                 _indente_log;
//};
//
//
#endif//end of WEBSERV_PARSE_CONFIG_FILE
//
////class Parser
////{
////private:
////	Parser();
////	string _arg;
////	std::ifstream _config_file;
////	unsigned int _NServ;
////	vector<string> _blocks;
////	vector<data_server> _servers; //Will hold information for a parsed server block. Might want to use a container to store multiple server blocks
////	std::string readToBuffer(void);
////	void openFile(void);
////	void findAmountServers(void); //Finds the amount of server blocks in the config file given as argument
////	void getBlocks(void);
////	void parseBlocks(void); //main method that takes name of the config file as argument and stores the result into an instance of the Config class
////	void parseSingleBlock(int blockId);
////	void defineDefaultServer(void);
////	void parseRoute(std::string& buffer, vector<Route>& routes);
////	void parseServerNameDirective(std::string& buffer, vector<string>& serverName);
////	void parseListenDirective(std::string& buffer, vector<std::pair<string, int> >& hostPort);
////	std::size_t findStopLocation(std::string& buffer);
////	void fillRoute(std::string& toParse, Route& loc);
////	std::string extractMatch(std::string& buffer);
////	void parseDirectives(vector<string>& directives, Route& loc);
////	void parseErrorPages(string& buffer, vector<std::pair<vector<int>, string> >& error_pages);
////	vector<string> split(string toSplit); //splits a string into a vector of strings on spaces and tabs
////	void parseMaxBodySize(string& buffer, data_server& data);
////	void parseRoot(string& buffer, data_server& data);
////public:
////	//methods
////	Parser(const char *argv);
////	~Parser();
////	void printBlocks(void);
////	void printAll(void);
////	unsigned int getNServ(void) const; //Returns the amount of server blocks given in the format file given as argument
////	vector<data_server> get_data(void);
////	void set_data(vector<data_server>& data_servers);
////	//exceptions
////	class OpenException: public exception {
////		const char* what() const throw();
////	};
////	class InvalidConfigFile: public exception {
////		const char* what() const throw();
////	};
////	class InvalidDirective: public exception {
////		const char* what() const throw();
////	};
////	class NotTheRightNumberOfArgs: public exception {
////		const char* what() const throw();
////	};
////	class InvalidLocationBlock: public exception {
////		const char* what() const throw();
////	};
////	class InvalidPort: public exception {
////		const char* what() const throw();
////	};
////	class DuplicateDirective: public exception {
////		const char* what() const throw();
////	};
////	class UnknownDirective: public exception {
////		const char* what() const throw();
////	};
////};
////
