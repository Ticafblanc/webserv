#include "../Include/Parser.hpp"

Parser::Parser(char **argv, int argc): arg(argv[1]), argc(argc), NServ(0) { }

Parser::~Parser() {
	return ;
}

void Parser::parse_config_file(void) {
	// server {info} server marks the type of block and the brackets mark the start and end of the server block
	string buffer;
	std::ifstream config_file;
	if (argc == 2)
		config_file.open(arg);
	else
		config_file.open("../config_files/default");
	if (config_file.fail() || !config_file.is_open())
		throw OpenException();
	while (std::getline(config_file, buffer, '\n')) {
		if (buffer.find("server") != string::npos) {
			
		}
		// if (buffer.find(""))
	}	
}

void Parser::findAmountServers(void) {
	string buffer;
	std::ifstream config_file;
	if (argc == 2)
		config_file.open(arg);
	else
		config_file.open("../config_files/default");
	if (config_file.fail() || !config_file.is_open())
		throw OpenException();
	while (std::getline(config_file, buffer, '\n')) {
		if (buffer.find("server") != string::npos) {
			for (string::iterator it = (buffer.begin() + buffer.find("server") + 6); it < buffer.end(); it++) {
				if (*it == ' ') {
					NServ++;
					break;
				}
			}
		}
	}
}

unsigned int Parser::getNServ(void) const {
	return NServ;
}

const char* Parser::OpenException::what() const throw() {
	return "Failed to open file";
}