//
// Created by mikhail on 10/10/15.
//

#include "../include/TreeNode.hpp"

TreeNode::TreeNode(Commit commit, TreeNode *next_node, TreeNode *parent_node)
    : m_commit_value(commit), m_next_node(next_node), m_parent_node(parent_node)
{
}