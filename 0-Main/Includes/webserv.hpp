#pragma once

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "Headers.hpp"
#include "1-Utils/Includes/Utils.hpp"
#include "2-Log/Log.class.hpp"
#include "3-Config/Config.class.hpp"
//#include "4-Http/Includes/HttpMessage.class.hpp"
#include "5-Epoll/Epoll.class.hpp"
#include "6-PegParser/PegParser.class.hpp"
#include "7-Socket/Socket.class.hpp"
//#include "8-Exception/Includes/Exception.hpp"

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

#endif
