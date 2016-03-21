#ifndef AU_GIT_COMMIT_HPP
#define AU_GIT_COMMIT_HPP

#include <string>
#include <ctime>
#include <vector>
#include <fstream>

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

#include "HashCodeType.hpp"


struct CommitFile {
    std::string _filename; // имя файла
    HashCodeType _hash_code_file; // его хеш
    std::time_t _timestamp; // время последнего изменения
};

class Commit
{
public:

    Commit();
    boost::filesystem::path get_file_name(size_t i);
    HashCodeType get_file_hash(size_t i);
    void add_files(const std::vector<CommitFile> &commit_files); // добавляет сущности CommitFile в коммит 
    void add_to_storage(const std::string &storage_path) const; // добавляет в storage
    void set_parent_hash_code_commit(const HashCodeType parent_commit_type); // мы понимаем предка нашего коммита
    const std::string hash_code() const; // вернуть хеш коммита
    static Commit create_commit_by_list(const std::vector<std::string> &files); // создание коммита из списка файлов

    HashCodeType get_hash_code() const; // генерация хеша у коммита

    friend bool operator<(const Commit &a, const Commit &b) // сравнивает по хешу
    {
        return a._hash_code_commit.hash_code().to_string() <
               b._hash_code_commit.hash_code().to_string();
    }

    bool operator==(const Commit &a); // ссылкаемся ли на один и тот же datastore?

private:

    HashCodeType _hash_code_commit; // хеш коммита
    HashCodeType _parent_hash_code; // хеш предка
    std::string _meta_info; // всякий треш
    std::vector<CommitFile> _commit_files; // список файлов в коммите

    friend class boost::serialization::access; // friend чтобы иметь доступ к private полям

    template <class Archive>
    void serialize(Archive &ar, const unsigned version) // запись репозитория куда-то
    {
        ar & _hash_code_commit & _parent_hash_code & _meta_info & _commit_files;

        for (size_t i = 0; i < _commit_files.size(); i++)
        {
            CommitFile curFile = _commit_files[i];
             ar & curFile._filename & curFile._hash_code_file & curFile._timestamp;
        }
    }
};

#endif //AU_GIT_COMMIT_HPP
