#ifndef ROUTE_HPP
# define ROUTE_HPP
# include "header.hpp"

// routes with
//◦Define a list of accepted HTTP methods for the route. if blank all accepted
//◦Define a HTTP redirection.
//◦Define a directory or a file from where the file should be searched
//	(for example, if url /kapouet is rooted to /tmp/www, url /kapouet/pouic/toto/pouet is /tmp/www/pouic/toto/pouet).
//◦Turn on or off directory listing.
//◦Set a default file to answer if the request is a directory.
//◦Execute CGI based on certain file extension (for example .php).
//◦Make the route able to accept uploaded files and configure where they should be saved

class Route
{
private:
	vector<string>						_methods; //list of accepted HTTP methods for the route
	string								_match; 
	string								_httpRedir;
	bool 								_directoryListing;
	string 								_searchDir;
	string 								_defaultDirFile;
	string 								_savePath;
	vector<std::pair<string, string> > 	_cgi; //first element of pair is extension, second is executable
public:
	Route();
	~Route();
	void setMatch(string& match) throw();
	string &getMatch(void) throw();
	void setHttpRedir(string& redir) throw();
	string& getHttpRedir(void) throw();
	void setDirectoryListing(bool state) throw();
	bool getDirectoryListing(void) throw();
	void setSearchDir(string& dir) throw();
	string& getSearchDir(void) throw();
	void setDefaultDirFile(string& dirFile) throw();
	string& getDefaultDirFile(void) throw();
	void setSavePath(string& path) throw();
	string& getSavePath(void) throw();
};

#endif