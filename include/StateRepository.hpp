#ifndef AU_GIT_STATEREPOSITORY_HPP
#define AU_GIT_STATEREPOSITORY_HPP

#include "Commit.hpp"

namespace
{
    const std::string repository_state_path = "state";
}

class StateRepository
{
public:
    StateRepository();
    ~StateRepository();

    void fix_duplicate();
    void add_file(std::string file_path);
    void set_commit(Commit& commit);
    void serialize();
    void deserialize();

private:

    boost::filesystem::path _repository_path;
    Commit _current_commit;

    class path_saver
    {

    public:
        path_saver(boost::filesystem::path path) : _file_path(path) {}

        path_saver() {}

        boost::filesystem::path get_file_path() const
        {
            return _file_path;
        }

        bool operator== (const path_saver ps) const
        {
            return _file_path.string() == ps.get_file_path().string();
        }

        bool operator< (const path_saver ps) const
        {
            return _file_path.string() < ps.get_file_path().string();
        }

        friend class boost::serialization::access;

        template <class Archive>
        void serialize(Archive &ar, const unsigned version)
        {
            ar & _file_path.string();
        }

    private:
        boost::filesystem::path _file_path;

    };

    std::vector<path_saver> _current_files;

};

#endif //AU_GIT_STATEREPOSITORY_HPP
