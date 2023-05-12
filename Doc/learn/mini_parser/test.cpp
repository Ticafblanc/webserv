#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
int main (int argc, char *argv[]) {
  std::string  arg(argv[1]);
  std::ifstream   file(argv[1]);
  std::string     line;
  std::string     key, value, indente;
  std::string            c = "\t";
  bool             flag;

  while (std::getline(file, line)) {
        key.clear(); value.clear();
        std::istringstream string_stream(line);
        string_stream >> key >> std::ws;
        if (!key.empty() && !(key[0] == '#')){
            if(key == "}"){
              indente.pop_back();
            }
            std::cout << indente << "" << key << std::endl;
            flag = true;
            while (flag){
              usleep(1000);
              string_stream >> value >> std::ws;
              // string_stream >> value >> std::ws;
              if (*(value.end() - 1) == ';' || value.empty()){
                flag = false;
                value.pop_back();
              }
              if(value == "{"){
                flag = false;
                indente += c;
              }
              std::cout << indente << "" << value << std::endl;
            }
        }
  }
  return 0;
}
