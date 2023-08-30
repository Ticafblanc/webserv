//
// Created by Jean-benoit Rossignol on 8/29/23.
//

#ifndef WEBSERVER_SETTER_CLASS_HPP
#define WEBSERVER_SETTER_CLASS_HPP

#include <map>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <filesystem>

class Setter {
public:
    /**
     * Constructor of the class setter
     * @param void
     * @throw nothing
     */
    Setter();
    /**
     * Destructor of the class setter
     * @param void
     * @throw nothing
     */
    ~Setter();

    static std::vector<char*>  setEnvp(std::vector<std::string> & envVec);
};

#endif //WEBSERVER_SETTER_CLASS_HPP
