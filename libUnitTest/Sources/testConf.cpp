#include <iostream>
#include <fstream>
#include <cstdlib>

int main(int argc, char** argv) {
    (void)argc;
    std::ifstream input(argv[1]);
    std::string inputContent;
    if (input.is_open()) {
        std::getline(input, inputContent);
        input.close();
    } else {
        std::cout << "Failed to open input file: " << argv[1] << std::endl;
        return 1;
    }
    std::ifstream expectedOutput(argv[2]);
    std::string expectedOutputContent;
    if (expectedOutput.is_open()) {
        std::getline(expectedOutput, expectedOutputContent);
        expectedOutput.close();
    } else {
        std::cout << "Failed to open expected output file: " << argv[2] << std::endl;
        return 1;
    }
    if (inputContent == expectedOutputContent) {
        std::cout << "Test Passed!" << std::endl;
    } else {
        std::cout << "Test Failed!" << std::endl;
        std::cout << "Expected Output: " << expectedOutputContent << std::endl;
        std::cout << "Actual Output: " << inputContent << std::endl;
    }

    return 0;
}