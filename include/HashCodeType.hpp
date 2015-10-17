//
// Created by mikhail on 10/9/15.
//

#ifndef AU_GIT_HASHCODETYPE_HPP
#define AU_GIT_HASHCODETYPE_HPP

#include <string>
#include <boost/serialization/access.hpp>

class HashCodeType
{
public:
    HashCodeType();

    std::string hash_code() const;
    bool        is_valid () const;
    void        set_valid(bool);


private:
    std::string m_hash_code;
    bool        m_valid_feature;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
        ar & m_hash_code & m_valid_feature;
    }
};

#endif //AU_GIT_HASHCODETYPE_HPP
