#include "Command.hpp"
#include "Repository.hpp"
#include "Commit.hpp"

Init::Init(std::string name)
{
    _repo_name = name;
}

void Init::exec()
{
    Repository repo(_repo_name);
    repo.init_repository(_repo_name);
}

Revert::Revert() {}

void Revert::exec()
{
    boost::filesystem::path repo_path = is_repository_exists("");
    Repository repo(repo_path.string());

    repo.revert_commit();
}

Add::Add(std::vector<std::string>& add_files)
{
    _files = add_files;
}

void Add::exec()
{
    boost::filesystem::path repo_path = is_repository_exists("");
    Repository repo(repo_path.string());

    repo.add_commit(_files);
}

void Empty::exec() {}

void Help::exec()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "augit add {list of files}:" << std::endl;
    std::cout << "augit revert" << std::endl;
    std::cout << "augit init repo" << std::endl;
}
