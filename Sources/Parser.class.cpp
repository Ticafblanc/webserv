#include "../Include/Parser.class.hpp"

Parser::Parser(char **argv, int argc): _arg(argv[1]), _argc(argc), _NServ(0) {
	findAmountServers();
	getBlocks();
	parseBlocks();
	data_server server = this->_servers[0];
	vector<string> serverNames = server.getServerName();
	vector<std::pair<string, int> > hostPorts = server.getHostPort();
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

//listen host:port; if only port is provided host defaults to 0.0.0.0; can't have 2 listens with the same port; different port is ok, can have the same hostname
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

void Parser::parseSingleBlock(int blockId) { //parses a single function block and populates a new data_server instance
	data_server data;
	vector<string> serverName;
	vector<std::pair<string, int> > hostPort;
	vector<Route> routes;
	string buffer = _blocks.at(blockId);
	bool parsingDone = false;
	while (parsingDone == false) {
		if (buffer.find("server_name") != string::npos) {
			parseServerNameDirective(buffer, serverName);
		}
		if (buffer.find("listen") != string::npos) {
			parseListenDirective(buffer, hostPort);
		}
		if (buffer.find("location") != string::npos) {
			parseRoute(buffer, routes);
			exit(0);
		}
		if (buffer.find("listen") == string::npos && buffer.find("listen") == string::npos && buffer.find("location") == string::npos) {
			parsingDone = true;
		}
	}
	if (serverName.size() == 0) {
		serverName.push_back("");
	}
	if (hostPort.size() == 0) {
		hostPort.push_back(std::make_pair("0.0.0.0", 8000));
	}
	data.setServerName(serverName);
	data.setHostPort(hostPort);
	this->_servers.push_back(data);
}

void Parser::parseServerNameDirective(std::string& buffer, vector<string>& serverName) {
	std::size_t start = buffer.find("server_name");
	std::size_t stop = buffer.find(';', start);
	if (stop == string::npos)
		throw InvalidDirective();
	string tempBufferStart = buffer.substr(0, start);
	string tempBufferStop = buffer.substr(stop + 1);
	string toParse = buffer.substr(start, ((stop + 1) - start));
	buffer.clear();
	buffer = buffer.append(tempBufferStart);
	buffer = buffer.append(tempBufferStop);
	if (toParse[toParse.find("server_name") + 11] != ' ')
		throw InvalidDirective();
	toParse = toParse.substr(toParse.find("server_name") + 11);
	start = 0, stop = 0;
	for (string::iterator it = toParse.begin(); it < toParse.end(); it++) {
		if (isalnum(*it) != 0 && start == 0)
			start = it - toParse.begin();
		if ((isspace(*it) && start != 0) || *it == ';')
			stop = it - toParse.begin();
		if (start != 0 && stop != 0) {
			serverName.push_back(toParse.substr(start, (stop - start)));
			start = 0, stop = 0;
		}
	}
	if (serverName.size() == 0)
		throw NotTheRightNumberOfArgs();
}

void Parser::parseListenDirective(std::string& buffer, vector<std::pair<string, int> >& hostPort) {
	std::pair<string, int> newPair;
	int port;
	string tempHost;
	string tempPort;

	std::size_t start = buffer.find("listen");
	std::size_t stop = buffer.find(';', start);
	if (stop == string::npos)
		throw InvalidDirective();
	string tempBufferStart = buffer.substr(0, start);
	string tempBufferStop = buffer.substr(stop + 1);
	string toParse = buffer.substr(start, ((stop + 1) - start));
	buffer.clear();
	buffer = buffer.append(tempBufferStart);
	buffer = buffer.append(tempBufferStop);
	if (toParse[toParse.find("listen") + 6] != ' ')
		throw InvalidDirective();
	toParse = toParse.substr(toParse.find("listen") + 6);
	start = 0, stop = 0;
	for (string::iterator it = toParse.begin(); it < toParse.end(); it++) {
		if (isalnum(*it) != 0 && start == 0)
			start = it - toParse.begin();
		if ((isspace(*it) != 0 && start != 0) || *it == ';')
			stop = it - toParse.begin();
		if (start != 0 && stop != 0) {
			if (toParse.find(':') != string::npos) {//getting both port and host
				tempHost = toParse.substr(start, toParse.find(':') - 1);
				tempPort = toParse.substr(toParse.find(':') + 1, (stop - toParse.find(':') - 1));
				port = std::stoi(tempPort);
				newPair = std::make_pair<string, int>(tempHost, port);
				hostPort.push_back(newPair);
			}
			else { //determine if host or port
				try //not sure about that, seems to work fine
				{
					port = std::stoi(toParse.substr(start, stop - start));
					newPair = std::make_pair<string, int>("0.0.0.0", port);
					hostPort.push_back(newPair);
				}
				catch(const std::exception& e)
				{
					tempHost = toParse.substr(start, stop - start);
					newPair = std::make_pair<string, int>(tempHost, 80);
					hostPort.push_back(newPair);
				}
			}
			if (hostPort.size() > 1)
				throw NotTheRightNumberOfArgs();
			start = 0, stop = 0;
		}
	}
}

void Parser::parseRoute(std::string& buffer, vector<Route>& routes) {
	Route loc;
	std::size_t start = buffer.find("location");
	std::size_t stop = this->findStopLocation(buffer); // throws if something goes wrong
	std::string tempBufferStart = buffer.substr(0, start);
	std::string tempBufferStop = buffer.substr(stop + 1);
	std::string toParse = buffer.substr(start, (stop - start + 1));
	buffer.clear();
	buffer = buffer.append(tempBufferStart);
	buffer = buffer.append(tempBufferStop);
	fillRoute(toParse, routes);
}

void Parser::fillRoute(std::string& toParse, vector<Route>& routes) {
	std::size_t start = toParse.find("location") + 8;
	for (string::iterator it = toParse.begin() + start; it < toParse.end(); it++) {
		
	}
}

std::size_t Parser::findStopLocation(std::string& buffer) {
	std::size_t start = buffer.find("location");
	if (isspace(buffer[start + 8]) == 0)
		throw InvalidDirective();
	start = buffer.find('{', start);
	if (start == string::npos)
		throw InvalidLocationBlock();
	int lock = 0;
	for (string::iterator it = (buffer.begin() + start); it < buffer.end(); it++) {
		if (*it == '{')
			lock++;
		if (*it == '}')
			lock--;
		if (lock == 0) {
			return (it - buffer.begin());
		}
	}
	if (lock != 0)
		throw InvalidLocationBlock();
	return (string::npos);
}

void Parser::parseBlocks(void) { // every server block is contained within the vector blocks in string form
	if (_NServ == 0)
		defineDefaultServer();
	else {
		for (unsigned int i = 0; i < _NServ; i++) {
			parseSingleBlock(i);
		}
	}
}

void Parser::defineDefaultServer(void) { //Define a single default server if _NServ == 0 
	data_server data; //new data instance
	vector<string> serverName; //vector of string that holds the name of the server
	vector<std::pair<string, int> > hostPort; //vector of pairs that holds the host & port
	std::pair<string, int> newPair("0.0.0.0", 8000); //new pair to be added into hostPort
	hostPort.push_back(newPair); //adding newPair to hostPort
	serverName.push_back(""); //adding empty string to serverName
	data.setServerName(serverName); //setting serverName into data
	data.setHostPort(hostPort); //setting host/port into data
	data.setIdServer(0); //setting serverId into data
	this->_servers.push_back(data); //adding data to _servers
}

void Parser::printBlocks(void) { //just for testing purposes
	for (unsigned int i = 0; i < _NServ; i++) {
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

const char* Parser::NotTheRightNumberOfArgs::what() const throw() {
	return "Not the right number of arguments for directive";
}

const char* Parser::InvalidLocationBlock::what() const throw() {
	return "Invalid location block";
}