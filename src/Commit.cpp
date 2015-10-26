#include "Commit.hpp"

Commit::Commit()
{

}

void Commit::add_files(const std::vector <CommitFile> &commit_files)
{
    m_commit_files.insert(m_commit_files.end(), commit_files.begin(), commit_files.end());
    m_hash_code_commit.set_hash_code_by_list(commit_files);
}

void Commit::add_to_storage() const
{
    for(CommitFile commit_file : m_commit_files)
        commit_file.add_to_storage();
}

void Commit::set_parent_hash_code_commit(const HashCodeType parent_commit_type)
{
    m_parent_hash_code = parent_commit_type;
}

HashCodeType Commit::get_hash_code() const
{
    return m_hash_code_commit;
}