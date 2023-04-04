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
	string comp("{ 	");
	this->openFile();
	std::getline(this->config_file, buffer, '\0');
	this->config_file.close();
	
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

// void Parser::findAmountServers(void) { //scene 1 prise 32
// 	string buffer;
// 	bool checkServer = false;
// 	string comp("{ 	");
// 	int lock = 0;
// 	this->openFile();
// 	while (std::getline(this->config_file, buffer, '\n')) { // I think this is fine
// 		if (buffer.find("server") != string::npos){ //I think this is fine
// 			if (comp.find(buffer[buffer.find("server") + 6]) == string::npos && buffer[buffer.find("server") + 6] != '\0')
// 				throw InvalidConfigFile();
// 			checkServer = true;
// 		}
// 		if (buffer.find("{") == string::npos) {
// 			while (std::getline(this->config_file, buffer, '\n'))
// 				if (buffer.find('{') != string::npos)
// 					break;
// 		}
// 		while (checkServer == true) {
// 			if (comp.find('{') != string::npos)
// 				lock++;
// 			if (comp.find('}') != string::npos)
// 				lock--;
// 			if (lock == 0) {
// 				NServ++;
// 				checkServer = false;
// 			}
// 			if (checkServer == true)
// 				if (!std::getline(this->config_file, buffer, '\n'))
// 					break;
// 		}
// 	}
// }

// void Parser::findAmountServers(void) { //fuck
// 	string buffer;
// 	string comp("{ 	");
// 	bool checkServer = false;
// 	int lock = 0;
// 	this->openFile();
// 	while (std::getline(this->config_file, buffer, '\n')) { // I think this is fine
// 		if (buffer.find("server") != string::npos){ //I think this is fine
// 			if (comp.find(buffer[buffer.find("server") + 6]) == string::npos && buffer[buffer.find("server") + 6] != '\0')
// 				throw InvalidConfigFile();
// 			checkServer = true;
// 		}
// 		while (buffer.find('{') == string::npos) {
// 			if (buffer.find('{') != string::npos) //I have no idea why I have to do this. This is fucking stupid but otherwise the loop runs forever
// 				break;
// 			std::getline(this->config_file, buffer, '\n');
// 		}
// 		while (checkServer == true) { //need a better loop for when to end
// 			if (buffer.find('{') != string::npos && buffer.find('}') != string::npos) {
// 				if (buffer.find('{') > buffer.find('}')){
// 					throw InvalidConfigFile();   //Throwing exception if closing curly bracket comes before opening curly bracket
// 				}
// 			}
// 			if (buffer.find('{') != string::npos) {
// 				lock++;
// 			}
// 			if (buffer.find('}') != string::npos) {
// 				lock--;
// 			}
// 			if (lock == 0) {
// 				NServ++;
// 				checkServer = false;
// 			}
// 			if (checkServer == true)
// 				std::getline(this->config_file, buffer, '\n');
// 		}
// 	}
// }

// void Parser::findAmountServers(void) { //trying a different approach
// 	string buffer;
// 	bool checkServer = false;
// 	int lock = 0;
// 	this->openFile();
// 	while (std::getline(this->config_file, buffer, '\n')) {
// 		while (buffer.find("{") == string::npos) {
// 			if (buffer.find("}") != string::npos && lock == 0)
// 				throw InvalidConfigFile();
// 			if (!std::getline(this->config_file, buffer, '\n'))
// 				throw InvalidConfigFile();
// 		}
// 		if (buffer.find("}") == string::npos)
// 			lock++;
// 		if (buffer.find("{") > buffer.find("}"))
// 				throw InvalidConfigFile();
// 		while (lock != 0) {
// 			if (!std::getline(this->config_file, buffer, '\n'))
// 				throw InvalidConfigFile();
// 			if (buffer.find("}") != string::npos)
// 				lock--;
// 			if (buffer.find("{") != string::npos)
// 				lock++;
// 		}
// 		if (lock!= 0)
// 			throw InvalidConfigFile();
// 		else
// 			NServ++;
// 	}
// }

unsigned int Parser::getNServ(void) const {
	return NServ;
}

const char* Parser::OpenException::what() const throw() {
	return "Failed to open file";
}

const char* Parser::InvalidConfigFile::what() const throw() {
	return "Invalid configuration file";
}