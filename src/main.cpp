#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>

#include "Commit.hpp"
#include "CommitTree.hpp"
#include "RepositoryException.hpp"
#include "Repository.hpp"

int main(int argc, char *argv[])

{
    try
    {
        Repository repo("test");
        repo.init_repository("test");

        std::vector<std::string> files;
        files.push_back("test/input");

        repo.add_commit(files);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
