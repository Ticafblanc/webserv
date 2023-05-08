//#ifndef PARSER_HPP
//#define PARSER_HPP
//#include "webserv.hpp"
//
//class Parser
//{
//private:
//	Parser();
//	string _arg;
//	std::ifstream _config_file;
//	unsigned int _NServ;
//	vector<string> _blocks;
//	vector<data_server> _servers; //Will hold information for a parsed server block. Might want to use a container to store multiple server blocks
//	std::string readToBuffer(void);
//	void openFile(void);
//	void findAmountServers(void); //Finds the amount of server blocks in the config file given as argument
//	void getBlocks(void);
//	void parseBlocks(void); //main method that takes name of the config file as argument and stores the result into an instance of the Config class
//	void parseSingleBlock(int blockId);
//	void defineDefaultServer(void);
//	void parseRoute(std::string& buffer, vector<Route>& routes);
//	void parseServerNameDirective(std::string& buffer, vector<string>& serverName);
//	void parseListenDirective(std::string& buffer, vector<std::pair<string, int> >& hostPort);
//	std::size_t findStopLocation(std::string& buffer);
//	void fillRoute(std::string& toParse, Route& loc);
//	std::string extractMatch(std::string& buffer);
//	void parseDirectives(vector<string>& directives, Route& loc);
//	void parseErrorPages(string& buffer, vector<std::pair<vector<int>, string> >& error_pages);
//	vector<string> split(string toSplit); //splits a string into a vector of strings on spaces and tabs
//	void parseMaxBodySize(string& buffer, data_server& data);
//	void parseRoot(string& buffer, data_server& data);
//public:
//	//methods
//	Parser(const char *argv);
//	~Parser();
//	void printBlocks(void);
//	void printAll(void);
//	unsigned int getNServ(void) const; //Returns the amount of server blocks given in the format file given as argument
//	vector<data_server> get_data(void);
//	void set_data(vector<data_server>& data_servers);
//	//exceptions
//	class OpenException: public exception {
//		const char* what() const throw();
//	};
//	class InvalidConfigFile: public exception {
//		const char* what() const throw();
//	};
//	class InvalidDirective: public exception {
//		const char* what() const throw();
//	};
//	class NotTheRightNumberOfArgs: public exception {
//		const char* what() const throw();
//	};
//	class InvalidLocationBlock: public exception {
//		const char* what() const throw();
//	};
//	class InvalidPort: public exception {
//		const char* what() const throw();
//	};
//	class DuplicateDirective: public exception {
//		const char* what() const throw();
//	};
//	class UnknownDirective: public exception {
//		const char* what() const throw();
//	};
//};
//
//#endif