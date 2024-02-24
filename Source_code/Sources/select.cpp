//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/select.hpp"

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

int Select::acceptConnection(int sd, int max_sd, fd_set *read_set,
                             fd_set *write_set,
                             SocketManager<Client> &sub_serverManager) {
  (void)sub_serverManager;
  int new_sd = 0;

  DEBUG("Readable socket")

  sockaddr_in client;
  socklen_t size = sizeof(client);
  if ((new_sd = accept(sd, (sockaddr *)&client, &size)) < 0) {
    if (errno != EWOULDBLOCK)
      throw(throwMessageErrno("accept() failed, " + itoa(errno)));
    return (max_sd);
  }

  // std::cout << "new_sd"

  Log("New client connection : " + itoa(new_sd));
  //  sub_serverManager.registerSocket(new Client(
  //      &_serverManager.getBySD(sd), ft_inet_ntoa(client.sin_addr), new_sd));
  FD_SET(new_sd, read_set);
  FD_SET(new_sd, write_set);
  if (new_sd > max_sd)
    max_sd = new_sd;
  return (max_sd);
}

#define BUFFER_SIZE_READ 1000000

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
  char buffer_recv[BUFFER_SIZE_READ + 1];
  bzero(buffer_recv, BUFFER_SIZE_READ + 1);
  int rc = 0;
  rc = read(sd, buffer_recv, BUFFER_SIZE_READ);
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

template <class T> static bool vector_contain(std::vector<T> tab, T obj) {
  for (size_t i = 0; i < tab.size(); i++)
    if (tab[i] == obj)
      return (true);
  return (false);
}

void Select::verifyDefaultServer() {
  int actual_check = -1;
  vector<int> checked_ports;
  vector<Socket> actual_set;

  for (size_t i = 0; i < this->_serverManager.getSockets().size(); i++) {
    actual_check =
        this->_serverManager.getSockets()[i].getServerConfiguration().port;
    if (vector_contain<int>(checked_ports, actual_check) == false) {
      bool has_default = false;
      for (size_t j = 0; j < this->_serverManager.getSockets().size(); j++)
        if ((int)this->_serverManager.getSockets()[j]
                .getServerConfiguration()
                .port == actual_check)
          actual_set.push_back(this->_serverManager.getSockets()[j]);
      for (size_t f = 0; f < actual_set.size(); f++)
        if (vector_contain<std::string>(
                actual_set[f].getServerConfiguration().names,
                "default_server") == true)
          has_default = true;
      if (has_default == false)
        actual_set[0].setToDefault();
      checked_ports.push_back(actual_check);
    }
  }
}

void Select::endServer(int signal) {
  (void)signal;
  _this->_run = false;
  cout << "goodbay" << endl;
}

void Select::checkServer(fd_set &readSet, int &maxSd, fd_set &masterRestSet,
                         fd_set &masterWriteSet) {
  for (size_t server = 0; server < this->_serverManager.getSockets().size();
       server++) {
    int serverSd =
        this->_serverManager.getSockets()[server].getSocketDescriptor();
    if (FD_ISSET(serverSd, &readSet))
      maxSd = this->acceptConnection(serverSd, maxSd, &masterRestSet,
                                     &masterWriteSet, _clientManager);
  }
}

void Select::checkClient(fd_set &readSet, int &maxSd, fd_set &masterRestSet,
                         fd_set &masterWriteSet) {
  for (size_t client = 0;
       client < this->_clientManager.getSockets().size(); client++) {
    int rtn;
    Client &client_socket = this->_clientManager.getSockets()[client];
    int client_sd = client_socket.getSocketDescriptor();
    bool client_treat = false;

    if (FD_ISSET(client_sd, &write_set) &&
        client_socket.informationReceived() == true) {
      try {
        Headers header(client_socket.getRequest(),
                       client_socket.getClientIp(),
                       hasContent(client_socket.getRequest()));
        std::string server_name = this->getServerName(header);
        //            Socket *last = this->_serverManager.getBySDandHost(
        //                client_socket.getParent()->getSocketDescriptor(),
        //                server_name);
        size_t len = header.getPlainRequest().length();
        if (header.getPlainRequest() == "\r\n" || len < 9)
          throw(throwMessage("Empty request"));
        //            if (treat(client_sd, header,
        //                      (*last).getServerConfiguration()) == -1) {
        //              max_sd = this->closeConnection(
        //                  client_sd, max_sd, &master_rest_set,
        //                  &master_write_set);
        //              delete this->_clientManager.getSockets()[client];
        //              this->_clientManager.getSockets().erase(
        //                  this->_clientManager.getSockets().begin() +
        //                  client);
        //              client--;
        //              continue;
        //            }
        client_socket.getRequest().clear();
        client_socket.setReceived(false);
        client_treat = true;
      } catch (const std::exception &e) {
        throwError(e);
      }
    }

    if (FD_ISSET(client_sd, &read_set) && client_treat == false) {
      if ((rtn = this->receiveConnection(
               client_sd, client_socket.getRequest())) < 0) {
        max_sd = this->closeConnection(
            client_sd, max_sd, &master_rest_set, &master_write_set);
        //            delete this->_clientManager.getSockets()[client];
        this->_clientManager.getSockets().erase(
            this->_clientManager.getSockets().begin() + client);
        client--;
      } else if (rtn == 0)
        client_socket.setReceived(true);
    }
}

void Select::loop() {
  signal(SIGINT, endServer);
  fd_set readSet;
  fd_set writeSet;
  fd_set masterRestSet;
  fd_set masterWriteSet;
  int maxSd;
  masterRestSet = this->_serverManager.getSDSet();
  FD_ZERO(&masterWriteSet);
  maxSd = _serverManager.getLastSD();
  verifyDefaultServer();
  while (_run) {
    readSet = masterRestSet;
    writeSet = masterWriteSet;
    try {
      if (select(maxSd + 1, &readSet, &writeSet, NULL, NULL) >= 0) {
        checkServer(readSet, maxSd, masterRestSet, masterWriteSet);
        checkClient(readSet, maxSd, masterRestSet, masterWriteSet);

        }
      }
    } catch (const std::exception &e) {
      throwError(e);
    }
  }
}

void Select::closeServer() {
  for (size_t client = 0; client < this->_clientManager.getSockets().size();
       client++) {
    close(this->_clientManager.getSockets()[client].getSocketDescriptor());
    Log("Client connection closed : " +
        itoa(this->_clientManager.getSockets()[client].getSocketDescriptor()));
    //    delete this->_clientManager.getSockets()[client];
  }

  for (size_t server = 0; server < this->_serverManager.getSockets().size();
       server++) {
    close(this->_serverManager.getSockets()[server].getSocketDescriptor());
    Log("Select closed : " +
        itoa(this->_serverManager.getSockets()[server].getSocketDescriptor()));
    //    delete this->_serverManager.getSockets()[server];
  }
}
