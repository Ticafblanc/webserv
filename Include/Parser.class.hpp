#ifndef PARSER_HPP
#define PARSER_HPP
#include "webserv.hpp"

class Parser
{
private:
	Parser();
	string _arg;
	std::ifstream _config_file;
	int _argc;
	unsigned int _NServ;
	vector<string> _blocks;
	vector<data_server> _servers; //Will hold informations for a parsed server block. Might want to use a container to store multiple server blocks
	std::string readToBuffer(void);
	void openFile(void);
	void findAmountServers(void); //Finds the amount of server blocks in the config file given as argumente
	void getBlocks(void);
	void parseBlocks(void); //main method that takes name of the config file as argument and stores the result into an instance of the Config class
	void parseSingleBlock(int blockId);
	void defineDefaultServer(void);
	void parseRoute(void);
	void parseServerNameDirective(std::string& buffer, vector<string>& serverName);
	void parseListenDirective(std::string& buffer, vector<std::pair<string, int> >& hostPort);
public:
	Parser(char **argv, int argc);
	~Parser();
	void printBlocks(void);
	unsigned int getNServ(void) const; //Returns the amount of server blocks given in the format file given as argument
	//methods
	class OpenException: public exception {
		const char* what() const throw();
	};
	class InvalidConfigFile: public exception {
		const char* what() const throw();
	};
	class InvalidDirective: public exception {
		const char* what() const throw();
	};
	class NotTheRightNumberOfArgs: public exception {
		const char* what() const throw();
	};
};

#endif