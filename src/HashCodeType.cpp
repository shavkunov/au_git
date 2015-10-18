//
// Created by mikhail on 10/10/15.
//

#include "HashCodeType.hpp"
#include "Sha1Converter.hpp"

#include <iostream>

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

void HashCodeType::set_hashcode(const std::string &file_path)
{
    m_hash_code = sha1_converter(file_path);
//    std::cout << m_hash_code << std::endl;
}