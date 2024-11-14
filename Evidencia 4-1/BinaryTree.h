#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <string>
#include <map>

struct TreeNode {
    int access_count;
    std::vector<std::string> ips;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int count) : access_count(count), left(nullptr), right(nullptr) {}
};

struct ClassNode {
    int access_count;
    std::vector<std::string> classes;
    ClassNode* left;
    ClassNode* right;

    ClassNode(int count) : access_count(count), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();
    void insertIP(int count, const std::string& ip);
    void insertClass(int count, const std::string& ip_class);
    void findTopIPs(int n);
    void displayClasses();

private:
    TreeNode* root_ip;
    ClassNode* root_class;
    void insertIP(TreeNode*& node, int count, const std::string& ip);
    void insertClass(ClassNode*& node, int count, const std::string& ip_class);
    void findTopIPs(TreeNode* node, std::vector<std::pair<int, std::vector<std::string>>>& top_ips, int& n);
    void displayClasses(ClassNode* node);
    void clear(TreeNode* node);
    void clear(ClassNode* node);
};

#endif // BINARYTREE_H