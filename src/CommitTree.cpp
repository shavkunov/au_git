#include "CommitTree.hpp"
#include "RepositoryException.hpp"

#include <fstream>
#include <map>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/utility.hpp>

CommitTree::CommitTree(const std::string &storage_path)
    : m_storage_path(storage_path)
{
    std::cout << "Constructor" << std::endl;
    deserialize(m_storage_path);
}

CommitTree::~CommitTree()
{
    std::cout << "Destructor" << std::endl;
    serialize(m_storage_path);
}

void CommitTree::set_storage_path(const std::string &storage_path)
{
    m_storage_path = storage_path;
}

void CommitTree::push_commit(const Commit &commit)
{
    std::shared_ptr<TreeNode> add_node(new TreeNode(commit, m_current_node));
    m_current_node = add_node;

    if (m_branches.size() == 0)
    {
        m_branches.push_back(m_current_node);
        m_current_index_branch = 0;
        return;
    }

    m_branches[m_current_index_branch] = m_current_node;
}

void CommitTree::create_branch(const Commit &commit, const std::string parent_hash_code)
{
    std::shared_ptr <TreeNode> branch_node = find_node_by_hash_code(parent_hash_code);
    if (branch_node == nullptr)
    {
        throw BranchNotCreatedException("Branch could not be created!");
    }

    std::shared_ptr <TreeNode> add_node(new TreeNode(commit, branch_node));
    m_branches.push_back(add_node);
    m_current_index_branch = m_branches.size() - 1;
    m_current_node = add_node;
}

std::shared_ptr <TreeNode> CommitTree::find_node_by_hash_code(const std::string& parent_hash_code)
{
    for(std::shared_ptr <TreeNode> node : m_branches)
    {
        for(std::shared_ptr <TreeNode> ptr = node; ptr != nullptr; ptr = ptr->m_parent_node)
        {
            if (ptr->m_commit_value.get_hash_code().hash_code().to_string() == parent_hash_code)
            {
                return ptr;
            }
        }
    }
    return nullptr;
}

void CommitTree::print_current_node() const
{
    for(std::shared_ptr <TreeNode> ptr = m_current_node; ptr != nullptr; ptr = ptr->m_parent_node)
        ptr->m_commit_value.print();
}

void CommitTree::pop_commit()
{
    if (m_current_node == nullptr)
    {
        // throw exception
        return;
    }
    std::shared_ptr <TreeNode> parent_node = m_current_node->m_parent_node;
    m_current_node = parent_node;
    m_branches[m_current_index_branch] = m_current_node;
}

void CommitTree::serialize(const std::string &storage_path)
{
    std::cout << "Serialize: " << storage_path + m_storage_pakage_name << std::endl;

    return;
    std::ofstream out_file(storage_path + m_storage_pakage_name);

    boost::archive::text_oarchive archive(out_file);
    std::map <Commit, std::vector <Commit>> table;
    Commit root_commit;

    for(std::shared_ptr <TreeNode> node : m_branches)
    {
        std::shared_ptr <TreeNode> temp = node;
        table[node->m_commit_value];
        while (temp->m_parent_node != nullptr)
        {
            table[temp->m_parent_node->m_commit_value].push_back(temp->m_commit_value);
            temp = temp->m_parent_node;
        }
        root_commit = temp->m_commit_value;
    }
    archive << table << root_commit;
}

void CommitTree::dfs(std::map <Commit, std::vector <Commit>> &table,
                     std::shared_ptr <TreeNode> &root,
                     std::vector <std::shared_ptr<TreeNode>> &branches)
{
    if (!table[root->m_commit_value].size())
    {
        branches.push_back(root);
        return;
    }
    for(auto& commit : table[root->m_commit_value])
    {
        std::shared_ptr <TreeNode> ptr(new TreeNode(commit, root));
        std::cout << commit.hash_code() << std::endl;
        dfs(table, ptr, branches);
    }
}

void CommitTree::deserialize(const std::string &storage_path)
{
    //return;
    std::cout << "Deserialize: " << storage_path + m_storage_pakage_name << std::endl;
    std::ifstream in_file(storage_path + m_storage_pakage_name);
    boost::archive::text_iarchive archive(in_file);

    std::map <Commit, std::vector <Commit>> table;
    Commit root_commit;
    archive >> table >> root_commit;

    std::cout << root_commit.hash_code() << std::endl;

    return;
    m_current_node = std::make_shared <TreeNode>(root_commit);
    dfs(table, m_current_node, m_branches);

    for(auto a : m_branches)
    {
        std::cout << a->m_commit_value.hash_code() << ": ";
        auto b = a;
        while (b != nullptr)
        {
            //std::cout << b->m_commit_value.hash_code() << " ";
            b = b->m_parent_node;
        }
        std::cout << "\n";
    }
}

