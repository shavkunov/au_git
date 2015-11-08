#include "Repository.hpp"
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <fstream>

Repository::Repository(const std::string& cur_dir)
{
    // create repository and start point
    init_repository(cur_dir);
    // create datastore (initialization singletone object)
    m_data_store = DataStore::instance();
    m_data_store->init_storage(m_objects_path);
    //
    m_commit_tree = std::make_unique <CommitTree>(m_objects_path.string());
}

void Repository::init_repository(const std::string& cur_dir)
{
    m_repository_path = is_repository_exists(cur_dir);
    if (m_repository_path.empty())
    {
        m_repository_path = boost::filesystem::path(cur_dir + (cur_dir[cur_dir.length() - 1] == '/' ? "" : "/") +".au_git/");
        std::cout << "!" << m_repository_path << std::endl;
        boost::filesystem::create_directory(boost::filesystem::path(m_repository_path));
        m_objects_path = m_repository_path.string() + "/.objects/";
        boost::filesystem::create_directory(boost::filesystem::path(m_objects_path));
        std::cout << "repository create: " << m_repository_path << std::endl;
    }
    m_objects_path = m_repository_path.string() + "/.objects/";
    std::cout << "Repository: " << m_repository_path << std::endl;
    std::cout << "Objects   : " << m_objects_path << std::endl;
}

Repository::~Repository()
{
    if (m_data_store)
        delete m_data_store;
}

void Repository::add_commit(const std::vector<std::string> &files)
{
    std::cout << "Commit files" << std::endl;
    Commit new_commit = Commit::create_commit_by_list(m_objects_path.string(), files);
    m_commit_tree->push_commit(new_commit);
    m_data_store->add_commit(new_commit);
}

void Repository::create_branch(const std::vector<std::string> &files, const std::string &commit_hash)
{
    std::cout << "Create branch" << std::endl;
    Commit new_commit = Commit::create_commit_by_list(m_objects_path.string(), files);
    m_commit_tree->create_branch(new_commit, commit_hash);
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
        while (cur_dir != boost::filesystem::path(""))
        {
            for (boost::filesystem::directory_iterator dir_iter(cur_dir); dir_iter != iter; ++dir_iter)
            {
                if (boost::filesystem::is_directory(*dir_iter) && dir_iter->path().filename() == m_au_git_folder_name)
                    return *dir_iter;
            }
            cur_dir = cur_dir.parent_path();
        }
    }
    return boost::filesystem::path("");
}

void Repository::serialize()
{
    //std::ofstream out("out.bin", std::ios::binary);
    //boost::archive::text_oarchive ser(out);
    //out << m_commit_tree << m_data_store << m_state_repository << m_repository_path << m_objects_path << m_au_git_folder_name;
}

void Repository::deserialize()
{
}
