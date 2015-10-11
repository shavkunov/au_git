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

    std::string  filename       () const;
    HashCodeType hash_code_file () const;
    void         set_remove_flag();

private:
    boost::filesystem::path m_file;
    HashCodeType            m_hash_code_file;
    std::time_t             m_timestamp;
};

#endif //AU_GIT_COMMITFILE_HPP
