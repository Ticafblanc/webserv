#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

int main(int argc, char** argv) {
    (void)argc;
    std::ifstream inputFile(argv[1]);
    std::stringstream inputContent;
    if (inputFile.is_open()) {
        inputContent << inputFile.rdbuf();
        inputFile.close();
    } else {
        std::cout << "Failed to open inputFile file: " << argv[1] << std::endl;
        return 1;
    }
    std::ifstream expectedOutputFile(argv[2]);
    std::stringstream expectedOutputContent;
    if (expectedOutputFile.is_open()) {
        expectedOutputContent << expectedOutputFile.rdbuf();
        expectedOutputFile.close();
    } else {
        std::cout << "Failed to open expected output file: " << argv[2] << std::endl;
        return 1;
    }
    std::string input;
    std::string expected;
    inputContent >> input >> std::ws;//remove PID
    while (!expectedOutputContent.eof()){
        inputContent >> input >> std::ws;
        expectedOutputContent >> expected >> std::ws;
        if (expected == " " || expected == "Socket" || expected == "Token"){
            std::getline(inputContent, input, '\n');
            std::getline(expectedOutputContent, expected, '\n');
            continue;
        }
        if (input.size() != expected.size()){
            input = input.substr(input.find_first_not_of(' '), input.find_last_not_of(' ') - input.find_first_not_of(' ') + 1);
            expected = expected.substr(expected.find_first_not_of(' '), expected.find_last_not_of(' ') - expected.find_first_not_of(' ') + 1);
        }
        if (input != expected) {
            std::cout << "Test Failed!" << std::endl;
            std::cout << "Expected Output: " << expected<< std::endl;
            std::cout << "Actual Output: " << input << std::endl;
            return 1;
        }
    }
    std::cout << "Test Passed!" << std::endl;
    return 0;
}