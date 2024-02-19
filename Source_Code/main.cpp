

#include "4-Utils/Includes/Utils.hpp"
#include "0-Cli/Includes/Cli.class.hpp"


int main(int argc, char **argv) {
  Cli cli(argc, argv);
  if (!cli.isStop()) {
    cout << "Welcome to Webserv !!" << endl;
    kill(cli.getPid(), LAUNCH);
  }
  while (!cli.isStop()) {
    pause();
    cout << "Received signal" << endl;
  }
  return cli.getStatus();
}



// static void launcher(Config & config) {
//     Epoll epoll(config);
//     epoll.launchEpoll();
//     while(true) {
//         try {
//             epoll.EpollWait();
//         }catch (std::exception & e){
//             config._accessLog.setIndent("");
//             config._accessLog.setLogEnable(true);
//             std::ostringstream oss;
//             oss << "last event >> " << config._accessLog;
//             config._errorLog.writeMessageLogFile(oss.str());
//             config._errorLog.writeMessageLogFile(e.what());
//         }
//     }
// }


