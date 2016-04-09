#include "CommitFile.hpp"
#include "Sha256Converter.hpp"

#include <fstream>
#include <iomanip>
#include <sstream>

#include <openssl/sha.h>

std::string Sha256::to_string() const
{
    std::stringstream stream;
    for(size_t i = 0; i < Sha256::kSize; ++i)
        stream << std::hex << static_cast<int>(bytes[i]);
    return stream.str();
}

Sha256 calculate_sha256(const uint8_t* bytes, size_t length)
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

    std::vector<uint8_t> bytes(file_length);
    in.read((char*)&bytes[0], file_length);

    return calculate_sha256(&bytes[0], file_length);
}

Sha256 encode_contents_list(const std::vector<CommitFile> &commits)
{
    Sha256 res;

    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);

    for(size_t i = 0; i < commits.size(); ++i)
        SHA256_Update(&sha256_ctx, commits[i].get_file_hash().hash_code().bytes, Sha256::kSize);
    SHA256_Final(res.bytes, &sha256_ctx);

    return res;
}

Sha256 add_hash_code(const Sha256 &code_first, const Sha256 &code_second)
{
    Sha256 res;
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, code_first.bytes,  Sha256::kSize);
    SHA256_Update(&sha256_ctx, code_second.bytes, Sha256::kSize);
    SHA256_Final(res.bytes, &sha256_ctx);
    return res;
}
