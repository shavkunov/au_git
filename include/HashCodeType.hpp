#ifndef AU_GIT_HASHCODETYPE_HPP
#define AU_GIT_HASHCODETYPE_HPP

#include <string>
#include <boost/filesystem.hpp>
#include <boost/serialization/access.hpp>

#include "Sha256Converter.hpp"

class HashCodeType
{
public:
    HashCodeType();

    Sha256 hash_code() const;
    bool   is_valid () const;
    void   set_valid(bool state_valid_flag);
    void   set_hash_code(const boost::filesystem::path &file_path);
    void   set_hash_code_by_list(const std::vector<CommitFile> &commits, const HashCodeType &code);

private:
    Sha256 m_hash_code;
    bool   m_valid_feature;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
        ar & m_hash_code & m_valid_feature;
    }
};

#endif //AU_GIT_HASHCODETYPE_HPP
