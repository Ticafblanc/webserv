#include "../Include/unit_test.hpp"

int construcor() {
    try {
        std::vector<server> vec(4);
        std::vector<data_server> data(4);
        std::vector<data_server>::iterator It = data.begin();
        std::string ip = "127.0.0.1";
        int port = 8081;
        for (int i = 0; It != data.end(); ++It, ++i, ++port) {
            It->setAddress();
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
    }
    catch (std::exception & e){
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}