#pragma once

#ifndef WEBSERV_HEADER_HPP
#define WEBSERV_HEADER_HPP

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <vector>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fstream>
#include <exception>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <csignal>
#include <map>
#include <sstream>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <ctime>
#include <limits>


#define FLAG1 0x01 // 0000 0001
#define FLAG2 0x02 // 0000 0010
#define FLAG3 0x04 // 0000 0100
#define FLAG4 0x08 // 0000 1000
#define FLAG5 0x10 // 0001 0000
#define FLAG6 0x20 // 0010 0000
#define FLAG7 0x40 // 0100 0000
#define FLAG8 0x80 // 1000 0000

//__FILE_NAME__
// __LINE__
//__PRETTY_FUNCTION__

using std::string;
using std::vector;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;


#endif
