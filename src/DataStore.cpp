#include "DataStore.hpp"
#include "RepositoryException.hpp"
#include "CommitFile.hpp"

#include <boost/format.hpp>
#include <boost/range/iterator_range.hpp>

namespace
{
    const std::string DATASTORE_FOLDER_NAME = ".objects";

    bool clone_file(boost::filesystem::path in_file, boost::filesystem::path out_file)
    {
        std::ifstream in(in_file.string(), std::ios::binary);
        std::ofstream out(out_file.string(), std::ios::binary);
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

bool DataStore::add_commit(const Commit &commit) const
{
    for (size_t i = 0; i < commit.files_amount(); i++)
    {
        std::string filename = commit.get_file_name(i);

        std::ifstream file(filename, std::ios::binary);
        std::string hash_code_file = encode_content_file(file).to_string();
        boost::filesystem::path in_file(filename);
        boost::filesystem::path out_file(boost::filesystem::path(_storage_path) / hash_code_file);

        if (!clone_file(in_file, out_file))
        {
            std::string message = boost::str(boost::format("File [%1%] is not commited!") % filename);
            throw FileIsNotCommitedException(message.c_str());
        }
    }

    return false;
}

boost::filesystem::path DataStore::get_commit(const HashCodeType &hash_code) const
{
    for(auto& current_file : boost::make_iterator_range(boost::filesystem::directory_iterator(_storage_path), {}))
    {
        if (current_file.path().filename() == hash_code.hash_code().to_string())
            return current_file;
    }
    return boost::filesystem::path("");
}
