//
// Created by Jean-benoit Rossignol on 8/29/23.
//

#include <Source_Code/4.3-Setter/Includes/Setter.class.hpp>

Setter::Setter() {}
Setter::~Setter() {}

std::vector<char*>  Setter::setEnvp(std::vector<std::string> & envVec) {
    std::vector<char*> env;
    for (size_t i = 0; i < envVec.size(); ++i) {
        env.push_back(const_cast<char*>(envVec[i].c_str()));
    }
    env.push_back(NULL);
    return env;
}

std::vector<char*>  Setter::setPhpEnv(const std::string& method, const std::string& query,
                                      std::map<std::string, std::string>& headers) {
    std::vector<std::string> envVec;

    envVec.push_back("REQUEST_METHOD=" + method);
    if (!query.empty()) {
        envVec.push_back("QUERY_STRING=" + query);
    }
    for (std::map<std::string, std::string>::iterator it = headers.begin();
    it != headers.end(); ++it) {
        std::string envVar = "HTTP_" + it->first;
        std::replace(envVar.begin(), envVar.end(), '-', '_');
        std::transform(envVar.begin(), envVar.end(), envVar.begin(), ::toupper);
        envVar += "=" + it->second;
        envVec.push_back(envVar);
    }
    return Setter::setEnvp(envVec);
}

std::vector<char*> Setter::setArgv(const std::string& executablePath, const std::string& filePath){
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>(executablePath.c_str()));
    argv.push_back(const_cast<char*>(filePath.c_str()));
    argv.push_back(NULL);

    return argv;
}