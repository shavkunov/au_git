#include "DataStore.hpp"
#include <boost/range/iterator_range.hpp>

DataStore* DataStore::m_instance = nullptr;

DataStore* DataStore::instance()
{
    if (m_instance == nullptr)
        m_instance = new DataStore();
    return m_instance;
}

DataStore::DataStore()
{
    //init_storage();
}

void DataStore::init_storage(const boost::filesystem::path &folder_path)
{
    m_folder_storage_path = folder_path;
}

bool DataStore::add_commit(const Commit &commit) const
{
    commit.add_to_storage(m_folder_storage_path.string());
    return false;
}

boost::filesystem::path DataStore::get_commit(const HashCodeType &hash_code) const
{
    for(auto& current_file : boost::make_iterator_range(boost::filesystem::directory_iterator(m_folder_storage_path), {}))
    {
        if (current_file.path().filename() == hash_code.hash_code().to_string())
            return current_file;
    }
    return boost::filesystem::path("");
}