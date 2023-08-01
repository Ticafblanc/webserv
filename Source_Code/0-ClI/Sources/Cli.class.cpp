


#include <Includes/Cli.class.hpp>
#include <Source_Code/1-Config/Includes/ConfigFile.class.hpp>

Cli::Cli(int argc, char ** argv)
: _pid(getpid()), _status(EXIT_SUCCESS), _stop(isMainProgram()), _launch(false), _checkFile(false), _argv(){
    _this = this;
    if (argc > 3) {
        std::cerr << "Too much arguments" << std::endl;
        _status = EXIT_FAILURE;
        return;
    }
    try{
        setArg(argc, argv);
        checkArg();
    }catch (const std::exception & e){
        std::cerr << "\n" << e.what() << std::endl;
        printCliHelp();
        _status = EXIT_FAILURE;
        _stop = true;
    }
}

Cli::~Cli() {}

Cli::Cli(const Cli & other) : _checkFile(other._checkFile){

}

Cli &Cli::operator=(const Cli & rhs) {
    if (this != &rhs){
    }
    return *this;
}

bool Cli::isMainProgram(){
    std::ifstream ifs("5-Log/.Log_files/pid.log");
    if (!ifs.is_open())
        throw std::runtime_error("impossible to open pid.log");
    std::vector<char> pidVec(100);
    ifs.getline(pidVec.data(),100);
    std::stringstream ss(pidVec.data());
    pid_t pid = 0;
    ss >> pid;
    if (pid != 0){
        std::cout << "Welcome to Webserv !!\n";
        initSignal();
        return false;
    }
    std::cout << "Webserv already open!!\n";
    _pid = pid;
    return true;
}

void Cli::initSignal(){
    signal(SIGINT, handleExit);//webserv -s quit
    signal(SIGTERM, handleStop);//webserv -s stop
    signal(SIGHUP, handleReload);//webserv -s reload
}

void Cli::setArg(int argc, char ** argv){
    bool testMode = (argv[0][0] == '@');
    for (int i = 1; i < argc && i < 3; ++i) {
        std::istringstream iss(argv[i]);
        while (!iss.eof()) {
            std::string str;
            iss >> std::ws >> str;
            if (!str.empty())
                _argv.push(str);
            if (testMode)
                std::cout << _argv.size() << _argv.back() << std::endl;
        }
    }
}

void Cli::checkArg() {
    if (!_stop && _argv.empty())
        checkFile(std::string());
    else if (_argv.size() <= 2) {
        while (true) {
            if (_argv.front()[0] == '-')
                checkOption(_argv.front());
            else
                checkFile(_argv.front());
            if (_argv.empty())
                return;
        }
    } else {
        throw std::runtime_error("To much argument");
    }
}

void Cli::checkOption(const std::string &option) {
    if (option.find_first_not_of("-csth?") != std::string::npos) {
        _argv.pop();
        if (option.find_first_not_of("-csth?") != std::string::npos || option.size() <= 2) {
            if ((option == "-?" || option == "-h") && _argv.empty())
                return printCliHelp();
            else if (option == "-s" && _stop)
                return sendSignal(_argv.front());
            else if (option == "-t" || (option == "-c" && !_stop))
                return checkFile(_argv.front());
        }
        throw std::runtime_error("Option Invalid");
    }
}

void Cli::sendSignal(const std::string &command) const {
    if (command == "stop")
        kill(_pid, SIGTERM);
    else if (command == "reload")
        kill(_pid, SIGHUP);
    else if (command == "exit")
        kill(_pid, SIGINT);
    else
        throw std::runtime_error("commande signal invalide");
}

void Cli::checkFile(const std::string &pathFile) const {
    int positionPathFileConfig = (argc == 2) ? 0 : 2;
    std::string pathConfigFile(selectPath(argv, positionPathFileConfig));

    try {
        PegParser<ConfigFile> peg(pathConfigFile.c_str(), "#");
//        Token     token;
//        Config webserv(token);
//        ConfigFile extractConfigFile(webserv, peg);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "webserv: configuration file " << pathConfigFile << " test failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "webserv: configuration file " << pathConfigFile << " test is successful" << std::endl;
    exit(EXIT_SUCCESS);

}
void Cli::printCliHelp(){
    std::cerr << "Webserv usage : webserv [-csth?] [-c file] [-s signal] [-t file]\n"
              << "\t\t-c file' Use an alternative configuration file.\n"
              << "\t\t-t' Don't run, just test the configuration file.\n"
              << "\t\t-s signal' Send signal to the master process.\n"
              << "\t\tstop' SIGTERM\n"
              << "\t\tquit' SIGQUIT\n"
              << "\t\treload' SIGHUP\n"
              << "\t\t-? | -h'               Print help."<< std::endl;
}

void Cli::handleExit(int sig) {
    if (sig == SIGINT){
        kill(_this->_pid, SIGTERM);
    }
    std::cout << "exit by signal" << std::endl;
    exit(EXIT_SUCCESS);
}

void Cli::handleStop(int sig) {
    if (sig == SIGTERM){
        _this->_stop = true;
    }
    std::cout << "Stop by signal" << std::endl;
}

void Cli::handleReload(int sig) {
    if (sig == SIGHUP){
        if (_this->_launch)
            kill(_this->_pid, SIGTERM);
    }
    std::cout << "Reload by signal" << std::endl;
    exit(EXIT_SUCCESS);
}

bool Cli::isStop() const {
    return _stop;
}

bool Cli::isLaunch() const {
    return _launch;
}

int Cli::getStatus() const {
    return _status;
}

pid_t Cli::getPid() const {
    return _pid;
}
