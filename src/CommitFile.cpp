//
// Created by mikhail on 10/10/15.
//

#include "../include/CommitFile.hpp"

CommitFile::CommitFile(const std::string &filename)
        : m_file(filename), m_timestamp(std::time_t(0))
{
}

std::string CommitFile::filename() const
{
    return m_file.filename().string();
}

HashCodeType CommitFile::hash_code_file() const
{
    return m_hash_code_file;
}

void CommitFile::set_remove_flag()
{
    m_hash_code_file.set_valid(false);
}