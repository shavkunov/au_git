#ifndef AU_GIT_DATASTORAGE_HPP
#define AU_GIT_DATASTORAGE_HPP

#include <boost/filesystem.hpp>
#include "HashCodeType.hpp"
#include "Log.hpp"

class DataStore
{
public:
    DataStore(const boost::filesystem::path &repository_folder);

    HashCodeType add_file(const boost::filesystem::path file_path);
    boost::filesystem::path get_file(HashCodeType file_hash);
    bool is_file_exists(HashCodeType file_hash);
    bool clone_file(boost::filesystem::path in_file,
                    boost::filesystem::path out_file);

private:
    boost::filesystem::path _storage_path;
};


#endif //AU_GIT_DATASTORAGE_HPP
