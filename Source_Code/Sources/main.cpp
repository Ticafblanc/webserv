

#include "../Includes/main.hpp"
#include "../Includes/server.hpp"
// #include "../includes/RequestInterpretor.hpp"
// #include "../includes/HeadersBlock.hpp"

char **g_envp;

/* Variable on global to remove still reachable */
Server server;
SocketManager<Socket *> sm;
Configuration test;



int main(int argc, char **argv, char **env) {
  Log("Start Server(s)...");
  string path;

  g_envp = env;
  if (argc > 2) {
    printError("Please use : ./WebServ <path>");
    return (1);
  }
  path = argc == 2 ? argv[1] : "../conf/webserv.conf";
  try {
    test = Configuration(path);
#if DEBUG_ACTIVE == 1
    test.print();
#endif
    for (int i = 0; i < (int)test.getServers().size(); i++) {
      Socket *exist = NULL;
      for (size_t j = 0; j < sm.getSockets().size(); j++)
        if (sm.getSockets()[j]->getServerConfiguration().port ==
            test.getServers()[i].port)
          exist = sm.getSockets()[j];
      if (exist == NULL)
        sm.registerSocket(new Socket(test.getServers()[i]));
      else
        sm.registerSocket(
            new Socket(exist->getSocketDescriptor(), test.getServers()[i]));
      Log("Server created on port " + itoa(test.getServers()[i].port) + " : " +
          itoa(sm.getSockets()[i]->getSocketDescriptor()));
    }
    server = Server(sm);
    sm.getSockets().clear();
    signal(SIGINT, endServer);
    server.loop();
  } catch (const std::exception &e) {
    throwError(e);
  }
  return (0);
}
