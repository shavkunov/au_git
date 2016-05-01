#ifndef AU_GIT_COMMITFILE_HPP
#define AU_GIT_COMMITFILE_HPP

#include "HashCodeType.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/serialization/access.hpp>

#include <ctime>
#include <string>

class CommitFile
{
public:
    CommitFile(){}

    CommitFile(std::string filename, HashCodeType hash, std::time_t time)
       : _filename(filename), _hash_code_file(hash), _prev_file_hash(false), _timestamp(time) {}

    std::string get_file_name() const
    {
        return _filename;
    }

    HashCodeType get_file_hash() const
    {
        return _hash_code_file;
    }

    HashCodeType get_prev_file_hash()
    {
        return _prev_file_hash;
    }

    void set_prev_file_hash(HashCodeType prev_file_hash)
    {
        _prev_file_hash = prev_file_hash;
    }

private:
    std::string _filename;
    HashCodeType _hash_code_file;
    HashCodeType _prev_file_hash;
    std::time_t _timestamp;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
        ar & _filename & _hash_code_file & _prev_file_hash & _timestamp;
    }
};

#endif //AU_GIT_COMMITFILE_HPP
