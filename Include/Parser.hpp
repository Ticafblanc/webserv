#include "Config.hpp"
// •Choose the port and host of each ’server’.
// •Setup the server_names or not.
// •The first server for a host:port will be the default for this host:port (that means it will answer to all the requests that don’t belong to an other server).
// •Setup default error pages.
// •Setup routes with one or multiple of the following rules/configuration (routes wont
// be using regexp):
// ◦Define a list of accepted HTTP methods for the route.
// ◦Define a HTTP redirection.
// ◦Define a directory or a file from where the file should be searched (for example,
// if url /kapouet is rooted to /tmp/www, url /kapouet/pouic/toto/pouet is /tmp/www/pouic/toto/pouet).
// ◦Turn on or off directory listing.
// ◦Set a default file to answer if the request is a directory.
// ◦Execute CGI based on certain file extension (for example .php).
// ◦Make the route able to accept uploaded files and configure where they should be saved.

// Do you wonder what a CGI is? Because you won’t call the CGI directly, use the full path as PATH_INFO.
// Just remember that, for chunked request, your server needs to unchunked
// it and the CGI will expect EOF as end of the body.
// Same things for the output of the CGI. If no content_length is returned
// from the CGI, EOF will mark the end of the returned data.
// Your program should call the CGI with the file requested as first argument.
// The CGI should be run in the correct directory for relative path file access.
// Your server should work with one CGI (php-CGI, Python, and so forth).

// You must provide some configuration files and default basic files to test and demon-
// strate every feature works during evaluation.

// Syntax:	server_name name ...;
// Default:	server_name "";
// Context:	server
// Sets names of a virtual server, for example:
// server {
//     server_name example.com www.example.com;
// }

// •Limit client body size.
// Syntax:	client_max_body_size size;
// Default:	
// client_max_body_size 1m;
// Context:	http, server, location
// Sets the maximum allowed size of the client request body. If the size in a request exceeds the configured value, the 413 (Request Entity Too Large) error is returned to the client. Please be aware that browsers cannot correctly display this error. Setting size to 0 disables checking of client request body size.

// Syntax:	client_body_buffer_size size;
// Default:	
// client_body_buffer_size 8k|16k;
// Context:	http, server, location
// Sets buffer size for reading client request body. In case the request body is larger than the buffer, the whole body or only its part is written to a temporary file. By default, buffer size is equal to two memory pages. This is 8K on x86, other 32-bit platforms, and x86-64. It is usually 16K on other 64-bit platforms.

// Syntax:	error_page code ... [=[response]] uri;
// Default:	—
// Context:	http, server, location, if in location
// Defines the URI that will be shown for the specified errors. A uri value can contain variables.

// Example:

// error_page 404             /404.html;
// error_page 500 502 503 504 /50x.html;
// This causes an internal redirect to the specified uri with the client request method changed to “GET” (for all methods other than “GET” and “HEAD”).

// Furthermore, it is possible to change the response code to another using the “=response” syntax, for example:

// error_page 404 =200 /empty.gif;
// If an error response is processed by a proxied server or a FastCGI/uwsgi/SCGI/gRPC server, and the server may return different response codes (e.g., 200, 302, 401 or 404), it is possible to respond with the code it returns:

// error_page 404 = /404.php;
// If there is no need to change URI and method during internal redirection it is possible to pass error processing into a named location:

// location / {
//     error_page 404 = @fallback;
// }

// location @fallback {
//     proxy_pass http://backend;
// }
// If uri processing leads to an error, the status code of the last occurred error is returned to the client.
// It is also possible to use URL redirects for error processing:

// error_page 403      http://example.com/forbidden.html;
// error_page 404 =301 http://example.com/notfound.html;
// In this case, by default, the response code 302 is returned to the client. It can only be changed to one of the redirect status codes (301, 302, 303, 307, and 308).

// The code 307 was not treated as a redirect until versions 1.1.16 and 1.0.13.
// The code 308 was not treated as a redirect until version 1.13.0.
// These directives are inherited from the previous configuration level if and only if there are no error_page directives defined on the current level.

class Parser
{
private:
	Parser();
	std::string arg;
	Config configFile; //Will hold informations for a parsed server block. Might want to use a container to store multiple server blocks
public:
	Parser(char **argv);
	~Parser();
	void parse_config_file(void); //main method that takes name of the config file as argument and stores the result into an instance of the Config class
	//methods
};