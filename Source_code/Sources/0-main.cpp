

#include "../Includes/9-select.hpp"

char **envp;

static string checkArg(int argc, char **argv, char **env) {
  if (argc > 2)
    throw ErrnoException("Please use : ./WebServ <path>");
  envp = env;
  string path = argc == 2 ? argv[1] : "www/default.com/conf/default.conf";
  return path;
}

int main(int argc, char **argv, char **env) {
//  Start:
  Configuration config;
  SocketManager<Socket> serverManager;
  SocketManager<Client> clientManager;
  Select select(serverManager, clientManager);
  try {
    string path = checkArg(argc, argv, env);
    config.parseConfig(path);
    serverManager.setServerSocket(config.getServers());
//          cout << " ready to loop" <<endl;
    select.loop();
  } catch (exception &e) {
    if (ErrnoException * E = dynamic_cast<ErrnoException*>(&e))
      E->print();
    else
      cerr << e.what() << endl;
    if (Exception * Ex = dynamic_cast<Exception *>(&e))
      select.deinit();
//    goto Start;
    exit(EXIT_FAILURE);
  }
//  end:
  cout << "end" << endl;
  exit(EXIT_SUCCESS);
}
