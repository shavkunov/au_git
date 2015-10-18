#include <CommitException.hpp>
#include "CommitFile.hpp"

#include <boost/format.hpp>

CommitFile::CommitFile(const std::string &filename)
        : m_filename(filename), m_timestamp(std::time_t(0))
{
    if (!boost::filesystem::exists(m_filename))
    {
        std::string message = boost::str(boost::format("File [%1%] is not found!") % m_filename);
        throw FileIsNotFoundException(message.c_str());
    }
    m_timestamp = boost::filesystem::last_write_time(m_filename);
    m_hash_code_file.set_hashcode(m_filename);
}

std::string CommitFile::filename() const
{
    return m_filename;
}

HashCodeType CommitFile::hash_code_file() const
{
    return m_hash_code_file;
}

void CommitFile::set_remove_flag()
{
    m_hash_code_file.set_valid(false);
}
