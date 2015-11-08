#include "Commit.hpp"

Commit::Commit()
{
}

void Commit::add_files(const std::vector <CommitFile> &commit_files)
{
    m_commit_files.insert(m_commit_files.end(), commit_files.begin(), commit_files.end());
    m_hash_code_commit.set_hash_code_by_list(commit_files, m_parent_hash_code);
}

void Commit::add_to_storage(const std::string &storage_path) const
{
    for(CommitFile commit_file : m_commit_files)
        commit_file.add_to_storage(storage_path);
}

void Commit::set_parent_hash_code_commit(const HashCodeType parent_commit_type)
{
    m_parent_hash_code = parent_commit_type;
}

HashCodeType Commit::get_hash_code() const
{
    return m_hash_code_commit;
}

bool Commit::operator== (const Commit &a)
{
    return m_hash_code_commit.hash_code().to_string() == a.m_hash_code_commit.hash_code().to_string();
}

const std::string Commit::hash_code() const
{
    return m_hash_code_commit.hash_code().to_string();
}

Commit Commit::create_commit_by_list(const std::string &storage_path, const std::vector<std::string> &files)
{
    Commit commit;
    std::vector <CommitFile> commit_files;
    commit_files.reserve(files.size());
    for(size_t i = 0; i < files.size(); ++i)
        commit_files.push_back(CommitFile(files[i]));
    commit.add_files(commit_files);
    std::cout << commit.hash_code() << std::endl;
    return commit;
}
