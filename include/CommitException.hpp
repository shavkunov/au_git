//
// Created by mikhail on 10/10/15.
//

#include <stdexcept>

#ifndef AU_GIT_COMMITEXCEPTION_HPP
#define AU_GIT_COMMITEXCEPTION_HPP

class CommitException : public std::exception
{
public:
    CommitException(char const* message)
        : m_message(message)
    {}
    virtual const char* what()
    {
        return m_message;
    }
private:
    char const* m_message;
};

class FileIsNotFoundException : public CommitException
{
public:
    FileIsNotFoundException(char* message)
            :CommitException(message)
    {}
};

#endif //AU_GIT_COMMITEXCEPTION_HPP
