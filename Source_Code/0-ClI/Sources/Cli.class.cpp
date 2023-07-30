


#include <Includes/Cli.class.hpp>


Cli::Cli(int argc, char ** argv) : _option(false), _stop(false), _launch(false), _checkFile(false), _argv(){
    for (int i = 1; i < argc; ++i) {
        _argv.push_back(argv[i]);
    }

}

Cli::~Cli() {}

Cli::Cli(const Cli & other){}

Cli &Cli::operator=(const Cli & rhs) {
    if (this != &rhs){
    }
    return *this;
}

void Cli::checkArg() {
    if (_argv.size() > 2) {
        printCliHelp();
        throw std::runtime_error("");
    }
    checkOption();
}

void Cli::printCliHelp(){
    std::cerr << "Error arguments   usage : webserv [-csth?] [-c file] [-s signal] [-t file]"
              << "\t\t-c file' Use an alternative configuration file."
              << "\t\t-s signal' Send signal to the master process.\n"
              << "\t\tstop' SIGTERM\n"
              << "\t\tquit' SIGQUIT\n"
              << "\t\treload' SIGHUP "
              << "\t\t-t' Don't run, just test the configuration file."
              << "\t\t-? | -h'               Print help."<< std::endl;
}

void  Cli::checkOption(){
    for (std::vector<std::string>::iterator it = _argv.begin(); it != _argv.end(); ++it){
        if ((*it)[0] == '-'){
            (*it).erase(0);
            if ((*it).find_first_not_of("csth?") == std::string::npos){
                printCliHelp();
                throw std::runtime_error("");
            }
            if ((*it) == "s")
                (void)argv;//@todo webserv -s (stop quit reopen reload) SIGINT, SIGTERM shutdown SIGHUP reload
            else if ((*it)[1] == 't')
                checkFile(argc, argv);
            else if ((*it)[1] == 'c' && argc == 3)
                return 2;
            std::cerr << "invalid option -" << argv[1][1] << std::endl;
            return -1;
        }
    }
    if (argc > 1) {
        if (argv[1][0] == '-') {

        }
        return 1;
    }
    return 0;
    std::istringstream iss(_argv[0]);
    if (_argv[0] == "-s" && _argv.size() == 2){
        if (_argv[1] == "stop" || _argv[1] == "reload")
            _stop = true;
        if (_argv[1] == "reload")
            _launch = true;
            killWebserv()

    }
        (void)_argv;//@todo webserv -s (stop reload) SIGINT, SIGTERM shutdown SIGHUP reload
    else if (_argv[0] == "-t")
        _checkFile = true;
    else if (_argv[0] == "-ts" || _argv[0] == "-st"){
(void)
_argv;//@todo webserv -s (stop reload) SIGINT, SIGTERM shutdown SIGHUP reload
_checkFile = true;
}
    else if (_argv[0] == "-c" && _argv.size() == 2)
        return 2;

}

bool Cli::isEnd() const {
    return _stop;
}

bool Cli::isCheckFile() const {
    return _checkFile;
}

bool Cli::isOption() const {
    return _option;
}
