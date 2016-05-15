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

    EmptyCommand* empty = new EmptyCommand();

    if (strcmp(argv[0], "augit") == 0)
    {
        if (strcmp(argv[1], "init") == 0)
        {
            std::string repo_name = argv[2];
            InitCommand* init_command = new InitCommand(repo_name);
            return *init_command;
        }

        if (strcmp(argv[1], "revert") == 0)
        {
            RevertCommand* revert_command = new RevertCommand();
            return *revert_command;
        }

        if (strcmp(argv[1], "add") == 0)
        {
            std::vector<std::string> add_files;

            std::copy(argv + 2, argv + argc, add_files.begin());
            AddCommand* add_command = new AddCommand(add_files);
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
        if (command.is_repository_needed())
        {
            boost::filesystem::path repo_path = Repository::is_repository_exists("");
            Repository repo(repo_path.string());
            command.exec(repo);
        } else
        {
            command.exec();
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
