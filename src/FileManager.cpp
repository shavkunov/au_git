#include "FileManager.hpp"
#include <boost/filesystem.hpp>

FileManager::FileManager() {}

void FileManager::restore_file(HashCodeType file_hash, std::string file,
                               std::unique_ptr<DataStore> const &_data_store)
{
    boost::filesystem::path file_from_datastore = _data_store->get_file(file_hash);
    boost::filesystem::path file_path(file);
    _data_store->clone_file(file_from_datastore, file_path);
}
