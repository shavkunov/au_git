//
// Created by mikhail on 11/1/15.
//

#ifndef AU_GIT_DATASTORAGE_HPP
#define AU_GIT_DATASTORAGE_HPP

#include "Commit.hpp"
#include <boost/filesystem.hpp>

class DataStore
{
public:
    static DataStore* instance();

    DataStore();
    void init_storage(const boost::filesystem::path &folder_path);
    bool add_commit(const Commit &commit) const;
    boost::filesystem::path get_commit(const HashCodeType &hash_code) const;

private:
    boost::filesystem::path m_folder_storage_path;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
//        ar & m_hash_code & m_valid_feature;
    }

private:
    static DataStore* m_instance;
};


#endif //AU_GIT_DATASTORAGE_HPP
