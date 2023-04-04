#include "../Include/unit_test.hpp"
#include "../../Include/webserv.hpp"
#include <arpa/inet.h>
#include <exception>
#include <sys/_endian.h>
#include <sys/socket.h>

std::vector<data_server> constructor() {
    std::vector<server> vec(4);
    std::vector<data_server> data(4);
    std::vector<data_server>::iterator It = data.begin();
    std::string ip = "127.0.0.1";
    int port = 8081;
    for (int i = 0; It != data.end(); ++It, ++i, ++port) {
        It->setIdServer(i);
        It->setIp_address(ip);
        It->setPort(port);
        It->setDomain(AF_INET);
        It->setType(SOCK_STREAM);
        It->setProtocol(0);
        It->setBacklog(10);
        It->setAddress();
        It->setLevel(SOL_SOCKET);
        It->setOptionName(SO_REUSEADDR);
        It->setOptionVal(1);
//            std::cout << i << std::endl;
    }
    std::vector<server>::iterator Vt = vec.begin();
    It = data.begin();
    for (; Vt != vec.end(); ++Vt, ++It) {
        Vt->setDataServer(*It);
    }
    Vt = vec.begin();
    for (; Vt != vec.end(); ++Vt){
        Vt->launcher();
    }
    return data;
}

int unitTestConstructor()
{
    std::vector<data_server> data;
    try {
        data = constructor();
    } catch (std::exception & e) {
        return -1;
    }
    std::vector<data_server>::iterator it = data.begin();
    std::string ip = "127.0.0.1";
    int port = 8081;
    for (int i = 0; it != data.end(); i++, it++, port++)
    {
        if (it->getIdServer() != i)
            return -1;
        if (it->getIpAddress() != "127.0.0.1")
            return -1;
        if (it->getPort() != port)
            return -1;
        if (it->getDomain() != AF_INET)
            return -1;
        if (it->getType() != SOCK_STREAM)
            return -1;
        if (it->getProtocol() != 0)
            return -1;
        if (it->getBacklog() != 10)
            return -1;
        if (it->getAddress().sin_family != it->getDomain())
            return -1;
        if (it->getAddress().sin_addr.s_addr != inet_addr(it->getIpAddress().c_str()))
            return -1;
        if (it->getAddress().sin_port != htons(port))
            return -1;
        if (it->getLevel() != SOL_SOCKET)
            return -1;
        if (it->getOptionName() != SO_REUSEADDR)
            return -1;
        if (it->getOptionVal() != 1)
        {
            std::cout << "Option value error\n" << std::endl;
            return -1;
        }
    }
    
    return 0;
}
