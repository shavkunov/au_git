#include "TreeNode.hpp"

TreeNode::TreeNode(Commit commit, std::shared_ptr<TreeNode> parent_node)
    : m_commit_value(commit),
      m_parent_node(parent_node)
{
}

TreeNode::TreeNode() {}
