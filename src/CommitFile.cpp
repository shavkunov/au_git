//
// Created by mikhail on 10/10/15.
//

#include "../include/CommitFile.hpp"

CommitFile::CommitFile(const std::string &filename)
        : m_filename(filename)
{
}

std::string CommitFile::filename() const
{
    return m_filename;
}

HashCodeType CommitFile::hash_code_file() const
{
    return m_hash_code_file;
}

void CommitFile::set_remove_flag()
{
    m_hash_code_file.set_valid(false);
}