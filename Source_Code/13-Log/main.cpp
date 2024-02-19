#include <Includes/Log.class.hpp>

int main() {
    std::cout << "Start test Log class" << std::endl;
    Log log_test;
    log_test.addToAccesLogBuffer("Epoll wait ...");
    log_test.openToAccesLogBuffer("open");
#ifdef LINUX
    log_test.addEventToAccess( 2, 22, EPOLLIN);
#endif
#ifdef MAC
    log_test.addEventToAccess( 2, 22, EVFILT_READ);
#endif

    log_test.addClientToAccess("127.0.0.1", 8080, 22, 33);
    log_test.addToAccesLogBuffer("ligne 1");
    log_test.addToAccesLogBuffer("ligne 2");
    log_test.openToAccesLogBuffer("open2");
    log_test.addToAccesLogBuffer("ligne 1");
    log_test.addToAccesLogBuffer("ligne 2");
    log_test.addToAccesLogBuffer("ligne 3");
    log_test.addToAccesLogBuffer("ligne 4");
    log_test.closeToAccesLogBuffer();
    log_test.addToAccesLogBuffer("ligne 3");
    log_test.addToAccesLogBuffer("ligne 4");
    log_test.closeToAccesLogBuffer();
    log_test.addToErrorLogBuffer("error 1");
    log_test.addToErrorLogBuffer("error 2");
    log_test.openToAccesLogBuffer("open");
    log_test.addToAccesLogBuffer("ligne 1");
    log_test.addToAccesLogBuffer("ligne 2");
    log_test.addToErrorLogBuffer("error 3");
    return 0;
}
