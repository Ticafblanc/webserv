
#include <Includes/Cli.class.hpp>

Cli* Cli::_this = NULL;

Cli::Cli(int argc, char ** argv)
: _pid(getpid()), _status(EXIT_SUCCESS), _exit(true), _run(false), _argv()/*, _config(*/{
    _this = this;
    initSignal();
    if (argc > 3) {
        std::cerr << "Too much arguments" << std::endl;
        _status = EXIT_FAILURE;
        return;
    }
    try{
        _exit = isMainProgram();
        setArg(argc, argv);
        checkArg();
    }catch (const std::exception & e){
        std::cerr << "\n" << e.what() << std::endl;
//        printCliHelp();
        _status = EXIT_FAILURE;
        _exit = true;
    }
}

Cli::~Cli() {}

Cli::Cli(const Cli & other)
: _pid(other._pid), _status(other._status), _exit(other._exit), _run(other._run), _argv(other._argv)/*, _config(other._config)*/ {}

Cli &Cli::operator=(const Cli & rhs) {
    if (this != &rhs){
    }
    return *this;
}

bool Cli::isMainProgram(){
    std::ifstream ifs;
    ifs.open(_PATHTOPIDLOGFILE_, std::ios::in | std::ios::out | std::ios::app);
    if (!ifs.is_open())
        throw std::runtime_error("impossible to open pid.log");
    std::vector<char> pidVec(100);
    ifs.getline(pidVec.data(),100);
    std::stringstream ss(pidVec.data());
    pid_t pid = 0;
    ss >> pid;
    if (pid == 0){
        std::cout << "Welcome to Webserv !!\n";
        return false;
    }
    std::cout << "Webserv already open!!\n";
    if (!TESTMODE)
        _pid = pid;
    return true;
}

void Cli::initSignal() {
    std::signal(SIGTERM, handleExit);//webserv -s quit
    std::signal(SIGINT, handleExit);//webserv -s quit
    std::signal(LAUNCH, handleLaunch);//webserv
    std::signal(STOP, handleStop);//webserv
    std::signal(SIGHUP, handleReload);//webserv -s reload
}

void Cli::setArg(int argc, char ** argv){
    for (int i = 1; i < argc && i < 3; ++i) {
        std::istringstream iss(argv[i]);
        std::string str;
        while (!iss.eof()) {
            iss >> std::ws >> str;
            if (!str.empty())
                _argv.push(str);
            str.clear();
            if (TESTMODE)
                std::cout << "set arg : " << _argv.back()  << " arg size : " << _argv.size()<< std::endl;
        }
    }
}

void Cli::checkArg() {
    if (!_exit && _argv.empty())
        checkFile("");
    else if (!_argv.empty() && _argv.size() <= 2) {
        if (TESTMODE)
            std::cout << "check arg : " << _argv.front() << std::endl;
        if (_argv.front()[0] == '-')
            checkOption(_argv.front());
        else
            checkFile(_argv.front());
        if (_argv.empty())
            return;
    }else {
        throw std::runtime_error("To much argument");
    }
}

void Cli::checkOption(const std::string &option) {
    if (TESTMODE)
        std::cout << "check option : " << option << " option size : " << option.size()<< std::endl;
    if (option.find_first_not_of("-csth?") == std::string::npos) {
        _argv.pop();
        if (option.find_first_not_of("-csth?") != std::string::npos || option.size() <= 2) {
            if ((option == "-?" || option == "-h") && _argv.empty())
                return printCliHelp();
            else if (option == "-s" && _exit)
                return sendSignal(_argv.front());
            else if (option == "-t" || (option == "-c" && !_exit))
                return checkFile(_argv.front());
        }
        throw std::runtime_error("Option Invalid");
    }
}

void Cli::sendSignal(const std::string &command) const {
    if (TESTMODE) {
        std::cout << "send Signal : " << command << std::endl;
    }
    if (command == "stop") {
        if (kill(_pid, STOP) != 0)
            throw std::runtime_error(strerror(errno));
    }
    else if (command == "reload") {
        if (kill(_pid, SIGHUP) != 0)
            throw std::runtime_error(strerror(errno));
    }
    else if (command == "quit") {
        if (kill(_pid, SIGINT) != 0)
            throw std::runtime_error(strerror(errno));
    }
    else
        throw std::runtime_error("commande signal invalide");
}

void Cli::checkFile(const std::string &pathFile) {
    if (TESTMODE)
        std::cout << "check File : " << pathFile << std::endl ;
    if (pathFile.empty())
        _pathToConfigFile = "/webserv/Docker_build/etc/webserv/webserv.conf"; //"/usr/local/etc/webserv/webserv.conf"
    else{
        if (isFile(pathFile) && pathFile.find_last_of(".conf") != std::string::npos)
            _pathToConfigFile = pathFile;
        else
            throw std::runtime_error(pathFile + " is not config file");
    }
}

void Cli::printCliHelp(){
    std::cout << "Webserv usage : webserv [-csth?] [-c file] [-s signal] [-t file]\n"
              << "\t\t-c file' Use an alternative configuration file.\n"
              << "\t\t-t' Don't run, just test the configuration file.\n"
              << "\t\t-s signal' Send signal to the master process.\n"
              << "\t\tstop' SIGTERM\n"
              << "\t\tquit' SIGQUIT\n"
              << "\t\treload' SIGHUP\n"
              << "\t\t-? | -h'               Print help."<< std::endl;
}

void Cli::handleExit(int sig) {
    if (sig == SIGINT || sig == SIGTERM) {
        if (TESTMODE)
            std::cout << "exit by signal" << std::endl;
        _this->_exit = true;
        kill(_this->_pid, STOP);

    }
}

void Cli::handleStop(int sig) {
    if (sig == SIGUSR2){
        if (TESTMODE)
            std::cout << "Stop by signal" << std::endl;
        std::signal(LAUNCH, handleLaunch);
        _this->_run = false;
    }
}

void Cli::handleLaunch(int sig) {
    if (sig == SIGUSR1){
        if (TESTMODE)
            std::cout << "launck by signal" << std::endl;
        std::signal(STOP, handleStop);

    }
}

void Cli::handleReload(int sig) {
    if (sig == SIGHUP) {
        if (TESTMODE)
            std::cout << "Reload by signal" << std::endl;
        kill(_this->_pid, STOP);
    }
}

bool Cli::isStop() const {
    return _exit;
}

void Cli::setRun() {
    _run = true;
}

bool Cli::isLaunch() const {
    return _run;
}

int Cli::getStatus() const {
    return _status;
}

pid_t Cli::getPid() const {
    return _pid;
}
