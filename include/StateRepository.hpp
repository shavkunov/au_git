//
// Created by mikhail on 10/10/15.
//

#ifndef AU_GIT_STATEREPOSITORY_HPP
#define AU_GIT_STATEREPOSITORY_HPP

#include <boost/serialization/access.hpp>

class StateRepository
{
public:
    StateRepository();
    ~StateRepository();

private:

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
//        ar & m_hash_code & m_valid_feature;
    }

};

#endif //AU_GIT_STATEREPOSITORY_HPP
