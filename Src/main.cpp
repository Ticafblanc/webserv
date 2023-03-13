#include "../Include/webserv.hpp"

int main(int argc, char **argv)
{
    if (argc > 2)
        cerr << "Takes a config file, leave empty for default config" << endl;
    else if (argc == 2)
        parse_config_file(argv[1]); // function that will be used to parse config file and set config options. Will most likely populate a class
    
    server_routine(); // aka do something here
}