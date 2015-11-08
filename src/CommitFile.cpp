#include "RepositoryException.hpp"
#include "CommitFile.hpp"

#include <boost/format.hpp>
#include <fstream>

bool clone_file(boost::filesystem::path in_file, boost::filesystem::path out_file)
{
    std::ifstream in(in_file.string(), std::ios::binary);
    std::ofstream out(out_file.string(), std::ios::binary);
    out << in.rdbuf();
    return in && out;
}

CommitFile::CommitFile()
{
}

CommitFile::CommitFile(const std::string &filename)
        : m_filename(filename),
          m_timestamp(std::time_t(0))
{
    if (!boost::filesystem::exists(m_filename))
    {
        std::string message = boost::str(boost::format("File [%1%] is not found!") % m_filename);
        throw FileIsNotFoundException(message.c_str());
    }
    m_timestamp = boost::filesystem::last_write_time(m_filename);
    m_hash_code_file.set_hash_code(m_filename);
}

void CommitFile::add_to_storage(const std::string& storage_path) const
{
    std::ifstream file(m_filename, std::ios::binary);
    std::string hash_code_file = encode_content_file(file).to_string();
    boost::filesystem::path in_file(m_filename);
    boost::filesystem::path out_file(boost::filesystem::path(storage_path).string() + hash_code_file);
    std::cout << out_file.string() << std::endl;
    if (!clone_file(in_file, out_file))
    {
        std::string message = boost::str(boost::format("File [%1%] is not commited!") % m_filename);
        throw FileIsNotCommitedException(message.c_str());
    }
}

boost::filesystem::path CommitFile::filename() const
{
    return boost::filesystem::path(m_filename);
}

HashCodeType CommitFile::hash_code_file() const
{
    return m_hash_code_file;
}

void CommitFile::set_remove_flag()
{
    m_hash_code_file.set_valid(false);
}
