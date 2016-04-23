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

Repository::Repository(const std::string& cur_dir)
{
    _repository_path = is_repository_exists(cur_dir);

    if (!_repository_path.empty())
    {
        std::cerr << "create" << std::endl;
        _data_store = std::unique_ptr<DataStore>(new DataStore(_repository_path));
        _commit_tree = std::unique_ptr<CommitTree>(new CommitTree());
        deserialize();
    }
}

void Repository::init_repository(const std::string& cur_dir)
{
    _repository_path = is_repository_exists(cur_dir);

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
    std::cerr << "Commit files" << std::endl;
    Commit new_commit = Commit::create_commit_by_list(files);
    _commit_tree->push_commit(new_commit);
    for (size_t index = 0; index < new_commit.files_amount(); index++)
    {
        _data_store->add_file(boost::filesystem::path(new_commit.get_file_name(index)));
        _state_repository.add_file(files[index]);
    }

    _state_repository.set_commit(new_commit);
    _state_repository.fix_duplicate();
}

void Repository::status() const
{
    std::cerr << "Status of repository" << std::endl;
}

boost::filesystem::path Repository::is_repository_exists(boost::filesystem::path cur_dir) const
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
    ser << *_commit_tree;
}

void Repository::deserialize()
{
    boost::filesystem::path in_path = _repository_path / repository_store_file_name;
    std::ifstream in(in_path.string());
    boost::archive::text_iarchive ser(in);

    ser >> *_commit_tree;
    _state_repository.deserialize();
}
