//
// Created by mikhail on 10/10/15.
//

#include "../include/Commit.hpp"
#include "../include/CommitException.hpp"

Commit::Commit()
{

}

void Commit::add_files(const std::list<CommitFile> &commit_files)
{
    //for(CommitFile current_commit_file : commit_files)
    {
        //if (!boost::filesystem::exists(current_commit_file.filename()))
        {
            ;//throw FileIsNotFoundException("File is not found");
        }
    }
    // ?
    m_commit_files.insert(m_commit_files.end(), commit_files.begin(), commit_files.end());
}

void Commit::set_parent_commit(const HashCodeType parent_commit_type)
{
    m_parent_hash_code = parent_commit_type;
}

HashCodeType Commit::get_hash_code() const
{
    return m_hash_code_commit;
}