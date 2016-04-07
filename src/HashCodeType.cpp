#include "Commit.hpp"
#include "HashCodeType.hpp"
#include <fstream>

HashCodeType::HashCodeType()
    : _hash_code(), _valid_feature(true)
{
}

Sha256 HashCodeType::hash_code() const
{
    return _hash_code;
}

bool HashCodeType::is_valid() const
{
    return _valid_feature;
}

void HashCodeType::set_valid(bool state_valid_flag)
{
    _valid_feature = state_valid_flag;
}

void HashCodeType::set_hash_code(const boost::filesystem::path &file_path)
{
    std::ifstream file(file_path.string(), std::ios::binary);
    _hash_code = encode_content_file(file);
}

void HashCodeType::set_hash_code_by_list(const std::vector<class CommitFile> &commits, const HashCodeType &code)
{
    _hash_code = encode_contents_list(commits);
    _hash_code = add_hash_code(_hash_code, code.hash_code());
}
