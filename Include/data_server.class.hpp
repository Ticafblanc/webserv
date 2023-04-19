//
// Created by Matthis DoQuocBao on 2023-03-27.
// Hijacked by Yan on 2023-04-06. This is my class now
//
#ifndef WEBSERV_DATA_SERVER_HPP
#define WEBSERV_DATA_SERVER_HPP

#include "header.hpp"
#include "Route.class.hpp"

//empty server_name is an error. if no server_name default name is ""
//default error pages, routes with
//◦Define a list of accepted HTTP methods for the route.
//◦Define a HTTP redirection.
//◦Define a directory or a file from where the file should be searched
//	(for example, if url /kapouet is rooted to /tmp/www, url /kapouet/pouic/toto/pouet is /tmp/www/pouic/toto/pouet).
//◦Turn on or off directory listing.
//◦Set a default file to answer if the request is a directory.
//◦Execute CGI based on certain file extension (for example .php).
//◦Make the route able to accept uploaded files and configure where they should be saved
class data_server{
/*
*====================================================================================
*|                                     Public Member                                |
*====================================================================================
*/

public:



/*
*====================================================================================
*|                                     Private Member                               |
*====================================================================================
*/

private:
    vector<string>                              _server_name;
    vector<std::pair<string, int> >             _host_port;
    vector<std::pair<vector<int>, string> >     _error_page;
    vector<Route>                               _routes;
    string                                      _root;
    std::size_t                                 _client_max_body_size;
    bool                                        _max_body_size_def;
    int                                         _serverId;
    sockaddr_in                                 _address;
    std::size_t                                 _addr_len;
    int                                         _server_fd;

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

public:

    data_server();
    ~data_server();
    data_server(const data_server& other);
    data_server& operator=(const data_server& rhs);

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

public:

    class data_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class arg_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/*
 * https://linux.die.net/man/3/inet_addr
 * https://linux.die.net/man/3/htons
 * struct sockaddr_in {
 *      sa_family_t    sin_family;address family: AF_INET
 *      in_port_t      sin_port;   port in network byte order
 *      struct in_addr sin_addr;   internet address
 *      };
 *
 * Internet address
 * struct in_addr {
 *      uint32_t       s_addr;     address in network byte order
 *      };
 *
 * https://man7.org/linux/man-pages/man2/socket.2.html
 * tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
 * udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
 * raw_socket = socket(AF_INET, SOCK_RAW, protocol);
*/

public:
    const vector<string>& getServerName(void) const throw(); //returns server name @ id
    void setServerName(const vector<string>& serverName) throw(); //sets server name @ id to serverName

    const int& getIdServer() const throw(); //number of server first server = 0 and last = (nbr server-1)
    void setIdServer(int id) throw(); //use with caution I guess

    const vector<std::pair<string, int> >& getHostPort(void) const throw(); //return ip address @ id
    void setHostPort(const vector<std::pair<string, int> >& hostPair) throw(); //sets ip address @ id with ipAddress 

    const int& getType() const throw(); //set type SOCK_STREAM, SOCK_DGRAM, SOCK_SEQPACKET, SOCK_RAW, SOCK_RDM, SOCK_PACKET * for service tcp => SOCK_STREAM
    void setType(int type) throw();

    const vector<Route>& getRoutes(void) const throw(); //returns vector of Route
    void setRoutes(const vector<Route>& routes) throw();

    const int& getProtocol() const throw();
    /*set protocol to 0*/
    void setProtocol(int protocol) throw();

    const string& getRoot(void) const throw();
    void setRoot(const string& root);

    void setMaxBodySize(int maxBodySize) throw();
    int getMaxBodySize(void) const throw();

    void setBodySizeStatus(bool status) throw();
    bool getBodySizeStatus(void) const throw();

    // int&  getBacklog();
    // /*set time to follow socket fd set at 10 for now*/
    // void setBacklog(int );=

    const int& getServerFd(void) const throw();
    /*value of socket */
    void setServerFd(int fd) throw();

    // int& getNewSocket();
    // /*set value of new socket after accpet*/
    // void setNewSocket(int );

    sockaddr_in& getAddress();
    /*set struct sockaddr_in */
    void setAddress(int domain, const std::string& ip_address, int port);
    void setAddress(int dom, int por);
    void setAddress();

    size_t& getAddrlen();
    /*store size of struct sockaddr_in*/
    void setAddrlen(const std::size_t &);

    // int& getLevel();
    // /*set level for soc option to SOL_SOCKET and  we will see */
    // void setLevel(int);

    // int& getOptionName();
    // /*set option_name for soc option to SO_REUSEADDR on mac and  SO_REUSEADDR|SO_REUSEPORT on linux */
    // void setOptionName(int);

    // int& getOptionVal();
    // /*set option_Value for soc option to 0 or 1 */
    // void setOptionVal(int);

    // pid_t& getPid();
    // /*store pid of process*/
    // void setPid(pid_t &);

    void close_server_fd();

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/

private:
/*check if file descriptor is open
 * if process fail throw server::socket_exception();
 */
    int fd_isopen();

/*check if socket  is open
 * if process fail throw server::socket_exception();
 */
    int socket_isopen();
};


#endif //WEBSERV_DATA_SERVER_HPP
