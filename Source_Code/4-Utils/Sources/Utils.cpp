//
// Created by Matthis DoQuocBao on 2023-05-31.
//

#include <Source_Code/4-Utils/Includes/Utils.hpp>


std::string intToString(int number) {
    std::ostringstream oss;
    oss << number;
    return oss.str();
}

char** setEnvp(char **envp) {
    if (envp) {
        std::vector<char *> vecEnvp;
        for (int i = 0; envp[i] != NULL; ++i) {
            char *tmp = strdup(envp[i]);
            vecEnvp.push_back(tmp);
        }
        vecEnvp.push_back(NULL);
        char **newEnvp = new char *[vecEnvp.size()];
        std::copy(vecEnvp.begin(), vecEnvp.end(), newEnvp);
        return newEnvp;
    }
    return NULL;
}