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

void Parser::findAmountServers(void) { //Prolly not my best work
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
			if (buffer.find('{') > buffer.find('}')) {
				throw InvalidConfigFile();
			}
			else
				buffer = buffer.substr(buffer.find('{'));
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