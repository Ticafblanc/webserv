//
// Created by Matthis DoQuocBao on 2024-02-19.
//

#ifndef WEBSERV_MAIN_HPP
#define WEBSERV_MAIN_HPP

#define _PATHTOPIDLOGFILE_ ".webserv/log/pid.log"
#define _PATHTOCONFIGLOGFILE_ ".webserv/log/config.log"
#define _PATHTOACCESSLOGFILE_ ".webserv/log/access.log"
#define _PATHTOERRORLOGFILE_ ".webserv/log/error.log"

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
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utility>
#include <vector>

using namespace std;

typedef vector<string> vecStr;
typedef vector<string>::iterator vecStrIt;
typedef vector<int> vecInt;
typedef vector<pair<string, int>> vecFiles;
typedef vector<char> vecChar;
typedef set<string> setStr;
typedef set<int> setInt;
typedef map<string, string> mapStrStr;
typedef map<string, vecStr> mapStrVecStr;
typedef map<string, vecStr>::iterator mapStrVecStrIt;
typedef map<int, int> mapIntInt;
typedef map<int, string> mapIntStr;
typedef pair<string, string> pairStrStr;
typedef pair<int, int> pairIntInt;
typedef pair<int, pairIntInt> pairIntIntD;
typedef queue<string> queStr;

const int BUFFER_SIZE = 1024;
const int MAX_CLIENTS = 10;

#endif // WEBSERV_MAIN_HPP
