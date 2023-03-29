#include "../Include/Parser.hpp"

Parser::Parser() {}

Parser::Parser(char **argv, int argc): arg(argv[1]), argc(argc) { }

void Parser::parse_config_file(void) {
	// server {info} server marks the type of block and the brackets mark the start and end of the server block
	std::string buffer;
	std::ifstream config_file(arg);
	while (std::getline(config_file, buffer, '\n')) {
		if (buffer.find("server")) 
	}	
}
