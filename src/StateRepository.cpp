#include "StateRepository.hpp"

#include <fstream>
#include <algorithm>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

StateRepository::StateRepository()
{
}

StateRepository::~StateRepository()
{
}

void StateRepository::status() const
{
    std::cerr << "Status of repository:" << std::endl;

    for (auto it : _current_files)
    {
        std::cout << it.first << std::endl;
    }
}

void StateRepository::apply_commit(Commit& commit)
{
    _current_commit = commit;

    for (size_t index = 0; index < commit.files_amount(); index++)
    {
        std::string cur_file = commit.get_file_name(index);

        if (is_file_exists(cur_file) && !commit.get_prev_file_hash(index).is_valid())
        {
            delete_file(cur_file);
            LOG << "deleting " << cur_file << std::endl;
            continue;
        }

        update_file(cur_file, commit.get_file_hash(index));
    }
}

void StateRepository::cancel_commit(Commit& prev_commit)
{
    for (size_t index = 0; index < _current_commit.files_amount(); index++)
    {
        std::string cur_file = _current_commit.get_file_name(index);
        HashCodeType prev_file_hash = _current_commit.get_prev_file_hash(index);

        if (is_file_exists(cur_file))
        {
            if (prev_file_hash.is_valid())
            {
                update_file(cur_file, prev_file_hash);
            } else
            {
                delete_file(cur_file);
            }
        } else
        {
            update_file(cur_file, get_file_hash(cur_file));
        }

    }

    _current_commit = prev_commit;

}

void StateRepository::update_file(std::string file_path, HashCodeType file_hash)
{
    _current_files[file_path] = file_hash;
}

void StateRepository::delete_file(std::string file_path)
{
    _current_files.erase(file_path);
}

bool StateRepository::is_file_exists(std::string file_path)
{
    return _current_files.count(file_path);
}

HashCodeType StateRepository::get_file_hash(std::string file_path)
{
    return _current_files[file_path];
}


