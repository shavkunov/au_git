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
    m_repository_path = is_repository_exists(cur_dir);

    if (!m_repository_path.empty())
    {
        m_data_store = std::unique_ptr<DataStore>(new DataStore(m_repository_path));
        m_commit_tree = std::unique_ptr<CommitTree>(new CommitTree());
        deserialize();
    }
}

void Repository::init_repository(const std::string& cur_dir)
{
    m_repository_path = is_repository_exists(cur_dir);

    if (!m_repository_path.empty())
    {
        // TODO: throw error
        return;
    }

    // create service folder
    m_repository_path = boost::filesystem::path(cur_dir) / au_git_folder_name;
    boost::filesystem::create_directory(m_repository_path);

    m_commit_tree = std::unique_ptr<CommitTree>(new CommitTree());
}

Repository::~Repository()
{
    if (!m_repository_path.empty())
    {
        serialize();
    }
}

void Repository::add_commit(const std::vector<std::string> &files)
{
    std::cout << "Commit files" << std::endl;
    Commit new_commit = Commit::create_commit_by_list(files);
    m_commit_tree->push_commit(new_commit);
    m_data_store->add_commit(new_commit);
}

void Repository::status() const
{
    std::cout << "Status of repository" << std::endl;
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
    boost::filesystem::path out_path = m_repository_path / repository_store_file_name;
    std::ofstream out(out_path.string());

    boost::archive::text_oarchive ser(out);
    ser << *m_commit_tree << m_state_repository;
}

void Repository::deserialize()
{
    boost::filesystem::path in_path = m_repository_path / repository_store_file_name;
    std::ifstream in(in_path.string());
    boost::archive::text_iarchive ser(in);

    ser >> *m_commit_tree >> m_state_repository;
}
