#ifndef AU_GIT_REPOSITORY_HPP
#define AU_GIT_REPOSITORY_HPP

#include "CommitTree.hpp"
#include "StateRepository.hpp"
#include "DataStore.hpp"

#include <memory>
#include <boost/filesystem.hpp>

class Repository
{
public:
    Repository(const std::string& cur_path);
    ~Repository();

    // ---------------------------------------- commands ----------------------------------------
    void add_commit(const std::vector <std::string> &files);
    void create_branch(const std::vector <std::string> &files, const std::string &commit_hash);
    void status() const;
    //-------------------------------------------------------------------------------------------

private:
    std::unique_ptr <CommitTree> m_commit_tree;
    DataStore*                   m_data_store;
    StateRepository              m_state_repository;

    boost::filesystem::path      m_repository_path;
    boost::filesystem::path      m_objects_path;

    const std::string            m_au_git_folder_name = ".au_git";

private:
    void init_repository(const std::string& cur_dir);
    boost::filesystem::path is_repository_exists(boost::filesystem::path path) const;

private:
    void serialize();
    void deserialize();
};

#endif //AU_GIT_REPOSITORY_HPP
