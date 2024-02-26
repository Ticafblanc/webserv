

#include "../Includes/9-select.hpp"

char **envp;
// void Select::closeServer() {
//   for (size_t client = 0; client < _clientManager.getSockets().size();
//        client++) {
//     close(_clientManager.getSockets()[client].getSd());
//     Log("Client connection closed : " +
//         itoa(_clientManager.getSockets()[client].getSd()));
//     //    delete _clientManager.getSockets()[client];
//   }
//
//   for (size_t server = 0; server < _serverManager.getSockets().size();
//        server++) {
//     close(_serverManager.getSockets()[server].getSd());
//     Log("Select closed : " +
//         itoa(_serverManager.getSockets()[server].getSd()));
//     //    delete _serverManager.getSockets()[server];
//   }
// }
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
    Configuration config;
    SocketManager<Socket> serverManager;
    SocketManager<Client> clientManager;
    Select select(serverManager, clientManager);
    try {
      config.parseConfig(ret.second);
      serverManager.setServerSocket(config.getServers());
//      cout << " ready to loop" <<endl;
      select.loop();
    } catch (const std::exception &e) {
      throwError(e);
    }
    return EXIT_SUCCESS;
  }
  cout << "end" << endl;
  return EXIT_FAILURE;
}
