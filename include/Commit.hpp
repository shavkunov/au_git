#ifndef AU_GIT_COMMIT_HPP
#define AU_GIT_COMMIT_HPP

#include <string>
#include <ctime>
#include <vector>

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

#include "HashCodeType.hpp"
#include "CommitFile.hpp"

class Commit
{
public:

    Commit();
    std::string get_file_name(size_t index) const;
    HashCodeType get_file_hash(size_t index) const;
    size_t files_amount() const;
    void add_files(const std::vector<CommitFile> &commit_files);
    void set_parent_hash_code_commit(const HashCodeType parent_commit_type);
    void set_prev_file_hash(HashCodeType prev_file_hash, size_t index);
    HashCodeType get_prev_file_hash(size_t index);
    const std::string hash_code() const;
    static Commit create_commit_by_list(const std::vector<std::string> &files);

    HashCodeType get_hash_code() const;

    friend bool operator<(const Commit &a, const Commit &b)
    {
        return a._hash_code_commit.hash_code().to_string() <
               b._hash_code_commit.hash_code().to_string();
    }

    bool operator==(const Commit &a);

private:

    HashCodeType _hash_code_commit;
    HashCodeType _parent_hash_code;
    std::string _meta_info;
    std::vector<CommitFile> _commit_files;

    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
        ar & _hash_code_commit & _parent_hash_code & _meta_info & _commit_files;
    }
};

#endif //AU_GIT_COMMIT_HPP
