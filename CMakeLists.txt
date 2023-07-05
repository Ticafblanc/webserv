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
        Source_Code/2-Engin/Sources/Token.cpp Source_Code/2-Engin/Sources/Client.class.cpp)

set(    MESSAGE
        Source_Code/3-Message/Sources/HttpMessage.Iclass.cpp
        Source_Code/3-Message/Sources/HttpReponse.class.cpp
        Source_Code/3-Message/Sources/HttpMessage.class.cpp
        Source_Code/3-Message/Sources/Execute.class.cpp)

set(    UTILS
        Source_Code/4-Utils/Template/PegParser.class.tpp
        Source_Code/4-Utils/Sources/Utils.cpp Source_Code/4-Utils/Template/recv_send.tpp Source_Code/4-Utils/Template/read_write.tpp)


#add_executable(webserv ${MAIN} ${CONFIG} ${ENGIN} ${MESSAGE} ${UTILS})
add_library(webserver_lib STATIC ${MAIN} ${CONFIG} ${ENGIN} ${MESSAGE} ${UTILS})

add_executable(webserv Source_Code/0-Main/Sources/main.cpp)

target_link_libraries(webserv PRIVATE webserver_lib ${CMAKE_DL_LIBS})

enable_testing()

function(test_fail_conf RUN input_file error status)

    set(TEST_DIR "libUnitTest/config_test")

    add_test(NAME ${RUN} COMMAND webserv -t ../${TEST_DIR}/${input_file} )

#    if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.20")
        set_tests_properties(${RUN} PROPERTIES PASS_REGULAR_EXPRESSION "${error}\n${status}")
#    else()
#        set_tests_properties(${RUN} PROPERTIES PASS_REGULAR_EXPRESSION "${error}\n${status}")
#    endif()

endfunction()

test_fail_conf(run_minimal_empty minimal_empty.conf
        "No IP:PORT to listen" "webserv: configuration file ../libUnitTest/config_test/minimal_empty.conf test failed")
test_fail_conf(run_wrongWorkerProcessMin_error wrongWorkerProcessMin_error.conf
        "value invalid in invalide data for worker processes => 0" "webserv: configuration file ../libUnitTest/config_test/wrongWorkerProcessMin_error.conf test failed")
test_fail_conf(run_wrongWorkerProcessMax_error wrongWorkerProcessMax_error.conf
        "value invalid in invalide data for worker processes => 5" "webserv: configuration file ../libUnitTest/config_test/wrongWorkerProcessMax_error.conf test failed")
test_fail_conf(run_wrongClientBodyBufferSizeMin_error wrongClientBodyBufferSizeMin_error.conf
        "value invalid in invalide data for body buffer size => 1023" "webserv: configuration file ../libUnitTest/config_test/wrongClientBodyBufferSizeMin_error.conf test failed")
test_fail_conf(run_wrongClientBodyBufferSizeMax_error wrongClientBodyBufferSizeMax_error.conf
        "value invalid in invalide data for body buffer size => 8193" "webserv: configuration file ../libUnitTest/config_test/wrongClientBodyBufferSizeMax_error.conf test failed")
test_fail_conf(run_wrongClientBodyHeaderSizeMin_error wrongClientBodyHeaderSizeMin_error.conf
        "value invalid in invalide data for header buffer size => 511" "webserv: configuration file ../libUnitTest/config_test/wrongClientBodyHeaderSizeMin_error.conf test failed")
test_fail_conf(run_wrongClientBodyHeaderSizeMax_error wrongClientBodyHeaderSizeMax_error.conf
        "value invalid in invalide data for header buffer size => 1025" "webserv: configuration file ../libUnitTest/config_test/wrongClientBodyHeaderSizeMax_error.conf test failed")
test_fail_conf(run_wrongClientMaxBodySizeMin_error wrongClientMaxBodySizeMin_error.conf
        "value invalid in invalide data for max body size => 1048576" "webserv: configuration file ../libUnitTest/config_test/wrongClientMaxBodySizeMin_error.conf test failed")
test_fail_conf(run_wrongClientMaxBodySizeMax_error wrongClientMaxBodySizeMax_error.conf
        "value invalid in invalide data for max body size => 500000" "webserv: configuration file ../libUnitTest/config_test/wrongClientMaxBodySizeMax_error.conf test failed")
test_fail_conf(run_wrongWorkerConnectionMin_error wrongWorkerConnectionMin_error.conf
        "value invalid in invalide data for workerConnection => 9" "webserv: configuration file ../libUnitTest/config_test/wrongWorkerConnectionMin_error.conf test failed")
test_fail_conf(run_wrongWorkerConnectionMax_error wrongWorkerConnectionMax_error.conf
        "value invalid in invalide data for workerConnection => 21" "webserv: configuration file ../libUnitTest/config_test/wrongWorkerConnectionMax_error.conf test failed")
test_fail_conf(run_wrongListenPortMin_error wrongListenPortMin_error.conf
        "value invalid in Port is out of range." "webserv: configuration file ../libUnitTest/config_test/wrongListenPortMin_error.conf test failed")
test_fail_conf(run_wrongListenPortMax_error wrongListenPortMax_error.conf
        "value invalid in Port is out of range." "webserv: configuration file ../libUnitTest/config_test/wrongListenPortMax_error.conf test failed")
test_fail_conf(run_wrongListenIP_error wrongListenIP_error.conf
        "value invalid in Bad ip segment: check ip limit" "webserv: configuration file ../libUnitTest/config_test/wrongListenIP_error.conf test failed")
test_fail_conf(run_wrongListenIPNoPort_error wrongListenIPNoPort_error.conf
        "value invalid in Port is out of range." "webserv: configuration file ../libUnitTest/config_test/wrongListenIPNoPort_error.conf test failed")
test_fail_conf(run_wrong_ServerNameEmpty_error wrongServerNameEmpty_error.conf
        "value invalid in no value at server_name" "webserv: configuration file ../libUnitTest/config_test/wrongServerNameEmpty_error.conf test failed")
test_fail_conf(run_wrong_root_error wrongRoot_error.conf
        "value invalid in Path not found => /error/path/defaut.com" "webserv: configuration file ../libUnitTest/config_test/wrongRoot_error.conf test failed")
test_fail_conf(run_wrong_codeMin_error wrongCodeMin_error.conf
        "value invalid in value in code invalid for return => 99" "webserv: configuration file ../libUnitTest/config_test/wrongCodeMin_error.conf test failed")
test_fail_conf(run_wrong_codeMax_error wrongCodeMax_error.conf
        "value invalid in value in code invalid for return => 600" "webserv: configuration file ../libUnitTest/config_test/wrongCodeMax_error.conf test failed")
test_fail_conf(run_wrong_codeNotFound_error wrongCodeNotFound_error.conf
        "value invalid in value in code invalid for return => 419" "webserv: configuration file ../libUnitTest/config_test/wrongCodeNotFound_error.conf test failed")
test_fail_conf(run_wrong_codeNotIndex_error wrongCodeNotIndex_error.conf
        "value invalid in no index to set" "webserv: configuration file ../libUnitTest/config_test/wrongCodeNotIndex_error.conf test failed")


function(test_success_conf RUN CONFIG_TEST input_file expected_output)

    set(TEST_DIR "libUnitTest/config_test")

    add_test(NAME ${RUN} COMMAND webserv -t ../${TEST_DIR}/${input_file} )

    add_executable(${CONFIG_TEST} libUnitTest/Sources/testConf.cpp)

    add_test(NAME ${CONFIG_TEST} COMMAND ${CONFIG_TEST} ../Docker_build/var/log/webserv.pid ../${TEST_DIR}/${expected_output} )

endfunction()

test_success_conf(run_minimal_server minimal_server minimal_server.conf minimal_server.expect)
test_success_conf(run_minimal_http minimal_http minimal_http.conf minimal_http.expect)
test_success_conf(run_base base base.conf base.expect)
test_success_conf(run_multiServer  multiServer multiServer.conf multiServer.expect)
