#include <iostream>
#include <initializer_list>

#include "CommitTree.hpp"
#include "RepositoryException.hpp"
#include "Repository.hpp"

int main(int argc, char *argv[])
{
    try
    {
        Repository repo("test");
        repo.init_repository("test");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
