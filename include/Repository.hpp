#ifndef AU_GIT_REPOSITORY_HPP
#define AU_GIT_REPOSITORY_HPP

#include <memory>
#include <boost/filesystem.hpp>

#include "CommitTree.hpp"
#include "DataStore.hpp"
#include "StateRepository.hpp"

class Repository
{
public:
    Repository(const std::string& cur_path);
    ~Repository();

    // ---------------------------------------- commands ----------------------------------------
    void add_commit(const std::vector<std::string> &files);
    void status() const; // статус
    void init_repository(const std::string& cur_dir);
    //-------------------------------------------------------------------------------------------

private:
    boost::filesystem::path is_repository_exists(boost::filesystem::path path) const;

    void serialize();
    void deserialize();

private:
    std::unique_ptr<CommitTree> _commit_tree;
    std::unique_ptr<DataStore> _data_store;
    StateRepository _state_repository;

    boost::filesystem::path _repository_path;
};

#endif //AU_GIT_REPOSITORY_HPP
