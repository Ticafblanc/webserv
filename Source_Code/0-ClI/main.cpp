#include <Includes/Cli.class.hpp>

int main(int argc,  char **argv) {
    (void)argv;
    (void)argc;
    std::cout << "Start test Cli class" << std::endl;
    std::vector<char *> vec;
    char prog[] ="cli_test";
    char option[] =" -s ";
    char configFile[] =" /webserv/Source_Code/0-Cli/conf_test.conf ";
    char ** arg = new char *  ;
    arg[0] = prog;
    arg[1] = option;
    arg [2] = configFile;

    std::cout << "Test  To much argc" << std::endl;
    Cli cliToMuchArgc(4, arg);
    std::cout << "Process finished with exit code " << cliToMuchArgc.getStatus() << std::endl;

    std::cout << "Test  no arg" << std::endl;
    Cli cliNoArg(1, NULL);
    std::cout << "Process finished with exit code " << cliNoArg.getStatus() << std::endl;

    std::cout << "Test  print -? -h" << std::endl;
    Cli cliHelp(2, arg);
    std::cout << "Process finished with exit code " << cliHelp.getStatus() << std::endl;

    std::cout << "Test -c -t file" << std::endl;
    Cli cliConf(2, arg);
    std::cout << "Process finished with exit code " << cliConf.getStatus() << std::endl;

    char command[] =" quit ";
    arg[2] = command;
    std::cout << "Test -s file" << std::endl;
    Cli cliSignal(3, arg);
    std::cout << "Process finished with exit code " << cliSignal.getStatus() << std::endl;
    return 0;
}
