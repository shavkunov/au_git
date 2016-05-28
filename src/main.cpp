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

    if (strcmp(argv[1], "init") == 0)
    {
        InitCommand* init_command = new InitCommand();
        return *init_command;
    }

    if (strcmp(argv[1], "revert_file") == 0)
    {
        std::string revert_file = argv[2];
        RevertCommand* revert_command = new RevertCommand(revert_file);
        return *revert_command;
    }

    if (strcmp(argv[1], "add") == 0)
    {

        std::vector<std::string> add_files;

        for (int i = 2; i < argc; i++)
        {
            std::string cur_file = argv[i];
            add_files.push_back(cur_file);
        }

        AddCommand* add_command = new AddCommand(add_files);

        return *add_command;
    }

    if (strcmp(argv[1], "help") == 0)
    {
        HelpCommand* help_command = new HelpCommand();
        return *help_command;
    }


    if (strcmp(argv[1], "status") == 0)
    {
        StatusCommand* status_command = new StatusCommand();
        return *status_command;
    }

    EmptyCommand* empty = new EmptyCommand();
    return *empty;
}

int main(int argc, char* argv[])

{
    try
    {
        Command& command = parse(argc, argv);
        if (command.is_repository_needed())
        {
            boost::filesystem::path repo_path = Repository::is_repository_exists(".");
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
