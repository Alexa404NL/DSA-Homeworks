#include "BinaryTree.h"
#include <algorithm>
#include <iostream>

BinaryTree::BinaryTree() : root_ip(nullptr), root_class(nullptr) {}

BinaryTree::~BinaryTree() {
    clear(root_ip);
    clear(root_class);
}

void BinaryTree::insertIP(int count, const std::string& ip) {
    insertIP(root_ip, count, ip);
}

void BinaryTree::insertClass(int count, const std::string& ip_class) {
    insertClass(root_class, count, ip_class);
}

void BinaryTree::insertIP(TreeNode*& node, int count, const std::string& ip) {
    if (!node) {
        node = new TreeNode(count);
        node->ips.push_back(ip);
    } else if (count == node->access_count) {
        node->ips.push_back(ip);
    } else if (count < node->access_count) {
        insertIP(node->left, count, ip);
    } else {
        insertIP(node->right, count, ip);
    }
}

void BinaryTree::insertClass(ClassNode*& node, int count, const std::string& ip_class) {
    if (!node) {
        node = new ClassNode(count);
        node->classes.push_back(ip_class);
    } else if (count == node->access_count) {
        node->classes.push_back(ip_class);
    } else if (count < node->access_count) {
        insertClass(node->left, count, ip_class);
    } else {
        insertClass(node->right, count, ip_class);
    }
}

void BinaryTree::findTopIPs(int n) {
    std::vector<std::pair<int, std::vector<std::string>>> top_ips;
    findTopIPs(root_ip, top_ips, n);
    for (const auto& entry : top_ips) {
        for (const auto& ip : entry.second) {
            std::cout << ip << " with " << entry.first << " accesses" << std::endl;
        }
    }
}

void BinaryTree::findTopIPs(TreeNode* node, std::vector<std::pair<int, std::vector<std::string>>>& top_ips, int& n) {
    if (!node || n <= 0) return;
    findTopIPs(node->right, top_ips, n);
    if (n > 0) {
        top_ips.push_back({node->access_count, node->ips});
        n -= 1;
    }
    findTopIPs(node->left, top_ips, n);
}

void BinaryTree::displayClasses() {
    displayClasses(root_class);
}

void BinaryTree::displayClasses(ClassNode* node) {
    if (!node) return;
    displayClasses(node->right);
    for (const auto& ip_class : node->classes) {
        std::cout << ip_class << " with " << node->access_count << " accesses" << std::endl;
    }
    displayClasses(node->left);
}

void BinaryTree::clear(TreeNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void BinaryTree::clear(ClassNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}