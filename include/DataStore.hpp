#ifndef AU_GIT_DATASTORAGE_HPP
#define AU_GIT_DATASTORAGE_HPP

#include <boost/filesystem.hpp>
#include "Commit.hpp"

class DataStore
{
public:
    DataStore(const boost::filesystem::path &repository_folder);

    bool add_commit(const Commit &commit) const;//file
    boost::filesystem::path get_commit(const HashCodeType &hash_code) const;

private:
    boost::filesystem::path m_storage_path;
};


#endif //AU_GIT_DATASTORAGE_HPP
