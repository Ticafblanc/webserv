//
// Created by Jean-benoit Rossignol on 8/29/23.
//

#include <Source_Code/4.3-Setter/Includes/Setter.class.hpp>

std::vector<char*>  Setter::setEnvp(std::vector<std::string> & envVec) {
    std::vector<char*> env;
    for (size_t i = 0; i < envVec.size(); ++i) {
        env.push_back(const_cast<char*>(envVec[i].c_str()));
    }
    env.push_back(NULL);
    return env;
}