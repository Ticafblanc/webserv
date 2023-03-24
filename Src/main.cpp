#include "../Include/webserv.hpp"

int main(int argc, char **argv)
{
    if (argc > 2)
        cerr << "Takes a config file, leave empty for default config" << endl;
    else if (argc == 2) {
        Parser parser(argv); //instantiation of parser
        parser.parse_config_file(); //call of method that does the parsing
    }
    
    server_routine(); // aka do something here
}