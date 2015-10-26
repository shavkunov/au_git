#include "TreeNode.hpp"

TreeNode::TreeNode(Commit commit, /*size_t position,*/ std::shared_ptr <TreeNode> parent_node)
    : m_commit_value(commit),
//      m_index_position(position),
      m_parent_node(parent_node)
{
}