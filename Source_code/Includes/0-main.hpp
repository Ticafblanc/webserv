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
#include <exception>
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
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utility>
#include <vector>

using namespace std;

typedef pair<string, string> pairStrStr;
typedef pair<int, int> pairIntInt;
typedef pair<bool, string> pairBoolStr;
typedef vector<string> vecStr;
typedef vector<string>::iterator vecStrIt;
typedef vector<int> vecInt;
typedef vector<pairStrStr> vecPairStrStr;
typedef vecPairStrStr::iterator vecPairStrStrIt;
typedef vector<char> vecChar;
typedef set<string> setStr;
typedef set<string>::iterator setStrIt;
typedef set<int> setInt;
typedef set<int>::iterator setIntIt;
typedef map<string, string> mapStrStr;
typedef map<string, vecStr> mapStrVecStr;
typedef map<string, vecStr>::iterator mapStrVecStrIt;
typedef map<int, int> mapIntInt;
typedef map<int, pairStrStr> mapIntPairStrStr;
typedef map<int, string> mapIntStr;
typedef queue<string> queStr;

extern char **envp;

// macro for select int[3] intVal
#define RETURN_VALUE 0
#define COUNT_ERROR 1

// macro for select for max connection
#define MAX_CONNECTION 100

// macro for select fd_set[4] fdSets
#define READ_SDS 0
#define WRITE_SDS 1
#define TMP_READ_SDS 2
#define TMP_WRITE_SDS 3

// macro for recv/send data
#define BUFFER_SIZE 1024

//macro for Header firstline
#define METHOD 0
#define PATH 1
#define HTTP_V 2
#define STATUS_CODE 3
#define RAISON_PHRASE 4

//

#endif // WEBSERV_MAIN_HPP
