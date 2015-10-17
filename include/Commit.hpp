//
// Created by mikhail on 10/9/15.
//

#ifndef AU_GIT_COMMIT_HPP
#define AU_GIT_COMMIT_HPP

#include <vector>
#include <string>
#include <iostream>

#include "CommitFile.hpp"
#include "HashCodeType.hpp"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

class Commit
{
public:
    Commit();

    void add_files(const std::vector<CommitFile> &);

    void set_parent_commit(const HashCodeType);

    HashCodeType get_hash_code() const;

    void print()
    {
        for (std::vector<CommitFile>::iterator it = m_commit_files.begin(); it != m_commit_files.end(); ++it)
        {
            std::cout << "\"" << it->filename() << "\" ";
        }
        std::cout << std::endl;
    }

private:
    HashCodeType m_hash_code_commit;
    HashCodeType m_parent_hash_code;
    std::string m_meta_info;
    std::vector<CommitFile> m_commit_files;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
        ar & m_hash_code_commit
           & m_parent_hash_code
           & m_meta_info
           & m_commit_files;
    }
};

#endif //AU_GIT_COMMIT_HPP
