#ifndef AU_GIT_FILE_MANAGER_HPP
#define AU_GIT_FILE_MANAGER_HPP

#include "HashCodeType.hpp"
#include "DataStore.hpp"

class FileManager
{
public:
    FileManager();
    void restore_file(HashCodeType file_hash, std::string file,
                      std::unique_ptr<DataStore> const &_data_store);

private:

};

#endif //AU_GIT_FILE_MANAGER_HPP
