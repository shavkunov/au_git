#ifndef AU_GIT_DATASTORAGE_HPP
#define AU_GIT_DATASTORAGE_HPP

#include <boost/filesystem.hpp>
#include "Commit.hpp"

class DataStore
{
public:
    DataStore(const boost::filesystem::path &repository_folder); // создаем от папки репозитория

    bool add_commit(const Commit &commit) const; // добавляем сюда коммит
    boost::filesystem::path get_commit(const HashCodeType &hash_code) const; // даем ссылку на коммит по его хешу

private:
    boost::filesystem::path _storage_path; // ссылка на datastore
};


#endif //AU_GIT_DATASTORAGE_HPP
