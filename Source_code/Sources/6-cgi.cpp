//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/6-cgi.hpp"

CGI::CGI() : _headers(), _pid(), _time() {}

CGI::CGI(Headers &headers) : _headers(&headers), _pid(), _time() {}

CGI::~CGI() {}

static void delVecPC(vecCharP& vP){
  for (vecCharPIt it = vP.begin(); it != vP.end(); ++it)
    delete *it;
}

void CGI::launchChild() {
  _pid = fork();
  if (_pid == -1)
    throw Exception("error launch child", _headers->getClient()->getSd(),
                    "500");
  if (_pid == 0) {
    dup2(_headers->getClient()->getSds()[STDOUT_FILENO], STDIN_FILENO);
    dup2(_headers->getClient()->getSds()[STDOUT_FILENO], STDOUT_FILENO);
    dup2(_headers->getClient()->getSds()[STDOUT_FILENO], STDERR_FILENO);
    close(_headers->getClient()->getSds()[STDIN_FILENO]);
    close(_headers->getClient()->getSds()[STDOUT_FILENO]);
    vector<char*> arg = _headers->getCgiArg();
    vector<char*> env = _headers->getCgiEnv();
    execve(arg[0], arg.data(),env.data());
    delVecPC(arg);
    delVecPC(env);
    exit(EXIT_FAILURE);
  }
}

void  CGI::manager() {
  cout << "cgi manager" << endl;

}
//    write(fd[1], _request.getContent().c_str(),
//    _request.getContent().length());
// close(fd[1]);
// waitpid(-1, NULL, 0);
//_freeArgs(args);
//_freeArgs(exec_args);
//  }
//  Log("End CGI");
//  //  return (readFile("/tmp/webserv_cgi"));
//  return "";
//}

