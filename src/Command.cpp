#include "Command.hpp"
#include "Repository.hpp"
#include "Commit.hpp"

InitCommand::InitCommand() : Command(false)  {}
RevertCommand::RevertCommand(std::string file) : Command(true), _file(file) {}
EmptyCommand::EmptyCommand() : Command(false) {}
HelpCommand::HelpCommand() : Command(false) {}
StatusCommand::StatusCommand() : Command(true) {}

void StatusCommand::exec(Repository& repo)
{
    repo.status();
}

void InitCommand::exec()
{
    std::cout << "Initializing repository..." << std::endl;
    boost::filesystem::path repo_path = Repository::is_repository_exists("");
    Repository repo(repo_path.string());
    repo.init_repository("");
    std::cout << "Done" << std::endl;
}

void RevertCommand::exec(Repository& repo)
{
    std::cout << "Reverting..." << std::endl;
    repo.revert_file(_file);
    std::cout << "Done" << std::endl;
}

AddCommand::AddCommand(std::vector<std::string>& add_files) : Command(true)
{
    _files = add_files;  //check files

}

void AddCommand::exec(Repository& repo)
{
    std::cout << "Adding files... " << std::endl;
    repo.add_commit(_files); // добавлять только измененные
    std::cout << "Done" << std::endl;
}

void HelpCommand::exec()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "au_git add {list of files:" << std::endl;
    std::cout << "au_git revert_file {file_name}" << std::endl;
    std::cout << "au_git init " << std::endl;
}
