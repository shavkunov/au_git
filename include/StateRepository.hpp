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
        //TODO: implement serialization
    }

};

#endif //AU_GIT_STATEREPOSITORY_HPP
