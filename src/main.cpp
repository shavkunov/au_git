#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>
#include <sstream>

#include "Commit.hpp"
#include "CommitTree.hpp"
#include "RepositoryException.hpp"
#include "Repository.hpp"
#include "Command.hpp"

Command& parse(int argc, char* argv[])
{

    Empty* empty = new Empty();

    if (!strcmp(argv[0], "augit"))
    {
        if (!strcmp(argv[1], "init"))
        {
            std::string repo_name = argv[2];
            Init* init_command = new Init(repo_name);
            return *init_command;
        }

        if (!strcmp(argv[1], "revert"))
        {
            Revert* revert_command = new Revert();
            return *revert_command;
        }

        if (!strcmp(argv[1], "add"))
        {
            std::vector<std::string> add_files;

            std::copy(argv + 2, argv + argc, add_files.begin());
            Add* add_command = new Add(add_files);
            return *add_command;
        }
    } else
    {
        // throw exception
    }

    return *empty;
}

int main(int argc, char* argv[])

{
    try
    {
        Command& command = parse(argc, argv);
        command.exec();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
