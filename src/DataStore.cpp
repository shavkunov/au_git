#include "DataStore.hpp"
#include "RepositoryException.hpp"

#include <fstream>
#include <boost/format.hpp>
#include <boost/range/iterator_range.hpp>

namespace
{
    const std::string DATASTORE_FOLDER_NAME = ".objects";

    bool clone_file(boost::filesystem::path in_file, boost::filesystem::path out_file)
    {
        std::ifstream in(in_file.string().c_str(), std::ios::binary);
        std::ofstream out(out_file.string().c_str(), std::ios::binary);
        out << in.rdbuf();
        return in && out;
    }
}

DataStore::DataStore(const boost::filesystem::path &repository_folder)
{
    _storage_path = repository_folder / DATASTORE_FOLDER_NAME;
    if (!boost::filesystem::exists(_storage_path))
    {
        boost::filesystem::create_directory(_storage_path);
    }
}

HashCodeType DataStore::add_file(const boost::filesystem::path file_path)
{
    std::string filename = file_path.string();

    std::ifstream file(filename, std::ios::binary);
    HashCodeType hash_code_file;
    hash_code_file.set_hash_code(file_path);

    boost::filesystem::path in_file(filename);
    boost::filesystem::path out_file(boost::filesystem::path(_storage_path) / hash_code_file.to_string());

    if (!clone_file(in_file, out_file))
    {
        std::string message = boost::str(boost::format("File [%1%] is not commited!") % filename);
        throw FileIsNotCommitedException(message.c_str());
    }

    return hash_code_file;
}

bool DataStore::is_file_exists(HashCodeType file_hash)
{
    return boost::filesystem::exists(boost::filesystem::path(_storage_path) / file_hash.to_string());
}

boost::filesystem::path DataStore::get_file(HashCodeType file_hash)
{
    if (!is_file_exists(file_hash))
        return boost::filesystem::path("");

    for(auto& current_file : boost::make_iterator_range(boost::filesystem::directory_iterator(_storage_path), {}))
    {
        if (current_file.path().filename() == file_hash.to_string())
            return current_file;
    }

    return boost::filesystem::path("");
}
