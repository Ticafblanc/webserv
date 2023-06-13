cmake_minimum_required(VERSION 3.22.1)
project(webserver)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(SYSTEM ./)

set(    MAIN
        0-Main/Sources/main.cpp 0-Main/Sources/Config.cpp)

set(    UTILS
        1-Utils/Sources/Utils.cpp)

set(    LOG
        2-Log/Log.class.cpp)

set(    CONFIG
        3-Config/ConfigFile.class.cpp
        3-Config/Code.class.cpp
        3-Config/Server.class.cpp
        3-Config/Events.class.cpp
        3-Config/Http.class.cpp
        3-Config/Types.class.cpp
        3-Config/Listen.class.cpp
        3-Config/Location.class.cpp)

set(    HTTP 4-Http/HttpMessage.class.cpp
        4-Http/HttpReponse.class.cpp
        4-Http/HttpRequest.class.cpp
        4-Http/Execute.class.cpp)

set(    EPOLL
        5-Epoll/Epoll.class.cpp
        5-Epoll/Token.cpp)

set(    PEG
        6-PegParser/PegParser.class.cpp)

set(    SOCKET
        5-Epoll/Socket.class.cpp)

set(    EXCEPTION
        8-Exception/Sources/Exception.cpp )

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
