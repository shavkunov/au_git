#ifndef AU_GIT_TREENODE_HPP
#define AU_GIT_TREENODE_HPP

#include "Commit.hpp"
#include <boost/serialization/split_member.hpp>

class TreeNode // дерево коммитов 
{
public:
    TreeNode();
    TreeNode(Commit commit, std::shared_ptr<TreeNode> parent_node = nullptr); // можно создать от коммита

    Commit commit_value; 
    std::shared_ptr<TreeNode> parent_node; // ссылка на предка

private:
    friend class boost::serialization::access;

    template<class Archive>
    void save(Archive &ar, const unsigned version) const
    {
        bool has_parent = parent_node != nullptr;
        ar << commit_value << has_parent;

        if (has_parent)
        {
            ar << *parent_node;
        }
    }

    template<class Archive>
    void load(Archive &ar, const unsigned version)
    {
        bool has_parent;
        ar >> commit_value >> has_parent;

        if (has_parent)
        {
            parent_node = std::make_shared<TreeNode>();
            ar >> *parent_node;
        }
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

#endif //AU_GIT_TREENODE_HPP
