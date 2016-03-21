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
    Repository(const std::string& cur_path); // конструктор от пути
    ~Repository();

    // ---------------------------------------- commands ----------------------------------------
    void add_commit(const std::vector<std::string> &files); // можем добавить коммит
    void status() const; // статус
    void init_repository(const std::string& cur_dir); // что ЭТО
    //-------------------------------------------------------------------------------------------

private:
    boost::filesystem::path is_repository_exists(boost::filesystem::path path) const;

    void serialize();
    void deserialize();

private:
    std::unique_ptr<CommitTree> _commit_tree; // указатель на дерево коммитов
    std::unique_ptr<DataStore> _data_store; // указатель на data_store
    StateRepository _state_repository; // состояние???

    boost::filesystem::path _repository_path; // путь до репозитория
};

#endif //AU_GIT_REPOSITORY_HPP
