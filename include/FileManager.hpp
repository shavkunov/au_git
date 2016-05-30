#ifndef AU_GIT_FILE_MANAGER_HPP
#define AU_GIT_FILE_MANAGER_HPP

#include "HashCodeType.hpp"
#include "DataStore.hpp"
#include "StateRepository.hpp"
#include "Commit.hpp"

class FileManager
{
public:
    FileManager();
    void restore_file(HashCodeType file_hash, std::string file,
                      std::unique_ptr<DataStore> const &data_store);

    void sync_with_work_copy(std::unique_ptr<DataStore> const &data_store,
                             StateRepository &state,
                             Commit &prev_commit);
private:

};

#endif //AU_GIT_FILE_MANAGER_HPP
