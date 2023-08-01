#include <Includes/Cli.class.hpp>

int main(int argc,  char **argv) {
    (void)argv;
    (void)argc;
    std::cout << "Start test Cli class" << std::endl;
    std::vector<char *> vec;
    char prog[] ="@";
    char option[] =" -? ";
    char configFile[] =" file_name ";
    char ** arg = new char *  ;
    arg[0] = prog;
    arg[2] = option;
    arg [1] = configFile;

    Cli cli1(3, arg);
    try{
        cli1.checkArg();
    }catch (const std::exception & e){
        std::cerr << "\n" << e.what() << std::endl;
        return 1;
    }
    return 0;
}
