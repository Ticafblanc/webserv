//
// Created by Matthis DoQuocBao on 2024-02-19.
//

#ifndef WEBSERV_MAIN_HPP
#define WEBSERV_MAIN_HPP

#define PATH_TO_PID_LOG_FILE_ ".webserv/log/pid.log"
#define PATHTOCONFIGLOGFILE_ ".webserv/log/config.log"
#define PATHTOACCESSLOGFILE_ ".webserv/log/access.log"
#define PATHTOERRORLOGFILE_ ".webserv/log/error.log"

#include <algorithm>
#include <arpa/inet.h>
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <dirent.h>
#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <netinet/in.h>
#include <ostream>
#include <poll.h>
#include <pthread.h>
#include <queue>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utility>
#include <vector>

using namespace std;

typedef pair<string, string> pairStrStr;
typedef pair<int, int> pairIntInt;
typedef vector<string> vecStr;
typedef vector<string>::iterator vecStrIt;
typedef vector<int> vecInt;
typedef vector<pairStrStr> vecPairStrStr;
typedef vecPairStrStr::iterator vecPairStrStrIt;
typedef vector<char> vecChar;
typedef set<string> setStr;
typedef set<int> setInt;
typedef map<string, string> mapStrStr;
typedef map<string, vecStr> mapStrVecStr;
typedef map<string, vecStr>::iterator mapStrVecStrIt;
typedef map<int, int> mapIntInt;
typedef map<int, pairStrStr> mapIntPairStrStr;
typedef map<int, string> mapIntStr;
typedef queue<string> queStr;

class Socket;
typedef std::map<int, Socket *> mapFdSockPtr;
typedef mapFdSockPtr::iterator mapFdSockPtrIt;

struct Config;
typedef pair<string, Config> pairStrConf;
typedef vector<pairStrConf> vecPairStrConf;
typedef map<string, vecPairStrConf> mapStrVecPairStrConf;

template <class T> class PegParser;
typedef PegParser<string> ppStr;

const int BUFFER_SIZE = 1024;
const int MAX_CLIENTS = 10;

#endif // WEBSERV_MAIN_HPP
