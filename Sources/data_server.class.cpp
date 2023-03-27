//
// Created by Matthis DoQuocBao on 2023-03-27.
//

#include "../Include/data_server.class.hpp"


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

data_server::data_server() : i_data(), s_data(), pid(), addr_len(), address(){}

data_server::data_server(const data_server& other){
    memccpy(this->i_data, other.i_data, sizeof i_data);
    memccpy(this->s_data, other.s_data, sizeof s_data);
    this->pid = other.pid;
    this->addr_len = other.addr_len;
    this->address.sin_family = other.address.sin_family;
    this->address.sin_addr.s_addr = other.address.sin_addr.s_addr;
    this->address.sin_port = other.address.sin_port);
    memccpy(this->address.sin_zero, other.address.sin_zero, sizeof address.sin_zero);
}

data_server& data_server::operator=(const data_server& rhs){
    memccpy(this->i_data, rhs.i_data, sizeof i_data);
    memccpy(this->s_data, rhs.s_data, sizeof s_data);
    this->pid = rhs.pid;
    this->addr_len = rhs.addr_len;
    this->address.sin_family = rhs.address.sin_family;
    this->address.sin_addr.s_addr = rhs.address.sin_addr.s_addr;
    this->address.sin_port = rhs.address.sin_port);
    memccpy(this->address.sin_zero, rhs.address.sin_zero, sizeof address.sin_zero);
    return this*;
}

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

const char *  data_server::arg_exception::what() const throw(){
    return ("argument invalid");
}

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

int[8]& data_server::getIData() const{
    return this->i_data;
}

std::string[2]& data_server::getSData(){
    return this->s_data;
}

std::string& data_server::getServerName() const{
    return this->s_data[server_name];
}

void data_server::setServer_name(std::string & name){
    this->s_data[server_name] = name;
}

std::string& data_server::getIpAddress() const{
    return this->s_data[ip_adresse];
}

void data_server::setIp_address(std::string & ip){
    this->s_data[ip_adresse] = ip;
}

int& data_server::getIdServer() const{
    return this->i_data[id_server];
}
void data_server::setIdServer(int & id){
    this->i_data[id_server] = id;
}

int& data_server::getPort() const{
    return this->i_data[port];

}
void data_server::setPort(int & p){
    this->i_data[port] = p;
}

int& data_server::getDomain() const{
    return this->i_data[domain];
}

void data_server::setDomain(int & dom){
    this->i_data[domain] = dom;
}

int& data_server::getType() const{
    return this->i_data[type];
}

void data_server::setType(int & type){
    this->i_data[type] = type;
}

int& data_server::getProtocol() const{
    return this->i_data[protocol];
}

void data_server::setProtocol(int & pro){
    this->i_data[protocol] = pro;
}

int&  data_server::getBacklog() const{
    return this->i_data[backlog];
}

void data_server::setBacklog(int & log){
    this->i_data[backlog] = log
}


int& data_server::getServerFd() const{
    return this->i_data[server_fd];
}

void data_server::setServerFd(int & fd){
    this->i_data[server_fd] = fd;
}

int& data_server::getNewSocket() const{
    return i_data[new_socket];
}

void data_server::setNewSocket(int & sok){
    this->i_data[new_socket] = sok;
}

sockaddr_in& data_server::getAddress() const{
    return this->address;
}

void data_server::set_address(int domain, int ip_address, int port){
    if (domain != AF_INET)
        throw server::arg_exception();
    this->address.sin_family = domain;
    this->address.sin_addr.s_addr = inet_addr(ip_address);//check format ip address during the parsing no ERROR
    this->address.sin_port = htons(port);//no error
    memset(address.sin_zero, '\0', sizeof address.sin_zero);//a delete
    this->addr_len = sizeof(this->address);
}

void data_server::set_address(){
    this->address.sin_family = this->domain;
    this->address.sin_addr.s_addr = inet_addr(this->s_data[ip_address].c_str());//check format ip address during the parsing no ERROR
    this->address.sin_port = htons(this->i_data[port]);//no error
    memset(address.sin_zero, '\0', sizeof address.sin_zero);//a delete
    this->addr_len = sizeof(this->address);
}

size_t& data_server::getAddrlen() const{
    return this->addr_len;
}

void data_server::setSddrlen(std::size_t & s){
    this->addr_len = s;
}

pid_t data_server::getPid() const{
    return this->pid;
}

void data_server::setPid(pid_t & p){
    this->pid = p;
}

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/

int data_server::fd_isopen() {
    int ret = fcntl(fd, F_GETFL);
    if (ret == -1) {
        throw server::socket_exception();
    }
    return 1;
}

int data_server::socket_isopen() {
    int error = 0;
    socklen_t len = sizeof(error);
    int ret = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);
    if (ret != 0) {
        throw server::socket_exception();
    }
    return (error == 0) ?  1 : 0;
}