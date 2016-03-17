#ifndef AU_GIT_COMMIT_HPP
#define AU_GIT_COMMIT_HPP

#include <string>
#include <vector>

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

#include "CommitFile.hpp"
#include "HashCodeType.hpp"

// сущность коммита
class Commit
{
public:
    Commit();

    void add_files(const std::vector<CommitFile> &commit_files); // добавляет сущности CommitFile в коммит 
    void add_to_storage(const std::string &storage_path) const; // добавляет в storage
    void set_parent_hash_code_commit(const HashCodeType parent_commit_type); // мы понимаем предка нашего коммита
    const std::string hash_code() const; // вернуть хеш коммита
    static Commit create_commit_by_list(const std::vector<std::string> &files); // создание коммита из списка файлов

    HashCodeType get_hash_code() const; // генерация хеша у коммита

    friend bool operator<(const Commit &a, const Commit &b) // сравнивает по хешу
    {
        return a.m_hash_code_commit.hash_code().to_string() <
               b.m_hash_code_commit.hash_code().to_string();
    }

    bool operator==(const Commit &a); // ссылкаемся ли на один и тот же datastore?

private:
    HashCodeType m_hash_code_commit; // хеш коммита 
    HashCodeType m_parent_hash_code; // хеш предка 
    std::string m_meta_info; // всякий треш 
    std::vector<CommitFile> m_commit_files; // список файлов в коммите 

    friend class boost::serialization::access; // friend чтобы иметь доступ к private полям

    template <class Archive>
    void serialize(Archive &ar, const unsigned version) // запись репозитория куда-то
    {
        ar & m_hash_code_commit & m_parent_hash_code & m_meta_info & m_commit_files;
    }
};

#endif //AU_GIT_COMMIT_HPP
