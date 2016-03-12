
#include "HashCodeType.hpp"
#include <fstream>

HashCodeType::HashCodeType()
    : m_hash_code(), m_valid_feature(true)
{
}

Sha256 HashCodeType::hash_code() const
{
    return m_hash_code;
}

bool HashCodeType::is_valid() const
{
    return m_valid_feature;
}

void HashCodeType::set_valid(bool state_valid_flag)
{
    m_valid_feature = state_valid_flag;
}

void HashCodeType::set_hash_code(const boost::filesystem::path &file_path)
{
    std::ifstream file(file_path.string(), std::ios::binary);
    m_hash_code = encode_content_file(file);
}

void HashCodeType::set_hash_code_by_list(const std::vector<CommitFile> &commits, const HashCodeType &code)
{
    m_hash_code = encode_contents_list(commits);
    m_hash_code = add_hash_code(m_hash_code, code.hash_code());
}
