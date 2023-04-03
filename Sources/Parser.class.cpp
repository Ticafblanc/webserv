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

void Parser::parse_config_file(void) {
	// server {info} server marks the type of block and the brackets mark the start and end of the server block
	string buffer;
	this->openFile();
	while (std::getline(this->config_file, buffer, '\n')) {
		if (buffer.find("server") != string::npos) {
			
		}
		// if (buffer.find(""))
	}	
}

void Parser::readfile(void) {
	this->openFile();
	string buffer;
	while (std::getline(this->config_file, buffer, '\n')){
		cout << buffer << endl;
	}
}

void Parser::findAmountServers(void) { //can prolly do better
	string buffer;
	string comp("{ 	");
	bool checkServer = false;
	int lock = 0;
	this->openFile();
	while (std::getline(this->config_file, buffer, '\n')) {
		if (buffer.find("server") != string::npos){
			if (comp.find(buffer[buffer.find("server") + 6]) == string::npos && buffer[buffer.find("server") + 6] != '\0')
				throw InvalidConfigFile();
			checkServer = true;
		}
		while (checkServer == true) {
			cout << buffer << endl;
			if (buffer.find('{') != string::npos && buffer.find('}') != string::npos) {
				if (buffer.find('{') > buffer.find('}')){
					throw InvalidConfigFile();   //Throwing exception if closing curly bracket comes before opening curly bracket
				}
			}
			if (buffer.find('{') != string::npos) {
				cout << "lock ++" << endl;
				lock++;
			}
			if (buffer.find('}') != string::npos) {
				cout << "lock --" << endl;
				lock--;
			}
			if (lock == 0) {
				NServ++;
				checkServer = false;
			}
			if (checkServer == true)
				std::getline(this->config_file, buffer, '\n');
		}
	}
}

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