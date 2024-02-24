


#include "../Includes/select.hpp"
// #include "../includes/RequestInterpretor.hpp"
// #include "../includes/HeadersBlock.hpp"

char **envp;

static pairBoolStr checkArg(int argc, char **argv, char **env) {
    if (argc > 2) {
        printError("Please use : ./WebServ <path>");
        return make_pair(false, "");
    }
    envp = env;
    string path = argc == 2 ? argv[1] : "../conf/webserv.conf";
    return make_pair(true, path);
}

int main(int argc, char **argv, char **env) {
    pairBoolStr ret = checkArg(argc, argv, env);
    if (ret.first) {
//    Select select;
//    SocketManager<Socket *> socketManager;
        Configuration config;
        try {
            cout << "coucou" << endl;
            config.parseConfig(ret.second);
            cout << "coucou" << endl;
//      for (int i = 0; i < (int)config.getServers().size(); i++) {
//        Socket *socket = NULL;
//        for (size_t j = 0; j < socketManager.getSockets().size(); j++)
//          if (socketManager.getSockets()[j]->getServerConfiguration().port ==
//              config.getServers()[i].port)
//            socket = socketManager.getSockets()[j];
//        if (socket == NULL)
//          socketManager.registerSocket(new Socket(config.getServers()[i]));
//        else
//          socketManager.registerSocket(
//              new Socket(socket->getSocketDescriptor(), config.getServers()[i]));
//        Log("Select created on port " + itoa(config.getServers()[i].port) +
//            " : " + itoa(socketManager.getSockets()[i]->getSocketDescriptor()));
//      }
//      select = Select(socketManager);
//      socketManager.getSockets().clear();
//      signal(SIGINT, endServer);
//      select.loop();
        } catch (const std::exception &e) {
            throwError(e);
        }
        return EXIT_SUCCESS;
    }
    cout << "end" << endl;
    return EXIT_FAILURE;
}
