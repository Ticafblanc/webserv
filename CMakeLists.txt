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
        Source_Code/1-Config/Sources/Types.class.cpp
        Source_Code/1-Config/Sources/Listen.class.cpp
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
        Source_Code/4-Utils/Template/PegParser.class.tpp
        Source_Code/4-Utils/Sources/Utils.cpp)


#add_executable(webserv ${MAIN} ${CONFIG} ${ENGIN} ${MESSAGE} ${UTILS})
add_library(webserver_lib STATIC ${MAIN} ${CONFIG} ${ENGIN} ${MESSAGE} ${UTILS})

add_executable(webserv Source_Code/0-Main/Sources/main.cpp)

target_link_libraries(webserv PRIVATE webserver_lib ${CMAKE_DL_LIBS})

enable_testing()

function(test_conf RUN CONFIG_TEST input_file expected_output)

    set(TEST_DIR "libUnitTest/config_test")

    add_test(NAME ${RUN} COMMAND webserv -t ${TEST_DIR}/${input_file} )

    add_executable(${CONFIG_TEST} libUnitTest/Sources/testConf.cpp)

    add_test(NAME ${CONFIG_TEST} COMMAND ${CONFIG_TEST} ../Docker_build/var/log/webserv.pid ../${TEST_DIR}/${expected_output} )

endfunction()


test_conf(run_minimal_server minimal_server minimal_server.conf minimal_server.expect)
test_conf(run_base_conf base_conf base.conf base.expect)






#set(    UNIT_TEST_CONFIG_FILE
#        libUnitTest/Sources/testConfigFile.cpp)
#
#add_executable(webservUnitTestConfigFile ${UNIT_TEST_CONFIG_FILE})
#
##add_library(webservlib ${MAIN} ${CONFIG} ${ENGIN} ${MESSAGE} ${UTILS})
##
##target_link_libraries(webserv webservlib)
#
#add_test(NAME TestConfigFile COMMAND ${CMAKE_COMMAND} -E bash -c "$<TARGET_FILE:myexecutable> my_argument > output.txt")
#
#add_test(NAME TestConfigFile COMMAND $<TARGET_FILE:webserv> -t)
