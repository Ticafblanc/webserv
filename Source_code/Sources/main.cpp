

#include "../Includes/select.hpp"
// #include "../includes/RequestInterpretor.hpp"

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
    Configuration config;
    SocketManager<Socket> serverManager;
    SocketManager<Client> clientManager;
    Select select(serverManager, clientManager);
    try {
      config.parseConfig(ret.second);
      serverManager.setServerSocket(config.getServers());
      select.loop();
    } catch (const std::exception &e) {
      throwError(e);
    }
    return EXIT_SUCCESS;
  }
  cout << "end" << endl;
  return EXIT_FAILURE;
}
