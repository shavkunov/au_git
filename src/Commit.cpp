#include "Commit.hpp"
#include "RepositoryException.hpp"

#include <boost/format.hpp>

Commit::Commit() {}

void Commit::add_files(const std::vector <CommitFile> &commit_files)
{
    _commit_files.insert(_commit_files.end(), commit_files.begin(), commit_files.end());
    _hash_code_commit.set_hash_code_by_list(commit_files, _parent_hash_code);
}

void Commit::set_parent_hash_code_commit(const HashCodeType parent_commit_type)
{
    _parent_hash_code = parent_commit_type;
}

void Commit::set_prev_file_hash(HashCodeType hash, size_t index)
{
    _commit_files[index].set_prev_file_hash(hash);
}

void Commit::set_file_hash(HashCodeType file_hash, size_t index)
{
    _commit_files[index].set_file_hash(file_hash);
}

HashCodeType Commit::get_hash_code() const
{
    return _hash_code_commit;
}

std::string Commit::get_file_name(size_t index) const
{
    return _commit_files[index].get_file_name();
}

HashCodeType Commit::get_file_hash(size_t index) const
{
    return _commit_files[index].get_file_hash();
}

HashCodeType Commit::get_prev_file_hash(size_t index)
{
    return _commit_files[index].get_prev_file_hash();
}

size_t Commit::files_amount() const
{
    return _commit_files.size();
}

bool Commit::operator==(const Commit &a)
{
    return _hash_code_commit.hash_code().to_string() == a._hash_code_commit.hash_code().to_string();
}

const std::string Commit::hash_code() const
{
    return _hash_code_commit.to_string();
}

Commit Commit::create_commit_by_list(const std::vector<std::string> &files)
{
    Commit commit;
    std::vector<CommitFile> commit_files;
    commit_files.reserve(files.size());

    for (size_t i = 0; i < files.size(); i++)
    {
        if (!boost::filesystem::exists(files[i]))

        {
            std::string message = boost::str(boost::format("File [%1%] is not found!") % files[i]);
            throw FileIsNotFoundException(message.c_str());
        }

        HashCodeType hash;
        hash.set_hash_code(files[i]);
        std::time_t time = boost::filesystem::last_write_time(files[i]);
        CommitFile file(files[i], hash, time);
        commit_files.push_back(file);
    }

    commit.add_files(commit_files);

    return commit;
}
