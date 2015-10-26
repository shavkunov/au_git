#include "Sha1Converter.hpp"
#include "CommitFile.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

std::string Sha256::to_string() const
{
    std::stringstream stream;
    for(size_t i = 0; i < Sha256::kSize; ++i)
        stream << std::hex << static_cast <int>(bytes[i]);
    return stream.str();
}

Sha256 calculate_sha256(uint8_t const * bytes, size_t length)
{
    Sha256 res;

    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, bytes, length);
    SHA256_Final(res.bytes, &sha256_ctx);

    return res;
}

Sha256 encode_content_file(std::ifstream &in)
{
    in.seekg(0, in.end);
    uint32_t file_length = in.tellg();
    in.seekg(0, in.beg);
    uint8_t *bytes = new uint8_t [file_length];
    in.read((char*)bytes, file_length * sizeof(bytes[0]));
    Sha256 result_code = calculate_sha256(bytes, file_length);
    delete []bytes;
    return result_code;
}

Sha256 encode_contents_list(const std::vector <CommitFile> &commits)
{
    Sha256 res;

    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);

    for(size_t i = 0; i < commits.size(); ++i)
    {
        SHA256_Update(&sha256_ctx, commits[i].hash_code_file().hash_code().bytes, Sha256::kSize);
    }

    SHA256_Final(res.bytes, &sha256_ctx);

    return res;
}