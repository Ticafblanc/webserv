cmake_minimum_required(VERSION 3.22.1)
project(webserver)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(SYSTEM ./)

set(    MAIN
        Source_Code/0-Main/Sources/main.cpp
        Source_Code/0-Main/Sources/Exception.cpp)

set(    CONFIG
        Source_Code/1-Config/Sources/Config.cpp
        Source_Code/1-Config/Sources/ConfigFile.class.cpp
        Source_Code/1-Config/Sources/Code.class.cpp
        Source_Code/1-Config/Sources/Server.class.cpp
        Source_Code/1-Config/Sources/Events.class.cpp
        Source_Code/1-Config/Sources/Http.class.cpp
        Source_Code/1-Config/Sources/Types.class.cpp
        Source_Code/1-Config/Sources/Listen.class.cpp
        Source_Code/1-Config/Sources/Location.class.cpp
        Source_Code/1-Config/Sources/Log.class.cpp)

set(    ENGIN
        Source_Code/2-Engin/Sources/Epoll.class.cpp
        Source_Code/2-Engin/Sources/Socket.class.cpp
        Source_Code/2-Engin/Sources/Token.cpp)

set(    MESSAGE
        Source_Code/3-Message/Sources/HttpMessage.class.cpp
        Source_Code/3-Message/Sources/HttpReponse.class.cpp
        Source_Code/3-Message/Sources/HttpRequest.class.cpp
        Source_Code/3-Message/Sources/Execute.class.cpp)

set(    UTILS
        Source_Code/4-Utils/Sources/PegParser.class.cpp
        Source_Code/4-Utils/Sources/Utils.cpp)



#set(UNIT_TEST_INIT Unit_test/Sources/unitTestInit.cpp Sources/serverSocket.class.cpp)
#set(UNIT_TEST_LAUNCHER Unit_test/Sources/unitTestLauncher.cpp)

#add_library(webservlib ${MAIN} ${UTILS} ${LOG} ${CONFIG} ${HTTP} ${EPOLL} ${PEG} ${SOCKET} ${EXCEPTION})
#target_link_libraries(webservlib)

#enable_testing()

add_executable(webserv ${MAIN} ${CONFIG} ${ENGIN} ${MESSAGE} ${UTILS})

#add_executable(unitTestInit ${UNIT_TEST_INIT})
#target_link_libraries(unitTestInit webservlib)
#add_executable(unitTestLauncher ${UNIT_TEST_LAUNCHER})
#target_link_libraries(unitTestLauncher webservlib)

#add_test(NAME initTest COMMAND unitTestInit)
#add_test(NAME launcherTest COMMAND unitTestLauncher)
