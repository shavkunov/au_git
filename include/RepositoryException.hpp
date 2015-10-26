#include <stdexcept>

#ifndef AU_GIT_REPOSITORYEXCEPTION_HPP
#define AU_GIT_REPOSITORYEXCEPTION_HPP

class AbstractException : public std::exception
{
public:
    AbstractException(char const* message)
            : m_message(message)
    {}
    virtual const char* what()
    {
        return m_message;
    }
private:
    char const* m_message;
};

class CommitException : public AbstractException
{
public:
    CommitException(char const* message)
            : AbstractException(message)
    {}
};

class FileIsNotFoundException : public CommitException
{
public:
    FileIsNotFoundException(char const* message)
            :CommitException(message)
    {}
};

class FileIsNotCommitedException : public CommitException
{
public:
    FileIsNotCommitedException(char const* message)
            :CommitException(message)
    {}
};


class BranchException : public AbstractException
{
public:
    BranchException(char const* message)
            : AbstractException(message)
    {}
};

class BranchNotCreatedException : public BranchException
{
public:
    BranchNotCreatedException(char const* message)
            :BranchException(message)
    {}
};


#endif //AU_GIT_REPOSITORYEXCEPTION_HPP
