#include "../Include/Parser.class.hpp"

Parser::Parser(char **argv, int argc): _arg(argv[1]), _argc(argc), _NServ(0) {
	findAmountServers();
	getBlocks();
	parseBlocks();
}

Parser::~Parser() { }

std::string Parser::readToBuffer(void) {
	string buffer;
	this->openFile();
	std::getline(this->_config_file, buffer, '\0');
	this->_config_file.close();
	return buffer;
}

void Parser::openFile(void) {
	if (this->_argc == 2)
		this->_config_file.open(_arg.c_str());
	else
		this->_config_file.open("../config_files/default");
	if (this->_config_file.fail() || !this->_config_file.is_open())
		throw OpenException();
}

void Parser::findAmountServers(void) { //Last valid option
	string buffer = readToBuffer();
	string comp("{ 	\n");
	int lock = 0;
	bool server_lock = false;
	while (buffer.size() != 0) {
		if (buffer.find("server") == string::npos)
			break ;
		buffer = buffer.substr(buffer.find("server"));
		if (comp.find(buffer[buffer.find("server") + 6]) == string::npos) {
			throw InvalidConfigFile();
		}
		else {
			if (buffer.find('{') > buffer.find('}') || buffer.find('{') == string::npos) {
				throw InvalidConfigFile();
			}
			else {
				buffer = buffer.substr(6);
				if (buffer.find("server") < buffer.find('{'))
					throw InvalidConfigFile();
				buffer = buffer.substr(buffer.find('{'));
			}
			for (string::iterator it = buffer.begin(); it < buffer.end(); it++) {
				if (*it == '{')
					lock++;
				if (*it == '}')
					lock--;
				if (lock == 0) {
					_NServ++;
					buffer = buffer.substr((it - buffer.begin()) + 1);
					break ;
				}
			}
			if (lock != 0)
				throw InvalidConfigFile();
		}
	}
}

void Parser::getBlocks(void) {
	string buffer = readToBuffer();
	string block;
	int lock = 0;
	while (buffer.size() != 0) {
		if (buffer.find("server") == string::npos)
			break ;
		buffer = buffer.substr(buffer.find('{'));
		for (string::iterator it = buffer.begin(); it < buffer.end(); it++) {
			if (*it == '{')
				lock++;
			if (*it == '}')
				lock--;
			if (lock == 0) {
				_blocks.push_back(buffer.substr(1, (it - buffer.begin() - 1)));
				buffer = buffer.substr((it - buffer.begin()) + 1);
				break ;
			}
		}
	}
}

/****************attributes*****************/

//listen host:port; if only port is provided host defaults to 0.0.0.0
//server_name name1 name2 ... ; empty server_name is an error
//host, port, server_names, default error pages, routes with
//◦Define a list of accepted HTTP methods for the route.
//◦Define a HTTP redirection.
//◦Define a directory or a file from where the file should be searched
//	(for example, if url /kapouet is rooted to /tmp/www, url /kapouet/pouic/toto/pouet is /tmp/www/pouic/toto/pouet).
//◦Turn on or off directory listing.
//◦Set a default file to answer if the request is a directory.
//◦Execute CGI based on certain file extension (for example .php).
//◦Make the route able to accept uploaded files and configure where they should be saved

void Parser::parseSingleBlock(int blockId) {
	string buffer = _blocks.at(blockId);
	string tempBuffer;
	bool parsingDone = false;
	while (parsingDone == false) {
		if (buffer.find("server_name") != string::npos) {

		}
		if (buffer.find("listen") != string::npos) {

		}
		if (buffer.find("location") != string::npos) {
			parseRoute();
		}
	}
}

void Parser::parseRoute(void) {

}

void Parser::parseBlocks(void) { // every server block is contained within the vector blocks in string form
	if (_NServ == 0)
		defineDefaultServer();
	else {
		data_server data;
		for (int i = 0; i < _NServ; i++) {
			parseSingleBlock(i);
		}
	}
}

void Parser::defineDefaultServer(void) { //Define a single default server if _NServ == 0 
	data_server data; //new data instance
	vector<string> serverName; //vector of string that holds the name of the server
	vector<std::pair<string, int> > newPair; //vector of pairs that holds the host & port
	std::pair<string, int> hostPort("", 8000); //new pair to be added into newPair
	newPair.push_back(hostPort); //adding hostPort to newPair
	serverName.push_back(""); //adding empty string to serverName
	data.setServerName(0, serverName); //setting serverName into data
	data.setHostPort(0, newPair); //setting host/port into data
	data.setIdServer(0); //setting serverId into data
	_servers.push_back(data); //adding data to _servers
}

void Parser::printBlocks(void) { //just for testing purposes
	for (int i = 0; i < _NServ; i++) {
		cout << _blocks.at(i) << endl;
	}
}

unsigned int Parser::getNServ(void) const {
	return _NServ;
}

const char* Parser::OpenException::what() const throw() {
	return "Failed to open file";
}

const char* Parser::InvalidConfigFile::what() const throw() {
	return "Invalid configuration file";
}

const char* Parser::InvalidDirective::what() const throw() {
	return "Invalid directive detected";
}