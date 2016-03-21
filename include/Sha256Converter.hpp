#ifndef AU_GIT_SHA256CONVERTER_HPP
#define AU_GIT_SHA256CONVERTER_HPP

#include <boost/serialization/access.hpp>
#include <string>
#include <vector>
#include "Commit.hpp"

class Sha256
{
public:
    Sha256() : bytes() {}

    static const int kSize = 32;
    uint8_t bytes[kSize];

    std::string to_string() const;

private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
        for(size_t i = 0; i < Sha256::kSize; ++i)
            ar & bytes[i];
    }
};

//
Sha256 calculate_sha256(const uint8_t* bytes, size_t length);

//
Sha256 encode_content_file(std::ifstream &in);

//
Sha256 encode_contents_list(const std::vector<CommitFile> &commits);

//
Sha256 add_hash_code(const Sha256 &code_first, const Sha256 &code_second);

#endif //AU_GIT_SHA256CONVERTER_HPP
