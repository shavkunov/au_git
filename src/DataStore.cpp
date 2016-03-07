#include "DataStore.hpp"
#include <boost/range/iterator_range.hpp>

namespace
{
    const std::string DATASTORE_FOLDER_NAME = ".objects";
}

DataStore::DataStore(const boost::filesystem::path &repository_folder)
{
    m_storage_path = repository_folder / DATASTORE_FOLDER_NAME;
    if (!boost::filesystem::exists(m_storage_path))
    {
        boost::filesystem::create_directory(m_storage_path);
    }
}

bool DataStore::add_commit(const Commit &commit) const
{
    commit.add_to_storage(m_storage_path.string());
    return false;
}

boost::filesystem::path DataStore::get_commit(const HashCodeType &hash_code) const
{
    for(auto& current_file : boost::make_iterator_range(boost::filesystem::directory_iterator(m_storage_path), {}))
    {
        if (current_file.path().filename() == hash_code.hash_code().to_string())
            return current_file;
    }
    return boost::filesystem::path("");
}
