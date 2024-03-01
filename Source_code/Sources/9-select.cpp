//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/9-select.hpp"

Select *Select::_this = NULL;

Select::Select(SocketManager<Socket> &sm, SocketManager<Client> &cm)
    : _run(true), _serverManager(sm), _clientManager(cm), _headers(),
      _request(), _response(), _cgi(), _sds(), _fdSets(4) {
  _this = this;
}

Select::Select(const Select &copy)
    : _run(true), _serverManager(copy._serverManager),
      _clientManager(copy._clientManager), _headers(copy._headers),
      _request(copy._request), _response(copy._response), _cgi(copy._cgi),
      _sds(copy._sds), _fdSets(copy._fdSets) {}

Select::~Select() {}

Select &Select::operator=(const Select &rhs) {
  if (this != &rhs) {
    _this = this;
    _run = rhs._run;
    _serverManager = rhs._serverManager;
    _clientManager = rhs._clientManager;
    _headers = rhs._headers;
    _cgi = rhs._cgi;
    _sds = rhs._sds;
    _fdSets = rhs._fdSets;
  }
  return *this;
}

pair<int, sockaddr_in> Select::acceptConnection(const int &sd) {
  sockaddr_in client = {};
  socklen_t size = sizeof(client);
  int newSd = accept(sd, (sockaddr *)&client, &size);
  if (newSd < 0) {
    throw ErrnoException("accept() failed");
  }
  return make_pair(newSd, client);
}

void Select::createSocketPair(Client &clt) {
  int newSd = socketpair(AF_UNIX, SOCK_STREAM, 0, clt.getSds());
  if (newSd < 0) {
    throw Exception("socketpair() failed", clt.getSd(), "500");
  }
  FD_CLR(clt.getSds()[STDIN_FILENO], &_fdSets[READ_SDS]);
//  FD_CLR(clt.getSds()[STDIN_FILENO], &_fdSets[WRITE_SDS]);
}

void Select::closeConnection(const int &sd) {
  FD_CLR(sd, &_fdSets[READ_SDS]);
  FD_CLR(sd, &_fdSets[WRITE_SDS]);
  if (_clientManager.closeSocket(sd) || _serverManager.closeSocket(sd))
    _sds.erase(sd);
  cout << "close connexion " << sd << endl;
}

ssize_t Select::sendBuffer(int &r, Client &clt) {
  ssize_t rc = -1;
  (void)r;
  (void)clt;
  //  string response = _request[clt.getSd()].getResponse(); // switch to
  //  reponse if (!response.empty()) {
  //    rc = send(clt.getSd(), response.c_str(), response.size(), 0);
  //    if (rc > 0) // manage udate value
  //      _request[clt.getSd()].getResponse() = response.substr(rc);
  //  }
  return rc;
}

bool Select::recvHeader(Client &clt) {
  if (clt.getHeader().empty()) {
    size_t pos = clt.getRequest().find("\r\n\r\n");
    if (pos != string::npos) {
      clt.getHeader() = clt.getRequest().substr(0, pos + 2);
      clt.getRequest() = clt.getRequest().substr(pos + 4);
      return true;
    } else
      throw Exception("Headers to long", clt.getSd(), "413");
  }
  return false;
}

ssize_t Select::recvBuffer(int &r, Client &clt) {
  char buffer[BUFFER_SIZE + 1];
  bzero(buffer, BUFFER_SIZE + 1);
  ssize_t rc = recv(r, buffer, BUFFER_SIZE, 0);
  if (rc > 0) {
    clt.getRequest().append(buffer);
  }
  return rc;
}

bool Select::sendMessage(int &r, Client &clt) {
  ssize_t ret = sendBuffer(r, clt);
  if (ret > 0) {
    if (_headers[r].isCloseRequest() /*&& _respons[r].isempt*/)
      closeConnection(r);
  }
  closeConnection(r);
  return false;
}

bool Select::recvMessage(int &r, Client &clt) {
  ssize_t ret = recvBuffer(r, clt);
  if (ret > 0) {
    if (recvHeader(clt)) {
      _headers[r].parse();
      if (clt.getLocation()->isCgi()) {
        createSocketPair(clt);
        _cgi[r].launchChild();
      }
    }
    if (clt.getLocation()->isCgi())
      _cgi[r].manager();
    else
      _request[r].manager();
    return clt.isEndRecv();
  }
    closeConnection(r);
    return false;
}

bool Select::acceptClient(int &r, Socket &srv) {
  pair<int, sockaddr_in> ret = acceptConnection(r);
  Client clt(srv, ret.second, ret.first);
  _clientManager.registerSocket(clt);
  _headers[ret.first] = Headers(_clientManager.getClientBySD(ret.first));
  _cgi[ret.first] = CGI(_headers[ret.first]);
  _request[ret.first] = Request(_headers[ret.first], _cgi[ret.first]);
  //  _response[newSd] = Response(_request[newSd], _cgi[newSd]);
  _sds.insert(ret.first);
  r = ret.first;
  cout << "accepte conextion " << ret.first << " " << endl;
  return true;
}

void Select::check(int ret) {
  if (ret < 0)
    throw ErrnoException("Select error");
  forLoopSock(_clientManager.getSockets(), &ret,TMP_READ_SDS, _sdCltRecv);
  forLoopSock(_clientManager.getSockets(), &ret,TMP_WRITE_SDS, _sdCltSend);
  forLoopSock(_serverManager.getSockets(), &ret,TMP_READ_SDS, _sdServ);
  mapSockClient &clt = _clientManager.getSockets();
  forLoopSd(clt, WRITE_SDS, _sdCltRecv, &Select::recvMessage);
  forLoopSd(clt, READ_SDS, _sdCltSend, &Select::sendMessage);
  mapSockServer &srv = _serverManager.getSockets();
  forLoopSd(srv, READ_SDS, _sdServ, &Select::acceptClient);
}

void Select::udateData() {
  _fdSets[TMP_READ_SDS] = _fdSets[READ_SDS];
  _fdSets[TMP_WRITE_SDS] = _fdSets[WRITE_SDS];
}

void Select::endServer(int signal) {
  (void)signal;
  _this->_run = false;
  cout << "goodbay" << endl;
}

void Select::init() {
  signal(SIGINT, endServer);
  signal(SIGQUIT, endServer);
  signal(SIGTERM, endServer);
  signal(SIGPIPE, SIG_IGN);
  FD_ZERO(&_fdSets[READ_SDS]);
  FD_ZERO(&_fdSets[WRITE_SDS]);
  FD_ZERO(&_fdSets[TMP_READ_SDS]);
  FD_ZERO(&_fdSets[TMP_WRITE_SDS]);
  mapSockServer &sock = _serverManager.getSockets();
  for (mapSockServerIt it = sock.begin(); it != sock.end(); ++it) {
    FD_SET(it->first, &_fdSets[READ_SDS]);
    _sds.insert(it->first);
  }
}

void Select::deinit() {
  for (setIntIt it = _sds.begin(); it != _sds.end(); ++it) {
    closeConnection(*it);
  }
}

void Select::loop() {
  init();
  while (_run) {
    try {
      udateData();
      check(select(*_sds.rbegin() + 1, &_fdSets[TMP_READ_SDS],
                   &_fdSets[TMP_WRITE_SDS], NULL, NULL));
    } catch (const Exception &e) {
      e.print();
    }
  }
  deinit();
}
