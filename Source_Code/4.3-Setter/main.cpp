//
// Created by Jean-benoit Rossignol on 8/29/23.
//
#include <Source_Code/4.3-Setter/Includes/Setter.class.hpp>
#include <iostream>

int main (int argc, char **argv, char **envp) {
    argv[0][0] = 'a';
    std::cout << argc << '\n' << std::endl;
    std::vector<char*> charVec;
    std::vector<std::string> stringVec;
    for(int i = 0; envp[i]; i++) {
        std::string envpString = envp[i];
        stringVec.push_back(envpString);
    }
    charVec = Setter::setEnvp(stringVec);
    std::vector<char*>::iterator it;
    for (it = charVec.begin(); it < charVec.end(); it++){
        std::cout << *it << std::endl;
    }
    return (0);
}