#ifndef AU_GIT_COMMITTREE_HPP
#define AU_GIT_COMMITTREE_HPP

#include <map>
#include <vector>

#include <boost/serialization/split_member.hpp>

#include "Commit.hpp"
#include "TreeNode.hpp"

// пока просто бамбук
class CommitTree
{
public:
    CommitTree();
    ~CommitTree();

    void push_commit(const Commit &commit); // добавить коммит
    void pop_commit(); // вроде удалить, но пока вообще не ясно что это и зачем

private:
    std::shared_ptr<TreeNode> find_node_by_hash_code(const std::string &hash_code); 

    friend class boost::serialization::access;

    template<class Archive>
    void save(Archive &ar, const unsigned version) const // название
    {
        bool has_head = m_head != nullptr;
        ar << has_head;

        if (has_head)
        {
            ar << *m_head;
        }
    }

    template<class Archive>
    void load(Archive &ar, const unsigned version) // название
    {
        bool has_head;
        ar >> has_head;

        if (has_head)
        {
            m_head = std::make_shared<TreeNode>();
            ar >> *m_head;
        }
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

private:
    std::shared_ptr<TreeNode> m_head; // начало дерева
};

#endif //AU_GIT_COMMITTREE_HPP
