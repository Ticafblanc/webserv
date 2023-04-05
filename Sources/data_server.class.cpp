/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_server.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/data_server.class.hpp"


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

data_server::data_server() : i_data(11), s_data(2), pid(), addr_len(), address(){}

data_server::~data_server() {
//    if(!fd_isopen() || !socket_isopen())
//        throw data_server::data_exception();
//    close(getServerFd());
}

data_server::data_server(const data_server& other) : i_data(other.i_data), s_data(other.s_data),
                                                    pid(other.pid), address(){
    this->addr_len = other.addr_len;
    this->address.sin_family = other.address.sin_family;
    this->address.sin_addr.s_addr = other.address.sin_addr.s_addr;
    this->address.sin_port = other.address.sin_port;
    memcpy(getAddress().sin_zero, other.address.sin_zero, sizeof address.sin_zero);
}

data_server& data_server::operator=(const data_server& rhs){
    this->i_data = rhs.i_data;
    this->s_data = rhs.s_data;
    this->pid = rhs.pid;
    this->addr_len = rhs.addr_len;
    this->address.sin_family = rhs.address.sin_family;
    this->address.sin_addr.s_addr = rhs.address.sin_addr.s_addr;
    this->address.sin_port = rhs.address.sin_port;
    memcpy(this->address.sin_zero, rhs.address.sin_zero, sizeof address.sin_zero);
    return *this;
}

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

const char *  data_server::data_exception::what() const throw(){
    return ("fd error");
}

const char *  data_server::arg_exception::what() const throw(){
    return ("argument invalid");
}

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

std::vector<int>& data_server::getIData(){
    return this->i_data;
}

std::vector<std::string>& data_server::getSData() {
    return this->s_data;
}

std::string& data_server::getServerName(){
    return getSData()[server_name];
}

void data_server::setServer_name(std::string & name){
    getSData()[server_name] = name;
}

std::string& data_server::getIpAddress(){
    return getSData()[ip_address];
}

void data_server::setIp_address(std::string & ip){
    getSData()[ip_address] = ip;
}

int& data_server::getIdServer() {
    return getIData()[id_server];
}
void data_server::setIdServer(int  id){
    getIData()[id_server] = id;
}

int& data_server::getPort(){
    return getIData()[port];

}
void data_server::setPort(int p){
    getIData()[port] = p;
}

int& data_server::getDomain(){
    return getIData()[domain];
}

void data_server::setDomain(int dom){
    getIData()[domain] = dom;
}

int& data_server::getType(){
    return getIData()[type];
}

void data_server::setType(int  typ){
    getIData()[type] = typ;
}

int& data_server::getProtocol(){
    return getIData()[protocol];
}

void data_server::setProtocol(int  pro){
    getIData()[protocol] = pro;
}

int&  data_server::getBacklog(){
    return getIData()[backlog];
}

void data_server::setBacklog(int  log){
    getIData()[backlog] = log;
}

int& data_server::getServerFd() {
    return getIData()[server_fd];
}

void data_server::setServerFd(int  fd){
    getIData()[server_fd] = fd;
}

int& data_server::getNewSocket(){
    return getIData()[new_socket];
}

void data_server::setNewSocket(int  sok){
    getIData()[new_socket] = sok;
}

sockaddr_in& data_server::getAddress(){
    return this->address;
}

void data_server::setAddress(int dom, const std::string& ip_addr, int por){
    if (dom != AF_INET)
        throw data_server::arg_exception();
    getAddress().sin_family = dom;
    getAddress().sin_addr.s_addr = inet_addr(ip_addr.c_str());//check format ip address during the parsing no ERROR
    getAddress().sin_port = htons(por);//no error
    memset(getAddress().sin_zero, '\0', sizeof getAddress().sin_zero);//a delete
    setAddrlen(sizeof(getAddress()));
}

void data_server::setAddress(int dom, int por){
    if (dom != AF_INET)
        throw data_server::arg_exception();
    getAddress().sin_family = dom;
    getAddress().sin_addr.s_addr = INADDR_ANY;//check format ip address during the parsing no ERROR
    getAddress().sin_port = htons(por);//no error
    memset(getAddress().sin_zero, '\0', sizeof getAddress().sin_zero);//a delete
    getAddrlen() = sizeof(getAddress());
}

void data_server::setAddress(){
    getAddress().sin_family = getDomain();
    getAddress().sin_addr.s_addr = inet_addr(getIpAddress().c_str());//check format ip address during the parsing no ERROR
    getAddress().sin_port = htons(getIData()[port]);//no error
    memset(getAddress().sin_zero, '\0', sizeof getAddress().sin_zero);//a delete
    setAddrlen(sizeof(getAddress()));
}

std::size_t& data_server::getAddrlen() {
    return this->addr_len;
}

void data_server::setAddrlen(const std::size_t & s){
    this->addr_len = s;
}

int& data_server::getLevel(){
    return getIData()[level];
}

void data_server::setLevel(int lev){
    getIData()[level] = lev;
}

int& data_server::getOptionName(){
    return getIData()[optionname];
}

void data_server::setOptionName(int opt){
    getIData()[optionname] = opt;
}

int& data_server::getOptionVal(){
    return getIData()[optionval];
}

void data_server::setOptionVal(int opt){
    std::cout << "set opt: " << opt << std::endl;
    getIData()[optionval] = opt;
}

pid_t& data_server::getPid() {
    return this->pid;
}

void data_server::setPid(pid_t & p){
    this->pid = p;
}

void data_server::close_server_fd(){
//    if(!fd_isopen() || !socket_isopen())
//        throw data_server::data_exception();
//    close(getServerFd());
}
/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/

int data_server::fd_isopen() {
    int ret = fcntl(getServerFd(), F_GETFL);
    if (ret == -1) {
        throw data_server::data_exception();
    }
    return 1;
}

int data_server::socket_isopen() {
    int error;
    socklen_t len = sizeof(error);
    int ret = getsockopt(getServerFd(), SOL_SOCKET, SO_ERROR, &error, &len);
    if (ret != 0 || error > 0) {
        throw data_server::data_exception();
    }
    return 1;
}
