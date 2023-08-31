//
// Created by Jean-benoit Rossignol on 8/29/23.
//
#include <Source_Code/4.3-Setter/Includes/Setter.class.hpp>
#include <iostream>

int main (int argc, char **argv, char **envp) {
    (void)argc;
    (void)argv;
    std::vector<char*> charVec;
    std::vector<std::string> stringVec;
    for(int i = 0; envp[i]; i++) {
        std::string envpString = envp[i];
        stringVec.push_back(envpString);
    }
    charVec = Setter::setEnvp(stringVec);
    std::vector<char*>::iterator it = charVec.begin();
    for (int i = 0; it < charVec.end(); i++, it++){
        if (*it == NULL)
            break;
        std::string checkIt = *it;
        if (checkIt.compare(envp[i]) == 0)
            std::cout << *it << std::endl;
        else
            return (1);
    }
    return (0);
}