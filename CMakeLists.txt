cmake_minimum_required(VERSION 3.22.1)
project(webserver)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(SYSTEM ./)

set(    MAIN
        0-Main/Sources/main.cpp)

set(    UTILS
        1-Utils/Sources/Utils.cpp)

set(    LOG
        2-Log/Sources/Log.class.cpp)

set(    CONFIG
        3-Config/Sources/Config.class.cpp)

set(    HTTP)

set(    EPOLL)

set(    PEG
        6-PegParser/Sources/PegParser.class.cpp)

set(    SOCKET
        7-Socket/Sources/serverSocket.class.cpp
        7-Socket/Sources/Socket.Aclass.cpp
        7-Socket/Sources/clientSocket.class.cpp)

set(    EXCEPTION
        8-Exception/Sources/Exception.cpp)

#set(UNIT_TEST_INIT Unit_test/Sources/unitTestInit.cpp Sources/serverSocket.class.cpp)
#set(UNIT_TEST_LAUNCHER Unit_test/Sources/unitTestLauncher.cpp)

#add_library(webservlib ${MAIN} ${UTILS} ${LOG} ${CONFIG} ${HTTP} ${EPOLL} ${PEG} ${SOCKET} ${EXCEPTION})
#target_link_libraries(webservlib)

#enable_testing()

add_executable(webserv ${MAIN} ${UTILS} ${LOG} ${CONFIG} ${HTTP} ${EPOLL} ${PEG} ${SOCKET} ${EXCEPTION})

#add_executable(unitTestInit ${UNIT_TEST_INIT})
#target_link_libraries(unitTestInit webservlib)
#add_executable(unitTestLauncher ${UNIT_TEST_LAUNCHER})
#target_link_libraries(unitTestLauncher webservlib)

#add_test(NAME initTest COMMAND unitTestInit)
#add_test(NAME launcherTest COMMAND unitTestLauncher)
