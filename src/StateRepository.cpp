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

void StateRepository::set_commit(Commit commit)
{
    _current_commit = commit;
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


