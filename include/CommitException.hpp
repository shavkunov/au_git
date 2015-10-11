//
// Created by mikhail on 10/10/15.
//

#include <string>

#ifndef AU_GIT_COMMITEXCEPTION_HPP
#define AU_GIT_COMMITEXCEPTION_HPP

class CommitException
{
public:
    CommitException(const std::string message)
        :m_message(message)
    {}
    virtual const std::string what() const throw()
    {
        return m_message;
    }

private:
    std::string m_message;
};

class FileIsNotFoundException : public CommitException
{
public:
    FileIsNotFoundException(const std::string message)
            :CommitException(message)
    {}
};

#endif //AU_GIT_COMMITEXCEPTION_HPP
