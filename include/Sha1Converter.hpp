#ifndef AU_GIT_SHA1CONVERTER_HPP
#define AU_GIT_SHA1CONVERTER_HPP

#include <openssl/sha.h>
#include <string>

std::string sha1_converter(const std::string &file_path);

#endif //AU_GIT_SHA1CONVERTER_HPP
