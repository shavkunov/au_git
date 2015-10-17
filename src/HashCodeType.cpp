//
// Created by mikhail on 10/10/15.
//

#include "HashCodeType.hpp"

HashCodeType::HashCodeType()
    : m_hash_code(""), m_valid_feature(true)
{
}

std::string HashCodeType::hash_code() const
{
    return m_hash_code;
}

bool HashCodeType::is_valid() const
{
    return m_valid_feature;
}

void HashCodeType::set_valid(bool state_valid_flag)
{
    m_valid_feature = state_valid_flag;
}