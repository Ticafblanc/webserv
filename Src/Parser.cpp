#include "../Include/Parser.hpp"

Parser::Parser() {}

Parser::Parser(char **argv): arg(argv[1]) { }

void Parser::parse_config_file(void) {

}

// server {info} server marks the type of block and the brackets mark the start and end of the server block