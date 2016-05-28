#include "Repository.hpp"

#include <fstream>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace
{
    const std::string repository_store_file_name = "repo";
    const std::string au_git_folder_name = ".au_git";
}

Repository::Repository(const std::string& repo_path)
{
    _repository_path = is_repository_exists(repo_path);

    if (!_repository_path.empty())
    {
        LOG << "create" << std::endl;
        _data_store = std::unique_ptr<DataStore>(new DataStore(_repository_path));
        _commit_tree = std::unique_ptr<CommitTree>(new CommitTree());
        deserialize();
    }
}

void Repository::init_repository(const std::string& cur_dir)
{
    //LOG << "init repo" << std::endl;
    if (!_repository_path.empty())
    {
        // TODO: throw error
        return;
    }

    // create service folder
    _repository_path = boost::filesystem::path(cur_dir) / au_git_folder_name;
    boost::filesystem::create_directory(_repository_path);

    _commit_tree = std::unique_ptr<CommitTree>(new CommitTree());
}

Repository::~Repository()
{
    if (!_repository_path.empty())
    {
        serialize();
    }
}

void Repository::add_commit(const std::vector<std::string> &files)
{
    //std::cout << "Commit files..." << std::endl;
    Commit new_commit = Commit::create_commit_by_list(files);

    for (size_t index = 0; index < new_commit.files_amount(); index++)
    {
        std::string cur_file = new_commit.get_file_name(index);


        if (_state_repository.is_file_exists(cur_file))
        {
            _data_store->add_file(boost::filesystem::path(cur_file));
            new_commit.set_prev_file_hash(boost::filesystem::path(cur_file), index);
        }
    }


    _commit_tree->push_commit(new_commit);
    //LOG << "added?" << std::endl;
    _state_repository.apply_commit(new_commit);
}

void Repository::revert_file(std::string file)
{
    std::cout << "Revert file" << std::endl;

    if (_state_repository.is_file_exists(file))
    {
        std::vector<std::string> files;
        files.push_back(file);

        Commit commit = Commit::create_commit_by_list(files);

        _commit_tree->push_commit(commit);
        _state_repository.apply_commit(commit);
    } else
    {
        // throw
    }
}

void Repository::revert_commit()
{
    std::cout << "Revert commit" << std::endl;

    _commit_tree->pop_commit();
    Commit prev_commit = _commit_tree->get_current_commit();

    _state_repository.cancel_commit(prev_commit);
}

void Repository::status() const
{
    _state_repository.status();
}

boost::filesystem::path Repository::is_repository_exists(boost::filesystem::path cur_dir)
{
    boost::filesystem::directory_iterator iter;
    if (boost::filesystem::exists(cur_dir) && boost::filesystem::is_directory(cur_dir))
    {
        while (!cur_dir.empty())
        {
            for (boost::filesystem::directory_iterator dir_iter(cur_dir); dir_iter != iter; ++dir_iter)
            {
                if (boost::filesystem::is_directory(*dir_iter) && dir_iter->path().filename() == au_git_folder_name)
                    return *dir_iter;
            }
            cur_dir = cur_dir.parent_path();
        }
    }
    return boost::filesystem::path();
}

void Repository::serialize()
{
    boost::filesystem::path out_path = _repository_path / repository_store_file_name;
    std::ofstream out(out_path.string());

    boost::archive::text_oarchive ser(out);
    ser << *_commit_tree << _state_repository;
}

void Repository::deserialize()
{
    boost::filesystem::path in_path = _repository_path / repository_store_file_name;
    std::ifstream in(in_path.string());
    boost::archive::text_iarchive ser(in);

    ser >> *_commit_tree >> _state_repository;
}
