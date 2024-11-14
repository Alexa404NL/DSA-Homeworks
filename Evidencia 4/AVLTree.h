#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <algorithm>
#include <stack>

template <typename Key, typename Value>
class AVLTree {
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        int height;

        Node(const Key& k, const Value& v);
    };

    Node* root;

    int height(Node* n);
    int balanceFactor(Node* n);
    void updateHeight(Node* n);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* n);
    Node* insert(Node* node, const Key& key, const Value& value);
    Node* find(Node* node, const Key& key) const;
    void clear(Node* node);

public:
    AVLTree();
    ~AVLTree();
    void insert(const Key& key, const Value& value);
    Value& operator[](const Key& key);
    const Value& at(const Key& key) const;
    bool contains(const Key& key) const;
    void clear();

    class Iterator {
    private:
        std::stack<Node*> stack;
        void pushLeft(Node* node);

    public:
        Iterator(Node* root);
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        Iterator& operator++();
        std::pair<const Key&, Value&> operator*();
    };

    Iterator begin() const;
    Iterator end() const;
};

#endif // AVLTREE_H