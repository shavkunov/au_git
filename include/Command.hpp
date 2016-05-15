#ifndef AU_GIT_COMMAND_HPP
#define AU_GIT_COMMAND_HPP

#include "Repository.hpp"
#include <boost/filesystem.hpp>
#include <string>

class Command
{
public:
    virtual void exec(Repository& repo);
    virtual void exec();

    Command(bool flag)
    {
        _repo_presence = flag;
    }

    bool is_repository_needed()
    {
        return _repo_presence;
    }

protected:
    bool _repo_presence;
};

class InitCommand : public Command
{
public:
    InitCommand(std::string name);
    void exec();
    void exec(Repository& repo) {}
private:
    std::string _repo_name;
};

class RevertCommand : public Command
{
public:
    RevertCommand();
    void exec(Repository& repo);
    void exec() {}
};

class AddCommand : public Command
{
public:
    AddCommand(std::vector<std::string>& add_files);
    void exec(Repository& repo);
    void exec() {}
private:
    std::vector<std::string> _files;
};

class EmptyCommand : public Command
{
public:
    void exec() {}
    void exec(Repository& repo) {}
    EmptyCommand();
};

class HelpCommand : public Command
{
public:
    HelpCommand();
    void exec();
    void exec(Repository& repo) {}
};

#endif //AU_GIT_COMMAND_HPP
