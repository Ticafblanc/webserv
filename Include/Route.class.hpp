#ifndef ROUTE_HPP
# define ROUTE_HPP
# include "header.hpp"

// routes with
//◦Define a HTTP redirection.
//◦Define a directory or a file from where the file should be searched
//	(for example, if url /kapouet is rooted to /tmp/www, url /kapouet/pouic/toto/pouet is /tmp/www/pouic/toto/pouet).
//◦Set a default file to answer if the request is a directory.

class Route
{
private:
	vector<string>						_allowed_methods; //list of accepted HTTP methods for the route. corresponds to ◦Define a list of accepted HTTP methods for the route. if blank all accepted
	string								_prefix; //directory given after location
	string								_httpRedir;
	bool 								_autoIndex; //corresponds to ◦Turn on or off directory listing.
	string 								_searchDir;
	string								_root;
	string 								_defaultDirFile;
	string 								_savePath; //corresponds to ◦Make the route able to accept uploaded files and configure where they should be saved
	vector<std::pair<string, string> > 	_cgi; //first element of pair is extension, second is executable. corresponds to ◦Execute CGI based on certain file extension (for example .php).
public:
	Route();
	~Route();

	void setAllowedMethods(vector<string>& allowed_methods) throw();
	const vector<string>& getAllowedMethods(void) const throw();
	void push_method(const string& method) throw();

	void setPrefix(string& prefix) throw();
	const string &getPrefix(void) const throw();

	void setHttpRedir(string& redir) throw();
	const string& getHttpRedir(void) const throw();

	void setDirectoryListing(bool state) throw();
	const bool getDirectoryListing(void) const throw();

	void setSearchDir(string& dir) throw();
	const string& getSearchDir(void) const throw();

	void setDefaultDirFile(string& dirFile) throw();
	const string& getDefaultDirFile(void) const throw();

	void setSavePath(string& path) throw();
	const string& getSavePath(void) const throw();

	void setRoot(const string& root);
	const string& getRoot(void) const throw();


	class DuplicateRoot: public std::exception {
		const char *what() const throw();
	};
};

#endif