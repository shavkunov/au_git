//
// Created by mikhail on 10/9/15.
//

#ifndef AU_GIT_COMMITFILE_HPP
#define AU_GIT_COMMITFILE_HPP

#include <string>
#include <ctime>

#include <boost/filesystem.hpp>

#include "HashCodeType.hpp"

class CommitFile
{
public:
    CommitFile(const std::string &);
    CommitFile(){}

    std::string  filename       () const;
    HashCodeType hash_code_file () const;
    void         set_remove_flag();

private:
    std::string  m_filename;
    HashCodeType m_hash_code_file;
    std::time_t  m_timestamp;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
        ar & m_filename & m_hash_code_file & m_timestamp;
    }
};

#endif //AU_GIT_COMMITFILE_HPP
