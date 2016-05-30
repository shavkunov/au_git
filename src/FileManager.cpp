#include "FileManager.hpp"
#include "HashCodeType.hpp"

#include <string>
#include <map>
#include <boost/filesystem.hpp>

FileManager::FileManager() {}

void FileManager::restore_file(HashCodeType file_hash, std::string file,
                               std::unique_ptr<DataStore> const &data_store)
{
    boost::filesystem::path file_from_datastore = data_store->get_file(file_hash);
    boost::filesystem::path file_path(file);
    data_store->clone_file(file_from_datastore, file_path);
}

void FileManager::sync_with_work_copy(std::unique_ptr<DataStore> const &data_store,
                                      StateRepository &state,
                                      Commit &prev_commit)
{
    //deleting new files
    for (size_t index = 0; index < prev_commit.files_amount(); index++)
    {
        boost::filesystem::path file_path(prev_commit.get_file_name(index));

        if (!prev_commit.get_prev_file_hash(index).is_valid())
        {
            //delete cur file
            boost::filesystem::remove(file_path);
        }
    }

    std::map<std::string, HashCodeType> files = state.get_all_files();

    //restoring others
    for (auto it = files.begin(); it != files.end(); it++)
    {
        restore_file(it->second, it->first, data_store);
    }

}
