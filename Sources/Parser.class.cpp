#include "../Include/Parser.class.hpp"

Parser::Parser(char **argv, int argc): arg(argv[1]), argc(argc), NServ(0) { }

Parser::~Parser() { }

void Parser::openFile(void) {
	if (this->argc == 2)
		this->config_file.open(arg.c_str());
	else
		this->config_file.open("../config_files/default");
	if (this->config_file.fail() || !this->config_file.is_open())
		throw OpenException();
}

void Parser::getBlocks(void) {
	string buffer;
	string block;
	int lock = 0;
	this->openFile();
	std::getline(this->config_file, buffer, '\0');
	this->config_file.close();
	while (buffer.size() != 0) {
		if (buffer.find("server") == string::npos)
			break ;
		buffer = buffer.substr(buffer.find("server") + 6);
		buffer = buffer.substr(buffer.find('{'));
		for (string::iterator it = buffer.begin(); it < buffer.end(); it++) {
			if (*it == '{')
				lock++;
			if (*it == '}')
				lock--;
			if (lock == 0) {
				
			}
		}
	}
}

void Parser::parseBlocks(void) {
	// every server block is contained within the vector of strings blocks
	
}

//need to fix to detect wrong character in between server blocks
//could make another function that checks in between server blocks. Probably the best option

//can't have server alone without brackets
//can't have brackets without server before them
//brackets must be in correct order
//not mandatory to have a server directive. Will provide a default one
//if server_name not specified, uses empty string. If more than one server with the same server name, duplicates are ignored
//directives within a server block need to end with ;
//will make it so there are no unwanted brackets in between server directives
//there should be no random strings either in between server directives
void Parser::findAmountServers(void) { //Counts the number of server blocks. Throws an error for invalid options
	string buffer;
	string comp("{ 	");
	int lock = 0;
	this->openFile();
	std::getline(this->config_file, buffer, '\0');
	this->config_file.close();
	while (buffer.size() != 0) {
		if (buffer.find("server") == string::npos)
			break ;
		buffer = buffer.substr(buffer.find("server"));
		if (comp.find(buffer[buffer.find("server") + 6]) == string::npos && buffer[buffer.find("server") + 6] != '\n') {
			throw InvalidConfigFile();
		}
		else {
			if (buffer.find('{') > buffer.find('}') || buffer.find('{') == string::npos) {
				throw InvalidConfigFile();
			}
			else {
				cout << "Fail here" << endl;
				buffer = buffer.substr(buffer.find('{'));
			}
			for (string::iterator it = buffer.begin(); it < buffer.end(); it++) {
				if (*it == '{')
					lock++;
				if (*it == '}')
					lock--;
				if (lock == 0) {
					NServ++;
					buffer = buffer.substr((it - buffer.begin()) + 1);
					break ;
				}
			}
		}
	}
	if (NServ == 0)
		throw InvalidConfigFile();
}

unsigned int Parser::getNServ(void) const {
	return NServ;
}

const char* Parser::OpenException::what() const throw() {
	return "Failed to open file";
}

const char* Parser::InvalidConfigFile::what() const throw() {
	return "Invalid configuration file";
}