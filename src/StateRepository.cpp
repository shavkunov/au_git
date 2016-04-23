#include "StateRepository.hpp"

#include <fstream>
#include <algorithm>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

StateRepository::StateRepository()
{
    if (!_repository_path.empty())
        deserialize();
}

StateRepository::~StateRepository()
{
    if (!_repository_path.empty())
        serialize();
}

void StateRepository::set_commit(Commit &commit)
{
    _current_commit = commit;
}

void StateRepository::add_file(std::string file_path)
{
    path_saver tmp(file_path);
    _current_files.push_back(tmp);
}

void StateRepository::fix_duplicate()
{
    sort(_current_files.begin(), _current_files.end());
    _current_files.erase(unique(_current_files.begin(), _current_files.end() ), _current_files.end());
}

void StateRepository::serialize()
{
    boost::filesystem::path out_path = _repository_path / repository_state_path;
    std::ofstream out(out_path.string());

    boost::archive::text_oarchive ser(out);
    ser << _current_commit << _current_files;
}

void StateRepository::deserialize()
{
    boost::filesystem::path in_path = _repository_path / repository_state_path;
    std::ifstream in(in_path.string());

    boost::archive::text_iarchive ser(in);
    ser >> _current_commit;// >> _current_files; ?!
}

