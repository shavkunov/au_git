//
// Created by mikhail on 10/9/15.
//

#ifndef AU_GIT_TREENODE_HPP
#define AU_GIT_TREENODE_HPP

#include "Commit.hpp"
#include "CommitTree.hpp"

class TreeNode
{
public:
    TreeNode(Commit commit = Commit(), size_t position = 0, TreeNode *parent_node = nullptr);

    Commit    m_commit_value;
    size_t    m_index_position;
    TreeNode* m_parent_node;

public:
    static void destroy_chain(TreeNode* node);

private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
        ar & m_commit_value & m_parent_node;
    }
};

#endif //AU_GIT_TREENODE_HPP
