

#ifndef WEBSERVER_CLI_HPP
#define WEBSERVER_CLI_HPP

#include "../../4-Utils/Includes/Utils.hpp"
#include "../../1-Config/Includes/ConfigFile.class.hpp"

#define LAUNCH SIGUSR1
#define STOP SIGUSR2


class Cli {

  /*>***************************private section******************************/

private:
  /*
   *============================================================================
   *|                                  Member
   *============================================================================
   */
  static Cli *_this;
  pid_t _pid;
  int _status;
  volatile sig_atomic_t _exit;
  volatile sig_atomic_t _run;
  queue<std::string> _argv;
  string _pathToConfigFile;
  Config _config;
  /*
   *============================================================================
   *|                                  Methode |
   *============================================================================
   */
  void setArg(int argc, char **argv);
  void checkArg();
  static void printCliHelp();
  bool isMainProgram();
  void checkOption(const std::string &option);
  void sendSignal(const std::string &command) const;
  void checkFile(const std::string &pathFile);
  void checkConfig();
  static void initSignal();
  static void handleReload(int sig);
  static void handleExit(int sig);
  static void handleStop(int sig);
  static void handleLaunch(int sig);
  static void clearPidFile();

  /*>********************************public
   * section**********************************/

public:
  /*
   *====================================================================================
   *|                                      Fonction |
   *====================================================================================
   */

  /**
   * Constructor of Cli class
   *
   * Cli();
   *
   * @param   pathToCliFile
   * @throw   none
   **/
  Cli(int argc, char **argv);

  /**
   * Destructor of Cli class
   *
   * ~Cli();
   *
   * @throw   none
   **/
  virtual ~Cli();

  /**
   * Copy constructor of Cli class
   *
   *     Cli(const Cli &);
   *
   * @param   Cli instance
   * @throw   none
   **/
  Cli(const Cli &);

  /**
   * Operator overload= of Cli class
   *
   * Cli& operator=(const Cli &);
   *
   * @param   Cli
   * @throw   none
   **/
  Cli &operator=(const Cli &);

  /*
   *====================================================================================
   *|                                      Methode |
   *====================================================================================
   */

  int getStatus() const;

  bool isStop() const;

  bool isLaunch() const;

  pid_t getPid() const;

  void setRun();
};

#endif
