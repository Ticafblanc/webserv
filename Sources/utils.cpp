//
// Created by Matthis DoQuocBao on 2023-05-28.
//

#include "../Include/webserv.hpp"

static std::map<std::string, std::string> parseJson(const std::string& json_data) {
    std::map<std::string, std::string> data;

    std::size_t start_position = json_data.find_first_of("\"");
    while (start_position != std::string::npos) {
        std::size_t end_position = json_data.find_first_of("\"", start_position + 1);
        if (end_position != std::string::npos) {
            std::size_t code_position = json_data.find_first_of("\"", end_position + 1);
            if (code_position != std::string::npos) {
                std::string code = json_data.substr(start_position + 1, end_position - start_position - 1);
                std::size_t message_position = json_data.find_first_of("\"", code_position + 1);
                if (message_position != std::string::npos) {
                    std::string message = json_data.substr(code_position + 1, message_position - code_position - 1);
                    data[code] = message;
                }
            }
        }

        start_position = json_data.find_first_of("\"", start_position + 1);
    }

    return data;
}