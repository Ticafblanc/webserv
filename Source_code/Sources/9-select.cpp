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
      _clientManager(copy._clientManager), _headers(copy._headers),
      _request(copy._request), _response(copy._response), _cgi(copy._cgi) {
  _this = this;
}

Select::~Select() {}

Select &Select::operator=(const Select &rhs) {
  if (this != &rhs) {
    _this = this;
    _run = rhs._run;
    _serverManager = rhs._serverManager;
    _clientManager = rhs._clientManager;
    _headers = rhs._headers;
    _request = rhs._request;
    _response = rhs._response;
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
  Client clt(_serverManager.getSocketBySD(sd), client, newSd);
  _clientManager.registerSocket(clt);
  //  _headers[newSd] = Headers(_clientManager.getClientBySD(newSd));
  //  _cgi[newSd] = CGI(_headers[newSd]);
  //  _request[newSd] = Request(_headers[newSd]);
  //  _response[newSd] = Response(_request[newSd]);
  FD_SET(newSd, &fdSets[READ_SDS]);
  FD_SET(newSd, &fdSets[WRITE_SDS]);
  sds.insert(newSd);
  cout << "accepte conextion " << newSd << endl;
}

void Select::closeConnection(const int &sd, set<int> &sds, fd_set *fdSets) {
  FD_CLR(sd, &fdSets[READ_SDS]);
  FD_CLR(sd, &fdSets[WRITE_SDS]);
  if (_serverManager.closeSocket(sd) || _clientManager.closeSocket(sd))
    sds.erase(sd);
  cout << "close conextion " << sd << endl;
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
}

ssize_t Select::sendBuffer(Client &clt) {
  ssize_t rc = -1;
  string response = _request[clt.getSd()].getResponse();
  if (!response.empty()) {
    rc = send(clt.getSd(), response.c_str(), response.size(), 0);
    if (rc > 0) {
      if ((size_t)rc >= response.size())
        return rc;
      //        _request[clt.getSd()].clear();
      else
        _request[clt.getSd()].getResponse() = response.substr(rc);
    }
  }
  return rc;
}

void Select::sendMessage(Client &clt, set<int> &sds, fd_set *fdSets) {
  ssize_t ret = sendBuffer(clt);
  if (ret == 0) {
    closeConnection(clt.getSd(), sds, fdSets);
  } else if (ret < 0)
    throwError(throwMessageErrno("send error"));
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

void Select::recvMessage(Client &clt, set<int> &sds, fd_set *fdSets) {
  ssize_t ret = recvBuffer(clt);
  if (ret > 0) {
    if (recvHeader(clt))
          _headers[clt.getSd()].parse();
    //    if (_headers[clt.getSd()].isGood())
    //      _request[clt.getSd()].checkIfComplet();
  } else if (ret == 0 /*|| _headers[clt.getSd()].isCloseConnection()*/) {
    closeConnection(clt.getSd(), sds, fdSets);
  } else
    throwError(throwMessageErrno("Recv error"));
}

void Select::checkClient(fd_set *fdSets, int *intVal, set<int> &sds) {
  while (*intVal > 0) {
    for (SocketManager<Client>::mapSockIt it =
             _clientManager.getSockets().begin();
         it != _clientManager.getSockets().end(); ++it) {
      try {
        if (FD_ISSET(it->first, &fdSets[TMP_READ_SDS]) && (*intVal)-- &&
            !it->second.isEndRecv()) {
          recvMessage(it->second, sds, fdSets);
          break;
        } else if (FD_ISSET(it->first, &fdSets[TMP_WRITE_SDS]) && (*intVal)-- &&
                   it->second.isEndRecv()) {
          sendMessage(it->second, sds, fdSets);
          break;
        }
      } catch (const std::exception &e) {
        throwError(e);
      }
    }
    (*intVal)--;
  }
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
      checkServer(fdSets, &intVal[RETURN_VALUE], sds);
      checkClient(fdSets, &intVal[RETURN_VALUE], sds);
    } else if (intVal[RETURN_VALUE] < 0 &&
               !countErrorIsValid(intVal[COUNT_ERROR]) && usleep(1000))
      throwError(throwMessageErrno("Select error"));
  }
}
