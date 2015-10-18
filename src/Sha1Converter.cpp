#include "Sha1Converter.hpp"
#include <fstream>
#include <cstring>
#include <iomanip>
#include <iostream>

std::string sha1_converter(const std::string &file_path)
{
    std::basic_ifstream <char> in_file(file_path, std::ios::binary | std::ios::in);
    std::string result_code;

    if (in_file.is_open())
    {
        in_file.seekg(0, in_file.end);
        long int file_length = in_file.tellg();
        in_file.seekg(0, in_file.beg);

        char * buffer = new char [file_length];
        unsigned char result[20];

        in_file.read(buffer, file_length);

        SHA1((unsigned char*)&buffer, file_length, result);

        delete []buffer;

        return std::string(reinterpret_cast<char*>(result));
    }

    return result_code;
}