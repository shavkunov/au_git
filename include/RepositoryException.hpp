#ifndef AU_GIT_REPOSITORYEXCEPTION_HPP
#define AU_GIT_REPOSITORYEXCEPTION_HPP

#include <stdexcept>

// разного рода ошибки, хотим при отладке понимать где что сломалось

class AbstractException : public std::exception // общий класс для всех ошибок
{
public:
    AbstractException(char const* message)
            : _message(message)
    {}
    virtual const char* what()
    {
        return _message;
    }
private:
    char const* _message;
};

// далее вроде название класса все описывает

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
