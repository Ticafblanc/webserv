
#include "../Includes/Cli.class.hpp"

Cli *Cli::_this = NULL;

Cli::Cli(int argc, char **argv)
    : _pid(getpid()), _status(EXIT_SUCCESS), _exit(true), _run(false), _argv(),
      _config() {
  _this = this;
  initSignal();
  if (argc > 3) {
    cerr << "Too much arguments" << endl;
    _status = EXIT_FAILURE;
    return;
  }
  try {
    setArg(argc, argv);
    checkArg();
  } catch (const exception &e) {
    cerr << e.what() << endl;
    printCliHelp();
    _status = EXIT_FAILURE;
  }
}

Cli::~Cli() {}

Cli::Cli(const Cli &other)
    : _pid(other._pid), _status(other._status), _exit(other._exit),
      _run(other._run), _argv(other._argv), _config(other._config) {}

Cli &Cli::operator=(const Cli &rhs) {
  if (this != &rhs) {
  }
  return *this;
}

bool Cli::isMainProgram() {
  fstream fs;
  fs.open(PATH_TO_PID_LOG_FILE_, fstream::in | fstream::out | fstream::app);
  if (!fs.is_open())
    throw runtime_error("impossible to open pid.log");
  fs.seekg(0, ios::end);
  bool isEmpty = (fs.tellg() == 0);
  if (isEmpty) {
    fs << _pid;
    fs.close();
    return true;
  }
  fs.seekg(0, ios::beg);
  string str;
  getline(fs, str);
  fs.close();
  istringstream(str) >> _pid;
  cout << "Webserv already open!!\nOn : [" << _pid << "]" << endl;
  return false;
}

void Cli::initSignal() {
  signal(SIGTERM, handleExit);  // webserv -s quit
  signal(SIGINT, handleExit);   // webserv -s quit
  signal(LAUNCH, handleLaunch); // webserv
  signal(SIGHUP, SIG_IGN);
}

void Cli::setArg(int argc, char **argv) {
  for (int i = 1; i < argc && i < 3; ++i) {
    istringstream iss(argv[i]);
    string str;
    while (!iss.eof()) {
      iss >> ws >> str;
      if (!str.empty())
        _argv.push(str);
      str.clear();
    }
  }
}

void Cli::checkArg() {
  if (!_exit && _argv.empty())
    checkFile("");
  else if (!_argv.empty() && _argv.size() <= 2) {
    if (_argv.front()[0] == '-')
      checkOption(_argv.front());
    else
      checkFile(_argv.front());
  } else {
    throw runtime_error("To much argument");
  }
}

void Cli::checkOption(const string &option) {
  if (option.find_first_not_of("-csth?") == string::npos) {
    _argv.pop();
    if (option.find_first_not_of("-csth?") != string::npos ||
        option.size() <= 2) {
      if ((option == "-?" || option == "-h") && _argv.empty())
        return printCliHelp();
      else if (option == "-s" && _exit)
        return sendSignal(_argv.front());
      else if (option == "-t" || (option == "-c" && !_exit))
        return checkFile(_argv.front());
    }
    throw runtime_error("Option Invalid");
  }
}

void Cli::sendSignal(const string &command) const {
  if (!_this->isMainProgram()) {
    if (command == "start") {
      cout << "Start signal" << endl;
      if (kill(_pid, LAUNCH) != 0)
        throw runtime_error(strerror(errno));
    } else if (command == "stop") {
      cout << "Stop signal" << endl;
      if (kill(_pid, STOP) != 0)
        throw runtime_error(strerror(errno));
    } else if (command == "reload") {
      cout << "Reload signal" << endl;
      if (kill(_pid, SIGHUP) != 0)
        throw runtime_error(strerror(errno));
    } else if (command == "quit") {
      cout << "Quit signal" << endl;
      if (kill(_pid, SIGINT) != 0)
        throw runtime_error(strerror(errno));
    } else
      throw runtime_error("commande signal invalide");
  } else
    throw runtime_error("commande signal impossible on main programme");
}

void Cli::checkFile(const string &pathFile) {
  if (pathFile.empty())
    _pathToConfigFile = "webserv.conf";
  if (isFile(pathFile) && pathFile.find_last_of(".conf") != string::npos)
    _pathToConfigFile = pathFile;
  else
    throw runtime_error(pathFile + " is not config file");
  checkConfig();
}

void Cli::checkConfig() {
  try {
    PegParser<ConfigFile> peg(_pathToConfigFile, "#");
    ConfigFile extractConfigFile(_config, peg);
  } catch (const std::exception &e) {
    std::cout << "8-ConfigFile error on => " << e.what() << std::endl;
    throw runtime_error("error in config file");
  }
}

void Cli::printCliHelp() {
  if (_this->_exit) {
    _this->_exit = true;
    clearPidFile();
  }
  cout << "Webserv usage : webserv [-csth?] [-c file] [-s signal] [-t file]\n"
       << "\t\t-c file' Use an alternative configuration file.\n"
       << "\t\t-t' Don't run, just test the configuration file.\n"
       << "\t\t-s signal' Send signal to the master process.\n"
       << "\t\tstart' LAUNCH\n"
       << "\t\tstop' SIGTERM\n"
       << "\t\tquit' SIGQUIT\n"
       << "\t\treload' SIGHUP\n"
       << "\t\t-? | -h'               Print help." << endl;
}

void Cli::clearPidFile() {
  std::ofstream file(PATH_TO_PID_LOG_FILE_, std::ofstream::trunc);
  if (!file.is_open())
    std::cerr << "fail to open file " << PATH_TO_PID_LOG_FILE_ << std::endl;
  else
    file.close();
}

void Cli::handleExit(int sig) {
  if (sig == SIGINT || sig == SIGTERM) {
    if (!_this->isStop()) {
      cout << "Quit server" << endl;
      clearPidFile();
      _this->_exit = true;
    }
    kill(_this->_pid, STOP);
  }
}

void Cli::handleStop(int sig) {
  if (sig == STOP) {
    if (!_this->isLaunch()) {
      _this->setRun();
      cout << "Stop server" << endl;
      signal(LAUNCH, handleLaunch);
      signal(SIGHUP, SIG_IGN);
    }
  }
}

void Cli::handleLaunch(int sig) {
  if (sig == LAUNCH) {
    if (!_this->isLaunch()) {
      _this->setRun();
      cout << "Launch server" << endl;
      signal(STOP, handleStop);
      signal(SIGHUP, handleReload);
    }
  }
}

void Cli::handleReload(int sig) {
  if (sig == SIGHUP) {
    cout << "Reload server" << endl;
    kill(_this->_pid, STOP);
  }
}

bool Cli::isStop() const { return _exit; }

void Cli::setRun() { _run = _run == 0; }

bool Cli::isLaunch() const { return _run; }

int Cli::getStatus() const { return _status; }

pid_t Cli::getPid() const { return _pid; }
