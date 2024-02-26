//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/9-select.hpp"

Select *Select::_this = NULL;

Select::Select(SocketManager<Socket> &sm, SocketManager<Client> &cm)
    : _run(true), _serverManager(sm), _clientManager(cm) {
  _this = this;
}

Select::Select(const Select &copy)
    : _run(true), _serverManager(copy._serverManager),
      _clientManager(copy._clientManager) {
  _this = this;
}

Select::~Select() {}

Select &Select::operator=(const Select &rhs) {
  if (this != &rhs) {
    _this = this;
    _run = rhs._run;
    _serverManager = rhs._serverManager;
    _clientManager = rhs._clientManager;
  }
  return *this;
}

// static std::string ft_inet_ntoa(struct in_addr in) {
//   std::stringstream buffer;
//
//   unsigned char *bytes = (unsigned char *)&in;
//   for (int cur_bytes = 0; cur_bytes < 4; cur_bytes++) {
//     buffer << (int)bytes[cur_bytes];
//     if (cur_bytes != 3)
//       buffer << '.';
//   }
//   DEBUG("INET NTOA = " << buffer.str())
//   return (buffer.str());
// }

void Select::acceptConnection(const int &sd, int *intVal, fd_set *fdSets) {
  sockaddr_in client = {};
  socklen_t size = sizeof(client);
  int newSd = accept(sd, (sockaddr *)&client, &size);
  if (newSd < 0) {
    if (errno != EWOULDBLOCK)
      throw(throwMessageErrno("accept() failed, " + itoa(errno)));
    return;
  }
  FD_SET(newSd, &fdSets[READ_SDS]);
  FD_SET(newSd, &fdSets[WRITE_SDS]);
  if (newSd > *intVal)
    *intVal = newSd;
}

/* return 0 = nop, 1 = classic content, 2 = chunked*/
static int hasContent(std::string request) {
  size_t pos_in = 0;
  std::string line;

  size_t pos = 0;
  size_t end = request.find("\n");
  while (end != std::string::npos) {
    line = request.substr(pos, end - pos);
    if ((pos_in = line.find("Transfer-Encoding: chunked")) !=
            std::string::npos &&
        pos_in == 0)
      return (2);
    else if (((pos_in = line.find("Content")) != std::string::npos) &&
             pos_in == 0)
      return (1);
    if ((pos_in = request.find("\r\n\r\n")) != std::string::npos &&
        pos_in == pos)
      break;
    pos = end + 1;
    end = request.find("\n", pos);
  }
  return (0);
}

static size_t getContentLen(std::string request) {
  size_t pos_in = 0;
  std::string line;

  size_t pos = 0;
  size_t end = request.find("\n");
  while (end != std::string::npos) {
    line = request.substr(pos, end - pos);
    if (((pos_in = line.find("Content-Length")) != std::string::npos) &&
        pos_in == 0)
      return (atoi(line.substr(line.find(":") + 2, line.length()).c_str()));
    if ((pos_in = request.find("\r\n\r\n")) != std::string::npos &&
        pos_in == pos)
      break;
    pos = end + 1;
    end = request.find("\n", pos);
  }
  return (0);
}

int Select::receiveConnection(int sd, std::string &request) {
  char buffer_recv[BUFFER_SIZE + 1];
  bzero(buffer_recv, BUFFER_SIZE + 1);
  int rc = 0;
  rc = read(sd, buffer_recv, BUFFER_SIZE);
  if (rc > 0) {
    cout << buffer_recv << endl;
    request.append(buffer_recv);
    size_t pos;
    int has_content = hasContent(request);
    if ((pos = request.find("\r\n\r\n")) != std::string::npos &&
        has_content == 0)
      return (0);
    if (has_content > 0) {
      std::string rest = request.substr(pos + 4, request.length() - (pos + 4));
      if (has_content != 2 && getContentLen(request) == rest.length())
        return (0);

      std::string to_find = "\r\n\r\n";

      if (has_content == 2)
        to_find = "0" + to_find;
      if ((pos = rest.find(to_find)) != std::string::npos) {
        if ((has_content == 2 &&
             (pos == 0 || (rest[pos - 1] == '\n' && rest[pos - 2] == '\r'))) ||
            has_content == 1)
          return (0);
      }
    }
  } else {
    Log("Error or connection close on : " + itoa(sd));
    return (-1);
  }
  return (1);
}

int Select::closeConnection(int sd, int max_sd, fd_set *read_set,
                            fd_set *write_set) {
  Log("Close client connection : " + itoa(sd));
  close(sd);
  FD_CLR(sd, read_set);
  FD_CLR(sd, write_set);
  if (sd == max_sd)
    while (FD_ISSET(max_sd, read_set) == false)
      max_sd -= 1;
  return (max_sd);
}

std::string Select::getServerName(const Headers &hb) {
  std::string server_name;

  for (size_t i = 0; i < hb.getHeaderFields().size(); i++) {
    DEBUG("Header name = " << hb.getHeaderFields()[i]._field_name)
    if (hb.getHeaderFields()[i]._field_name == "Host") {
      size_t pos = hb.getHeaderFields()[i]._field_value.find(':');
      if (pos != std::string::npos)
        server_name = hb.getHeaderFields()[i]._field_value.substr(0, pos);
      else
        server_name = hb.getHeaderFields()[i]._field_value.substr(
            0, hb.getHeaderFields()[i]._field_value.length());
      DEBUG("Select Name = " << server_name)
      break;
    }
  }
  return (server_name);
}

void Select::endServer(int signal) {
  (void)signal;
  _this->_run = false;
  cout << "goodbay" << endl;
}

void Select::checkServer(fd_set *fdSets, int *intVal) {
  for (SocketManager<Socket>::mapSockIt it =
           _serverManager.getSockets().begin();
       it != _serverManager.getSockets().end() && *intVal; ++it) {
    if (FD_ISSET(it->first, &fdSets[TMP_READ_SDS]) && intVal--)
      acceptConnection(it->first, intVal, fdSets);
  }
}

int recvMessage(Client &clt) {
  if ((rtn = receiveConnection(client_sd, client_socket.getRequest())) < 0) {
    max_sd =
        closeConnection(client_sd, max_sd, &master_rest_set, &master_write_set);
    //            delete _clientManager.getSockets()[client];
    _clientManager.getSockets().erase(_clientManager.getSockets().begin() +
                                      client);
    client--;
  } else if (rtn == 0)
    client_socket.setReceived(true)
}
int sendMessage(Client &clt) {
  Headers header(client_socket.getRequest(), client_socket.getClientIp(),
                 hasContent(client_socket.getRequest()));
  std::string server_name = getServerName(header);
  //            Socket *last = _serverManager.getBySDandHost(
  //                client_socket.getParent()->getSocketDescriptor(),
  //                server_name);
  size_t len = header.getPlainRequest().length();
  if (header.getPlainRequest() == "\r\n" || len < 9)
    throw(throwMessage("Empty request"));
  //            if (treat(client_sd, header,
  //                      (*last).getServerConfiguration()) == -1) {
  //              max_sd = closeConnection(
  //                  client_sd, max_sd, &master_rest_set,
  //                  &master_write_set);
  //              delete _clientManager.getSockets()[client];
  //              _clientManager.getSockets().erase(
  //                  _clientManager.getSockets().begin() +
  //                  client);
  //              client--;
  //              continue;
  //            }
  client_socket.getRequest().clear();
  client_socket.setReceived(false);
}

void Select::checkClient(fd_set *fdSets, int *intVal) {
  for (SocketManager<Client>::mapSockIt it =
           _clientManager.getSockets().begin();
       it != _clientManager.getSockets().end(); ++it) {

    if (FD_ISSET(it->first, &fdSets[TMP_WRITE_SDS]) &&
        it->second.informationReceived()) {
      try {
        sendMessage(it->second);
      } catch (const std::exception &e) {
        throwError(e);
      }
    }

    if (FD_ISSET(it->first, &fdSets[TMP_READ_SDS]) &&
        !it->second.informationReceived()) {
      try {
        recvMessage(it->second);
      } catch (const std::exception &e) {
        throwError(e);
      }
    }
  }

  static void resetCountError(int &countError) { countError = 3; }
  static bool countErrorIsValid(int &countError) { return countError-- > 0; }

  static void udateData(fd_set * fdSets) {
    fdSets[TMP_READ_SDS] = fdSets[READ_SDS];
    fdSets[TMP_WRITE_SDS] = fdSets[WRITE_SDS];
  }

  static void initSelect(fd_set * fdSets, int *greaterSds,
                         SocketManager<Socket>::mapSock &sockets) {
    FD_ZERO(&fdSets[READ_SDS]);
    FD_ZERO(&fdSets[WRITE_SDS]);
    FD_ZERO(&fdSets[TMP_READ_SDS]);
    FD_ZERO(&fdSets[TMP_WRITE_SDS]);
    for (SocketManager<Socket>::mapSockIt it = sockets.begin();
         it != sockets.end(); ++it) {
      FD_SET(it->first, &fdSets[READ_SDS]);
      if (*greaterSds < it->first)
        *greaterSds = it->first;
    }
  }

  void Select::loop() {
    signal(SIGINT, endServer);
    int intVal[3];
    fd_set fdSets[4];
    initSelect(fdSets, &intVal[GREATER_SDS], _serverManager.getSockets());
    resetCountError(intVal[COUNT_ERROR]);
    while (_run) {
      udateData(fdSets);
      try {
        intVal[RETURN_VALUE] =
            select(intVal[GREATER_SDS] + 1, &fdSets[TMP_READ_SDS],
                   &fdSets[TMP_WRITE_SDS], NULL, NULL);
        if (intVal[RETURN_VALUE] >= 0) {
          resetCountError(intVal[COUNT_ERROR]);
          checkServer(fdSets, intVal);
          checkClient(fdSets, intVal);
        } else if (!countErrorIsValid(intVal[COUNT_ERROR]) || usleep(1000))
          throw(throwMessageErrno("Select error"));
      } catch (const std::exception &e) {
        throwError(e);
      }
    }
  }
