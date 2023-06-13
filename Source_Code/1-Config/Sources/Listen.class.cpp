//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include <Source_Code/1-Config/Includes/Listen.class.hpp>

Listen::Listen(Config& config, ConfigServer& configServer)
: _config(config), _configServer(configServer){}

Listen::~Listen() {}
//todo manage close fd at end of programme
/*check if file descriptor is open
 * if process fail throw serverSocket::socket_exception();
 */
//    int fd_isopen();

/*check if AbaseSocket  is open
 * if process fail throw serverSocket::socket_exception();
 */
//    int socket_isopen();

Listen::Listen(const Listen& other)
        : _config(other._config), _configServer(other._configServer) {}

Listen &Listen::operator=(const Listen & rhs) {
    this->_config = rhs._config;
    return *this;
}

std::string Listen::parseListenData() {
    //@todo check port and ip
    return std::string("");
}

std::string Listen::parseListenData(std::string in) {
    std::stringstream input(in);
    std::string ip;
    std::string portStr;
    int         portInt;
    std::getline(input >> std::ws, ip, ':');
    input >> portStr >> std::ws;
    portInt = std::atoi(portStr.c_str());
    _configServer.listen[ip] = portInt;
    return std::string();
}

static bool check_ip_limit(unsigned int val, unsigned int min, unsigned int max, std::string &error)
{
    if (val >= min && val <= max)
        return true;
    error = "Bad ip segment: check ip limit";
    return false;
}

/*
    VALID ADDRESS
    Class A: 10.0.0.0 to 10.255.255.255
    Class B: 172.16.0.0 to 172.31.255.255
    Class C: 192.168.0.0 to 192.168.255.255
    127.0.0.1
    0.0.0.0
*/

static bool check_class_A(std::vector<unsigned int> &ip_vec, std::string &error)
{
    std::vector<unsigned int>::iterator ip_vec_it;
    ip_vec_it = ip_vec.end() - 1;
    if (ip_vec.size() == 1)
        return true;
    return (check_ip_limit(*ip_vec_it, 0, 255, error));
}

static bool check_class_B(std::vector<unsigned int> &ip_vec, std::string &error)
{
    std::vector<unsigned int>::iterator ip_vec_it;
    ip_vec_it = ip_vec.end() - 1;
    switch (ip_vec.size()) {
        case 1:
            return true;
        case 2:
            return (check_ip_limit(*ip_vec_it, 16, 31, error));
        case 3:
            return (check_ip_limit(*ip_vec_it, 0, 255, error));
        case 4:
            return (check_ip_limit(*ip_vec_it, 0, 255, error));
        default:
            error = "Bad ip address: check class B";
            return false;
    }
}

static bool check_class_C(std::vector<unsigned int> &ip_vec, std::string &error)
{
    std::vector<unsigned int>::iterator ip_vec_it;
    ip_vec_it = ip_vec.end() - 1;
    switch (ip_vec.size()) {
        case 1:
            return true;
        case 2:
            return (check_ip_limit(*ip_vec_it, 168, 168, error));
        case 3:
            return (check_ip_limit(*ip_vec_it, 0, 255, error));
        case 4:
            return (check_ip_limit(*ip_vec_it, 0, 255, error));
        default:
            error = "Bad ip address: check class C";
            return false;
    }
}

static bool check_default_address(std::vector<unsigned int> &ip_vec, std::string &error)
{
    std::vector<unsigned int>::iterator ip_vec_beg;
    std::vector<unsigned int>::iterator ip_vec_end;
    ip_vec_beg = ip_vec.begin();
    ip_vec_end = ip_vec.end() - 1;
    if (*ip_vec_beg == 0)
        return (check_ip_limit(*ip_vec_end, 0, 0, error));
    else if (*ip_vec_beg == 127)
    {
        if (ip_vec.size() == 1)
            return true;
        else if (ip_vec.size() == 2 || ip_vec.size() == 3)
            return(check_ip_limit(*ip_vec_end, 0, 0, error));
        else
            return (check_ip_limit(*ip_vec_end, 1, 1, error));
    }
    error = "Bad ip address: default address";
    return false;
}

static bool check_uchar(std::vector<unsigned int> &ip_vec, std::string &error)
{
    if (ip_vec.empty())
        return true;
    std::vector<unsigned int>::iterator ip_vec_it;
    ip_vec_it = ip_vec.begin();
    switch (*ip_vec_it) {
        case 10:
            return (check_class_A(ip_vec, error));
        case 172:
            return (check_class_B(ip_vec, error));
        case 192:
            return (check_class_C(ip_vec, error));
        default:
            return (check_default_address(ip_vec, error));
    }
}

static bool check_ip_format(std::string ip, std::string &error)
{
    int                         dot_count = 0;
    unsigned long               pos = 0;

    while (true)
    {
        pos = ip.find('.', pos + 1);
        if (pos == std::string::npos)
            break;
        dot_count++;
    }
    if (dot_count != 3)
    {
        error = "Bad Ip address: check format";
        return false;
    }
    return true;
}

void    Listen::check_port(std::string port, std::string &error) {
    int port_int;
    if (port.empty())
    {
        error = "The address does not have a port.";
        return;
    }
    port_int = std::atoi(port.c_str());
    if (port_int < 1024 || port_int > 49151)
    {
        error = "Port is out of range.";
        return;
    }
    _port = port_int;
}

std::string Listen::check_ip(std::string ip_address, std::string &error) {
    std::vector<unsigned int> segment_vec;
    std::stringstream ip_ss(ip_address);
    std::string segment;

    if (ip_address == "INADDR_ANY")
    {
        return "0.0.0.0";
    }
    if (!check_ip_format(ip_address, error))
        return;
    else
    {
        while (check_uchar(segment_vec, error) && !ip_ss.eof()) {
            std::getline(ip_ss, segment, '.');
            if (!segment.empty() && segment.size() < 4)
                if (segment.find_first_not_of("1234567890") == std::string::npos)
                    segment_vec.push_back(std::atoi(segment.c_str()));
            if (!error.empty())
                return;
            if (segment_vec.size() > 4)
            {
                error = "Bad Ip address: check ip";
                return;
            }
        }
        return ip_address;
    }
}

std::string Listen::check_input() {
    std::string error;
    std::string ip_address;
    std::string port;

    if (_input.str().find(':') != std::string::npos)
    {
        std::getline(_input, ip_address, ':');
        check_ip(ip_address, error);
        if (!error.empty())
            return error;
    }
    std::getline(_input, port);
    check_port(port, error);
    return error;
}

for ( std::map<std::string, int>::iterator it = server.listen.begin();
it != server.listen.end(); ++it) {
Socket sock(it->first, it->second);
Socket& newSocket = sock;
for(std::map<int, Socket>::iterator sockIt = mapFdServer.begin();
sockIt != mapFdServer.end(); ++sockIt){
if (sockIt->second == newSocket){
newSocket = sockIt->second;
break;
}
}
newSocket.addServerName(server.name, server.token);
try {
newSocket.buildServerSocket();
}catch (std::exception & e){
std::cerr << e.what()<<std::endl;
continue;
}mapFdServer.insert(std::make_pair(newSocket.getSocket(), newSocket));