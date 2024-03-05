//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/6-cgi.hpp"

CGI::CGI() : _headers(), _fd(), _pid(), _time() {}

CGI::CGI(Headers &headers) : _headers(&headers), _fd(), _pid(), _time() {}

CGI::~CGI() {}

CGI::CGI(const CGI &copy)
    : _headers(copy._headers), _fd(), _pid(copy._pid), _time(copy._time) {
  _fd[STDIN_FILENO] = copy._fd[STDIN_FILENO];
  _fd[STDOUT_FILENO] = copy._fd[STDOUT_FILENO];
}

CGI &CGI::operator=(const CGI &rhs) {
  if (this != &rhs) {
    _headers = rhs._headers;
    _fd[STDIN_FILENO] = rhs._fd[STDIN_FILENO];
    _fd[STDOUT_FILENO] = rhs._fd[STDOUT_FILENO];
    _pid = rhs._pid;
    _time = rhs._time;
  }
  return *this;
}

CGIChild::CGIChild() : CGI() {}

CGIChild::CGIChild(Headers &headers) : CGI(headers) {}

CGIChild::~CGIChild() {}

CGIChild::CGIChild(const CGIChild& copy): CGI(copy){}

CGIChild &CGIChild::operator=(const CGIChild& rhs){
  CGI::operator=(rhs);
  return *this;
}

static void delVecPC(vecCharP &vP) {
  for (vecCharPIt it = vP.begin(); it != vP.end(); ++it)
    delete *it;
}

void CGIChild::manager() {
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
    vector<char *> arg = _headers->getCgiArg();
    vector<char *> env = _headers->getCgiEnv();
    execve(arg[0], arg.data(), env.data());
    delVecPC(arg);
    delVecPC(env);
    exit(EXIT_FAILURE);
  }
}

CGIParent::CGIParent() : CGI() {}

CGIParent::CGIParent(Headers &headers) : CGI(headers) {}

CGIParent::~CGIParent() {}

CGIParent::CGIParent(const CGIParent& copy): CGI(copy){}

CGIParent &CGIParent::operator=(const CGIParent& rhs){
  CGI::operator=(rhs);
  return *this;
}

void CGIParent::manager() { cout << "cgi manager" << endl; }
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
