#ifndef AU_GIT_REPOSITORY_HPP
#define AU_GIT_REPOSITORY_HPP

#include <memory>
#include <boost/filesystem.hpp>

#include "CommitTree.hpp"
#include "DataStore.hpp"
#include "StateRepository.hpp"
#include "Log.hpp"

class Repository
{
public:
    Repository(const std::string& cur_path);
    ~Repository();
    static boost::filesystem::path is_repository_exists(boost::filesystem::path cur_dir);

    // ---------------------------------------- commands ----------------------------------------
    void add_commit(const std::vector<std::string> &files);
    void revert_commit();
    void revert_file(std::string file);
    void status() const;
    void init_repository(const std::string& cur_dir);
    //-------------------------------------------------------------------------------------------

private:

    void serialize();
    void deserialize();

    std::unique_ptr<CommitTree> _commit_tree;
    std::unique_ptr<DataStore> _data_store;
    StateRepository _state_repository;

    boost::filesystem::path _repository_path;
};

#endif //AU_GIT_REPOSITORY_HPP
