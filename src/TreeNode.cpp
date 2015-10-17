#include "TreeNode.hpp"

TreeNode::TreeNode(Commit commit, size_t position, TreeNode *parent_node)
    : m_commit_value(commit),
      m_index_position(position),
      m_parent_node(parent_node)
{
}

void TreeNode::destroy_chain(TreeNode* node)
{
    while (node != nullptr)
    {
        TreeNode* temp_node = node;
        node = node->m_parent_node;
        delete temp_node;
        temp_node = nullptr;
    }
}