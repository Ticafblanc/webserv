//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/9-select.hpp"

Select *Select::_this = NULL;

Select::Select(SocketManager<Socket> &sm, SocketManager<Client> &cm)
    : _run(true), _serverManager(sm), _clientManager(cm), _headers(),
      _request(), _response(), _cgi() {
  _this = this;
}

Select::Select(const Select &copy)
    : _run(true), _serverManager(copy._serverManager),
      _clientManager(copy._clientManager), _headers(copy._headers), _request(),
      _response(copy._response), _cgi(copy._cgi) {}

Select::~Select() {}

Select &Select::operator=(const Select &rhs) {
  if (this != &rhs) {
    _this = this;
    _run = rhs._run;
    _serverManager = rhs._serverManager;
    _clientManager = rhs._clientManager;
    _headers = rhs._headers;
    _cgi = rhs._cgi;
  }
  return *this;
}

void Select::acceptConnection(const int &sd, set<int> &sds, fd_set *fdSets) {
  sockaddr_in client = {};
  socklen_t size = sizeof(client);
  int newSd = accept(sd, (sockaddr *)&client, &size);
  if (newSd < 0) {
    if (errno != EWOULDBLOCK)
      throw(throwMessageErrno("accept() failed, " + itoa(errno)));
    return;
  }
  int in[2], out[2];
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, in) == 0 ||
      socketpair(AF_UNIX, SOCK_STREAM, 0, out) == 0)
    throw(
        throwMessageErrno("Creation of the socketpair descriptor of a socket"));
  int io[4];
  io[0] = in[0];
  io[1] = in[1];
  io[2] = out[0];
  io[3] = out[1];
  Client clt(_serverManager.getSocketBySD(sd), client, newSd, io);
  _clientManager.registerSocket(clt);
  _headers[newSd] = Headers(_clientManager.getClientBySD(newSd));
  _cgi[newSd] = CGI(_headers[newSd]);
  _request[newSd] = Request(_headers[newSd], _cgi[newSd]);
  //  _response[newSd] = Response(_request[newSd], _cgi[newSd]);
  FD_SET(newSd, &fdSets[READ_SDS]);
  //  FD_SET(newSd, &fdSets[WRITE_SDS]);
  sds.insert(newSd);
  cout << "accepte conextion " << newSd << " " << io[CGI_CLIENT] << " "
       << io[CGI_SD] << endl;
}

void Select::closeConnection(setInt &toClose, set<int> &sds, fd_set *fdSets) {
  for (setIntIt it = toClose.begin(); it != toClose.end(); ++it) {
    int sd = *it;
    FD_CLR(*it, &fdSets[READ_SDS]);
    FD_CLR(*it, &fdSets[WRITE_SDS]);
    if (_serverManager.closeSocket(*it) || _clientManager.closeSocket(*it))
      sds.erase(*it);
    cout << "close conextion " << sd << endl;
  }
}

void Select::checkServer(fd_set *fdSets, int *intVal, set<int> &sds) {
  for (SocketManager<Socket>::mapSockIt it =
           _serverManager.getSockets().begin();
       it != _serverManager.getSockets().end() && *intVal; ++it) {
    if (FD_ISSET(it->first, &fdSets[TMP_READ_SDS]) && (*intVal)--)
      try {
        acceptConnection(it->first, sds, fdSets);
      } catch (const std::exception &e) {
        throwError(e);
      }
  }
  while (*intVal) {
    try {
      acceptConnection(_serverManager.getSockets().begin()->first, sds, fdSets);
    } catch (const std::exception &e) {
      throwError(e);
    }
    (*intVal)--;
  }
}

ssize_t Select::sendBuffer(Client &clt) {
  ssize_t rc = -1;
  string response = _request[clt.getSd()].getResponse();
  if (!response.empty()) {
    rc = send(clt.getSd(), response.c_str(), response.size(), 0);
    if (rc > 0) {
      if ((size_t)rc >= response.size())
        return rc; // manage return value;
      //        _request[clt.getSd()].clear();
      else
        _request[clt.getSd()].getResponse() = response.substr(rc);
    }
  }
  return rc;
}

bool Select::sendMessage(Client &clt, set<int> &toClose) {
  ssize_t ret = sendBuffer(clt);
  if (ret == 0) {
    toClose.insert(clt.getSd());
  } else if (ret < 0)
    throwError(throwMessageErrno("send error"));
  return false;
}

bool Select::recvHeader(Client &clt) {
  if (clt.getHeader().empty()) {
    size_t pos = clt.getRequest().find("\r\n\r\n");
    if (pos != string::npos) {
      clt.getHeader() = clt.getRequest().substr(0, pos + 2);
      clt.getRequest() = clt.getRequest().substr(pos + 4);
      return true;
    }
  }
  return false;
}

ssize_t Select::recvBuffer(Client &clt) {
  char buffer[BUFFER_SIZE + 1];
  bzero(buffer, BUFFER_SIZE + 1);
  ssize_t rc = recv(clt.getSd(), buffer, BUFFER_SIZE, 0);
  if (rc > 0) {
    clt.getRequest().append(buffer);
  }
  return rc;
}

bool Select::recvMessage(Client &clt, set<int> &toClose) {
  ssize_t ret = recvBuffer(clt);
  if (ret > 0) {
    if (clt.getHeader().empty() && recvHeader(clt))
      _headers[clt.getSd()].parse();
    if (!clt.isEndRecv())
      _request[clt.getSd()].manageRequest();
    return clt.isEndRecv();
  } else if (ret == 0 /*|| _headers[clt.getSd()].isCloseConnection()*/) {
    toClose.insert(clt.getSd());
  } else
    throwError(throwMessageErrno("Recv error"));
  return false;
}

bool Select::isSend(int sd, fd_set &fd, Client &clt, setInt &toClose) {
  if (FD_ISSET(sd, &fd)) {
    if (sendMessage(clt, toClose))
      FD_CLR(sd, &fd);
    return true;
  }
  return false;
}

bool Select::isRecv(int sd, fd_set &fd, Client &clt, setInt &toClose) {
  if (FD_ISSET(sd, &fd)) {
    if (recvMessage(clt, toClose))
      FD_SET(sd, &fd);
    return true;
  }
  return false;
}

void Select::checkClient(fd_set *fdSets, int *intVal, set<int> &sds) {
  set<int> toClose;
  for (SocketManager<Client>::mapSockIt it =
           _clientManager.getSockets().begin();
       (*intVal) && it != _clientManager.getSockets().end(); ++it) {
    try {
      if (isSend(it->first, fdSets[TMP_WRITE_SDS], it->second, toClose))
        (*intVal)--;
      if (isRecv(it->first, fdSets[TMP_READ_SDS], it->second, toClose))
        (*intVal)--;
    } catch (const std::exception &e) {
      throwError(e);
    }
  }
  closeConnection(toClose, sds, fdSets);
}

void Select::checkCgi(fd_set *fdSets, int *intVal, set<int> &sds) {
  set<int> toClose;
  for (SocketManager<Client>::mapSockIt it =
           _clientManager.getSockets().begin();
       (*intVal) && it != _clientManager.getSockets().end(); ++it) {
    try {
      if (FD_ISSET(it->second.getSdIn()[CGI_SD], &fdSets[TMP_READ_SDS]) &&
          (*intVal)-- && !it->second.isEndRecv()) {
        recvMessage(it->second, toClose);
      }
      if (FD_ISSET(it->second.getSdOut()[CGI_CLIENT], &fdSets[TMP_WRITE_SDS]) &&
          (*intVal)-- && it->second.isEndRecv()) {
        sendMessage(it->second, toClose);
      }
      if (FD_ISSET(it->second.getSdIn()[CGI_SD], &fdSets[TMP_READ_SDS]) &&
          (*intVal)-- && !it->second.isEndRecv()) {
        recvMessage(it->second, toClose);
      }
      if (FD_ISSET(it->second.getSdOut()[CGI_CLIENT], &fdSets[TMP_WRITE_SDS]) &&
          (*intVal)-- && it->second.isEndRecv()) {
        sendMessage(it->second, toClose);
      }
    } catch (const std::exception &e) {
      throwError(e);
    }
  }
  closeConnection(toClose, sds, fdSets);
}

static void resetCountError(int &countError) { countError = 3; }
static bool countErrorIsValid(int &countError) { return countError-- > 0; }

static void udateData(fd_set *fdSets) {
  fdSets[TMP_READ_SDS] = fdSets[READ_SDS];
  fdSets[TMP_WRITE_SDS] = fdSets[WRITE_SDS];
}

static void initSelect(fd_set *fdSets, set<int> &sds,
                       SocketManager<Socket>::mapSock &sockets) {
  FD_ZERO(&fdSets[READ_SDS]);
  FD_ZERO(&fdSets[WRITE_SDS]);
  FD_ZERO(&fdSets[TMP_READ_SDS]);
  FD_ZERO(&fdSets[TMP_WRITE_SDS]);
  for (SocketManager<Socket>::mapSockIt it = sockets.begin();
       it != sockets.end(); ++it) {
    FD_SET(it->first, &fdSets[READ_SDS]);
    sds.insert(it->first);
  }
}

void Select::endServer(int signal) {
  (void)signal;
  _this->_run = false;
  cout << "goodbay" << endl;
}

void Select::loop() {
  signal(SIGINT, endServer);
  int intVal[2];
  set<int> sds;
  fd_set fdSets[4];
  initSelect(fdSets, sds, _serverManager.getSockets());
  resetCountError(intVal[COUNT_ERROR]);
  while (_run) {
    udateData(fdSets);
    intVal[RETURN_VALUE] = select(*sds.rbegin() + 1, &fdSets[TMP_READ_SDS],
                                  &fdSets[TMP_WRITE_SDS], NULL, NULL);
    if (intVal[RETURN_VALUE] >= 0) {
      resetCountError(intVal[COUNT_ERROR]);
      //      checkCgi(fdSets, &intVal[RETURN_VALUE], sds);
      checkClient(fdSets, &intVal[RETURN_VALUE], sds);
      checkServer(fdSets, &intVal[RETURN_VALUE], sds);
    } else if (intVal[RETURN_VALUE] < 0 &&
               !countErrorIsValid(intVal[COUNT_ERROR]) && usleep(1000))
      throwError(throwMessageErrno("Select error"));
  }
}
