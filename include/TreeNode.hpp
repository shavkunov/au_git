//
// Created by mikhail on 10/9/15.
//

#ifndef AU_GIT_TREENODE_HPP
#define AU_GIT_TREENODE_HPP

#include "Commit.hpp"

class TreeNode
{
public:
    TreeNode(Commit commit = Commit(), TreeNode *next_node = nullptr, TreeNode *parent_node = nullptr);

    Commit    m_commit_value;
    TreeNode* m_next_node;
    TreeNode* m_parent_node;
};

#endif //AU_GIT_TREENODE_HPP
