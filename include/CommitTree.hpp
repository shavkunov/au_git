#ifndef AU_GIT_COMMITTREE_HPP
#define AU_GIT_COMMITTREE_HPP

#include "Commit.hpp"
#include "TreeNode.hpp"
#include <map>
#include <vector>

class TreeNode;

class CommitTree
{
public:
    CommitTree(const std::string &storage_path);
    ~CommitTree();

    void set_storage_path(const std::string &storage_path);
    void push_commit(const Commit &commit);
    void pop_commit();
    void create_branch(const Commit &commit, const std::string parent_hash_code);
    void print_current_node() const;

private:
    void serialize(const std::string &storage_path);
    void deserialize(const std::string &storage_path);

    std::shared_ptr <TreeNode> find_node_by_hash_code(const std::string &parent_hash_code);
    void dfs(std::map <Commit, std::vector <Commit>> &table, std::shared_ptr <TreeNode> &root, std::vector <std::shared_ptr<TreeNode>> &branches);

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned version)
    {
//        ar & m_hash_code & m_valid_feature;
    }

private:
    std::vector <std::shared_ptr<TreeNode>> m_branches;
    std::shared_ptr <TreeNode>              m_current_node = nullptr;
    std::string                             m_storage_path;
    size_t                                  m_last_index   = 0;
    size_t                                  m_current_index_branch;
    const std::string                       m_storage_pakage_name = ".data_tree";
};

#endif //AU_GIT_COMMITTREE_HPP
