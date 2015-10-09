//
// Created by mikhail on 10/9/15.
//

#ifndef AU_GIT_HASHCODETYPE_HPP
#define AU_GIT_HASHCODETYPE_HPP

#include <string>

class HashCodeType
{
public:
    HashCodeType();

    std::string hash_code(    ) const;
    bool        is_valid (    ) const;
    void        set_valid(bool);


private:
    std::string m_hash_code;
    bool        m_valid_feature;

};

#endif //AU_GIT_HASHCODETYPE_HPP
