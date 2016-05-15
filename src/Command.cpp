#include "Command.hpp"
#include "Repository.hpp"
#include "Commit.hpp"

InitCommand::InitCommand(std::string name) : Command(false), _repo_name(name)  {}

void InitCommand::exec()
{
    boost::filesystem::path repo_path = Repository::is_repository_exists("");
    Repository repo(repo_path.string());
    repo.init_repository(_repo_name);
}

RevertCommand::RevertCommand() : Command(true) {}

void RevertCommand::exec(Repository& repo)
{
    repo.revert_commit();
}

AddCommand::AddCommand(std::vector<std::string>& add_files) : Command(true)
{
    _files = add_files;  
}

void AddCommand::exec(Repository& repo)
{
    repo.add_commit(_files);
}

EmptyCommand::EmptyCommand() : Command(false) {}

HelpCommand::HelpCommand() : Command(false) {}

void HelpCommand::exec()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "augit add {list of files}:" << std::endl;
    std::cout << "augit revert" << std::endl;
    std::cout << "augit init repo" << std::endl;
}
