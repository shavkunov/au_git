//
// Created by mikhail on 10/9/15.
//

#ifndef AU_GIT_COMMIT_HPP
#define AU_GIT_COMMIT_HPP

#include <list>
#include <string>
#include <iostream>

#include "CommitFile.hpp"
#include "HashCodeType.hpp"

class Commit
{
public:
    Commit();
    Commit(const std::list <CommitFile> &);

    void add_files(const std::list <CommitFile> &);

    void set_parent_commit(const HashCodeType);

    void print()
    {
        for(std::list <CommitFile>::iterator it = m_commit_files.begin();
                it != m_commit_files.end(); ++it)
        {
            std::cout << "\"" << it->filename() << "\" ";
        }
        std::cout << std::endl;
    }

private:
    HashCodeType            m_hash_code_commit;
    HashCodeType            m_parent_hash_code;
    std::string             m_meta_info;
    std::list <CommitFile>  m_commit_files;
};

#endif //AU_GIT_COMMIT_HPP
