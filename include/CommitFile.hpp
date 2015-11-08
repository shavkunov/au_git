#ifndef AU_GIT_COMMITFILE_HPP
#define AU_GIT_COMMITFILE_HPP

#include <string>
#include <ctime>

#include <boost/filesystem/path.hpp>
#include <boost/serialization/access.hpp>

#include "HashCodeType.hpp"

class CommitFile
{
public:
    CommitFile();
    CommitFile(const std::string &filename);

    boost::filesystem::path  filename() const;
    HashCodeType             hash_code_file () const;
    void                     set_remove_flag();
    void                     add_to_storage(const std::string &storage_path) const;

    void print() const
    {
        std::cout << m_filename << " ";
    }

private:
    std::string   m_filename;
    HashCodeType  m_hash_code_file;
    std::time_t  m_timestamp;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
        ar & m_filename & m_hash_code_file & m_timestamp;
    }
};

#endif //AU_GIT_COMMITFILE_HPP
