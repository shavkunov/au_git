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

    void add_files(const std::vector<CommitFile> &commit_files);
    void add_to_storage(const std::string &storage_path) const;
    void set_parent_hash_code_commit(const HashCodeType parent_commit_type);
    const std::string hash_code() const;
    static Commit create_commit_by_list(const std::string &storage_path, const std::vector <std::string> &files);

    HashCodeType get_hash_code() const;

    void print() const
    {
        for(CommitFile c : m_commit_files)
        {
            c.print();
        }
        std::cout << std::endl;
    }

    friend bool operator<(const Commit &a, const Commit &b)
    {
        return a.m_hash_code_commit.hash_code().to_string() <
               b.m_hash_code_commit.hash_code().to_string();
    }

    bool operator== (const Commit &a);

private:
    HashCodeType             m_hash_code_commit;
    HashCodeType             m_parent_hash_code;
    std::string              m_meta_info;
    std::vector <CommitFile> m_commit_files;

    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
        ar & m_hash_code_commit & m_parent_hash_code & m_meta_info & m_commit_files;
    }
};

#endif //AU_GIT_COMMIT_HPP
