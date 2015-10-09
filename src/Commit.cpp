//
// Created by mikhail on 10/10/15.
//

#include "../include/Commit.hpp"

Commit::Commit()
{

}

Commit::Commit(const std::list <CommitFile> &commit_files)
{
    //m_hash_code_commit = "abcd";
    //m_parent_hash_code = "bcde";
    m_meta_info        = "meta info";
    m_commit_files = commit_files;
}

void Commit::add_files(const std::list<CommitFile> &commit_files)
{
    // ?
    m_commit_files.insert(m_commit_files.end(), commit_files.begin(), commit_files.end());
}

void Commit::set_parent_commit(const HashCodeType parent_commit_type)
{
    m_parent_hash_code = parent_commit_type;
}
