#ifndef AU_GIT_STATEREPOSITORY_HPP
#define AU_GIT_STATEREPOSITORY_HPP

#include "Commit.hpp"
#include "HashCodeType.hpp"
#include <boost/serialization/map.hpp>
#include <map>

class StateRepository
{
public:
    StateRepository();
    ~StateRepository();

    bool is_file_exists(std::string file_path);
    HashCodeType get_file_hash(std::string file_path);
    void update_file(std::string file_path, HashCodeType file_hash);
    void delete_file(std::string file_path);
    void apply_commit(Commit& commit);
    void cancel_commit(Commit& prev_commit);

private:
    Commit _current_commit;

    std::map<std::string, HashCodeType> _current_files;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
        ar & _current_commit & _current_files;
    }
};

#endif //AU_GIT_STATEREPOSITORY_HPP
