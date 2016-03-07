#ifndef AU_GIT_TREENODE_HPP
#define AU_GIT_TREENODE_HPP

#include "Commit.hpp"
#include <boost/serialization/split_member.hpp>

class TreeNode
{
public:
    TreeNode();
    TreeNode(Commit commit, std::shared_ptr<TreeNode> parent_node = nullptr);

    Commit m_commit_value;
    std::shared_ptr<TreeNode> m_parent_node;

private:
    friend class boost::serialization::access;

    template<class Archive>
    void save(Archive &ar, const unsigned version) const
    {
        bool has_parent = m_parent_node != nullptr;
        ar << m_commit_value << has_parent;

        if (has_parent)
        {
            ar << *m_parent_node;
        }
    }

    template<class Archive>
    void load(Archive &ar, const unsigned version)
    {
        bool has_parent;
        ar >> m_commit_value >> has_parent;

        if (has_parent)
        {
            m_parent_node = std::make_shared<TreeNode>();
            ar >> *m_parent_node;
        }
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

#endif //AU_GIT_TREENODE_HPP
