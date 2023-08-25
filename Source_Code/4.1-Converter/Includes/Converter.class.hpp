//
// Created by Ben on 2023-08-22.
//

#ifndef WEBSERVER_CONVERTER_CLASS_HPP
#define WEBSERVER_CONVERTER_CLASS_HPP

#include <map>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <filesystem>

class Converter {
public:

    /**
     * Constructor of converter class
     *
     * @param void
     */
    Converter();

    /**
     * Destructor of converter class
     *
     * @throw nothing
     */
    ~Converter();

    /**
     * Public method of converter class
     *
     * convert an integer to a std::string
     *
     * @param number
     * @return std::string of the number converted.
     */
    static std::string intToString(int number);

    /**
     * Public method of converter class
     *
     * convert an hexadecimal string to a size_t value
     *
     * @param hexString
     * @return size_t of the string converted.
     */
    static std::size_t hexStringToSizet(const std::string & hexString);

    /**
     * Public method of converter class
     *
     * convert a size_t value to an hexadecimal string
     *
     * @param size
     * @return std::string of the size_t converted
     */
    static std::string sizetToHexString(std::size_t size);
};

#endif //WEBSERVER_CONVERTER_CLASS_HPP
