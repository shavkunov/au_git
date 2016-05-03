#ifndef AU_GIT_COMMAND_HPP
#define AU_GIT_COMMAND_HPP

#include <boost/filesystem.hpp>
#include <string>

namespace
{
    const std::string au_git_folder_name = ".au_git";
}

class Command
{
public:

    boost::filesystem::path is_repository_exists(boost::filesystem::path cur_dir)const
    {
        boost::filesystem::directory_iterator iter;
        if (boost::filesystem::exists(cur_dir) && boost::filesystem::is_directory(cur_dir))
        {
            while (!cur_dir.empty())
            {
                for (boost::filesystem::directory_iterator dir_iter(cur_dir); dir_iter != iter; ++dir_iter)
                {
                    if (boost::filesystem::is_directory(*dir_iter) && dir_iter->path().filename() == au_git_folder_name)
                        return *dir_iter;
                }
                cur_dir = cur_dir.parent_path();
            }
        }
        return boost::filesystem::path();
    }
	virtual void exec() = 0;
};

class Init : public Command 
{
public:
    Init(std::string name);
    void exec();
private:
    std::string _repo_name;
};

class Revert : public Command
{
public:
    Revert();
    void exec();
};

class Add : public Command
{
public:
    Add(std::vector<std::string>& add_files);
    void exec();
private:
    std::vector<std::string> _files;
};

class Empty : public Command
{
public:
    void exec();
};

class Help : public Command
{
public:
    void exec();
};

#endif //AU_GIT_COMMAND_HPP
