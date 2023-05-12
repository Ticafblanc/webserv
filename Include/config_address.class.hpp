////
//// Created by Matthis Doquocbao on 5/10/23.
////
//
//#ifndef WEBSERVER_CONFIG_ADDRESS_CLASS_HPP
//#define WEBSERVER_CONFIG_ADDRESS_CLASS_HPP
//
//
//class config_address {
///*>********************************public section**********************************/
//
//public:
//
///*
//*====================================================================================
//*|                                  Member Fonction                                 |
//*====================================================================================
//*/
//
///**
// * Constructor of config_address.class class
// *
// * config_address.class();
// *
// * @param   void
// * @throw   none
// **/
//    config_address(const std::string ip_address, const int port);
//
///**
//* Destructor of config_address.class class
//*
//* config_address.class.class();
//*
//* @throw   none
//**/
//    ~config_address();
//
///**
//* Constructor of config_address.class class
//*
//* config_address.class(const config_address.class& other);
//*
//* @param   void
//* @throw   none
//**/
//    config_address(const config_address& other);
//
///**
// * Constructor of config_address.class class
// *
// * config_address.class& operator=(const config_address.class& rhs);
// *
// * @returns     config_address.class&
// * @param       const config_address.class&
// * @throw       none
// */
//    config_address& operator=(const config_address& rhs);
//
///*
//*====================================================================================
//*|                                  Element access                                 |
//*====================================================================================
//*/
//
///**
// * Public methode of config_address.class class
// *
// * std::string& get_ip_address(int position);
// *
// * @returns     string& contain ip address of server
// * @param       position int is a position of variable in vector<std::string> table,
// *              represente the one of ip address of server
// * @throw       config_address_exception out of range
// */
//
//    std::string &get_ip_address(int);
//
///**
// * Public methode of config_address.class class
// *
// * std::string& get_sock_address(int position);
// *
// * @returns     struct sockaddr& contain struct sockaddr of server
// * @param       position int is a position of variable in vector<struct sockaddr> table,
// *              represente the one of struct sockaddr of server
// * @throw       data_exception out of rang
// */
//    struct sockaddr &get_sock_address();
//
//
///**
// * Protected methode of config_webserv class
// *
// * std::string& get_ip_address(int sever_number, int position);
// *
// * @returns     string& contain name of server
// * @param       sever_number is an int, he is the server number in std::vector<vector<std::string> >
// *              to acces liste of ip address for each server
// *
// *              position int is a position of variable in vector<std::string> table,
// *              represente the one of ip address of server
// * @throw       config_exception out of range
// */
//    std::string& get_ip_address(int, int);
//
///**
// * Protected methode of config_webserv class
// *
// * void set_ip_address(int server_number, std::string & ip_address);
// *
// * @returns     void
// * @param       sever_number is an int, he is the server number in std::vector<vector<std::string> >
// *              to acces liste of name for each server
// *
// *              ip_address is an std::string contain ip address of server to add
// * @throw       config_exception if ip already exist
// */
//    void add_ip_address(int, std::string &);
//
///**
// * Protected methode of config_webserv class
// *
// * int& get_Port(int sever_number, int position);
// *
// * @returns     int& contain the port to follow
// * @param       sever_number is an int, he is the server number in std::vector<vector<int> >
// *              to acces liste of ip address for each server
// *
// *              position int is a position of variable in vector<int> table,
// *              represente the one of port of server
// * @throw       config_exception out of range
// */
//    int& get_Port(int, int);
//
///**
// * Protected methode of config_webserv class
// *
// * void add_Port(int server_number, int port);
// *
// * @returns     void
// * @param       sever_number is an int, he is the server number in std::vector<vector<std::string> >
// *              to acces liste of name for each server
// *
// *              port is an int contain port of server to add
// * @throw       config_exception if ip already exist
// */
//    void add_Port(int, int);
//
//    int& getProtocol();
//    /*set protocol to 0*/
//    void setProtocol(int );
//
//    int&  getBacklog();
//    /*set time to follow socket fd set at 10 for now*/
//    void setBacklog(int );
//
//    int& getServerFd();
//    /*value of socket */
//    void setServerFd(int );
//
//    int& getNewSocket();
//    /*set value of new socket after accpet*/
//    void setNewSocket(int );
//
//    sockaddr_in& getAddress();
//    /*set struct sockaddr_in */
//    void setAddress(int domain, const std::string& ip_address, int port);
//    void setAddress(int dom, int por);
//    void setAddress();
//
//    size_t& getAddrlen() ;
//    /*store size of struct sockaddr_in*/
//    void setAddrlen(const std::size_t &);
///*>*******************************private section**********************************/
//
//private:
//
///*
//*====================================================================================
//*|                                     Member                                       |
//*====================================================================================
//*/
//    const std::string       _ip_address;
//    const int               _port;
//    const int               _protocol;
//    const struct sockaddr   _sock_address;
//    int                     _server_socket;
//    struct epoll_event      _event;
//
//};
//
//
//#endif //WEBSERVER_CONFIG_ADDRESS_CLASS_HPP
