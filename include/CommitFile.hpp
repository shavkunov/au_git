//
// Created by mikhail on 10/9/15.
//

#ifndef AU_GIT_COMMITFILE_HPP
#define AU_GIT_COMMITFILE_HPP

#include <string>

#include "HashCodeType.hpp"

class CommitFile
{
public:
    CommitFile(const std::string &);

    std::string  filename       () const;
    HashCodeType hash_code_file () const;
    void         set_remove_flag();

private:
    std::string  m_filename;
    HashCodeType m_hash_code_file;

};

#endif //AU_GIT_COMMITFILE_HPP
