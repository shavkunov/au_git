#include "TreeNode.hpp"

TreeNode::TreeNode(Commit commit, std::shared_ptr<TreeNode> parent_node)
    : commit_value(commit),
      parent_node(parent_node)
{
}

TreeNode::TreeNode() {}
