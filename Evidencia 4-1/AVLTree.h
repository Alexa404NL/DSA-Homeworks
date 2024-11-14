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

        Node(const Key& k, const Value& v)
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int balanceFactor(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(Node* n) {
        if (n) {
            n->height = 1 + std::max(height(n->left), height(n->right));
        }
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* n) {
        updateHeight(n);

        if (balanceFactor(n) > 1) {
            if (balanceFactor(n->left) < 0) {
                n->left = rotateLeft(n->left);
            }
            return rotateRight(n);
        }

        if (balanceFactor(n) < -1) {
            if (balanceFactor(n->right) > 0) {
                n->right = rotateRight(n->right);
            }
            return rotateLeft(n);
        }

        return n;
    }

    Node* insert(Node* node, const Key& key, const Value& value) {
        if (!node) return new Node(key, value);

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            node->value = value;
        }

        return balance(node);
    }

    Node* find(Node* node, const Key& key) const {
        if (!node) return nullptr;

        if (key < node->key) {
            return find(node->left, key);
        } else if (key > node->key) {
            return find(node->right, key);
        } else {
            return node;
        }
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        clear(root);
    }

    void insert(const Key& key, const Value& value) {
        root = insert(root, key, value);
    }

    Value& operator[](const Key& key) {
        Node* node = find(root, key);
        if (node) {
            return node->value;
        } else {
            insert(key, Value());
            return find(root, key)->value;
        }
    }

    const Value& at(const Key& key) const {
        Node* node = find(root, key);
        if (!node) throw std::out_of_range("Key not found");
        return node->value;
    }

    bool contains(const Key& key) const {
        return find(root, key) != nullptr;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    // Iterator implementation
    class Iterator {
    private:
        std::stack<Node*> stack;

        void pushLeft(Node* node) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
        }

    public:
        Iterator(Node* root) {
            pushLeft(root);
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        bool operator==(const Iterator& other) const {
            return stack == other.stack;
        }

        Iterator& operator++() {
            Node* node = stack.top();
            stack.pop();
            if (node->right) {
                pushLeft(node->right);
            }
            return *this;
        }

        std::pair<const Key&, Value&> operator*() {
            Node* node = stack.top();
            return {node->key, node->value};
        }
    };

    Iterator begin() const {
        return Iterator(root);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};

#endif // AVLTREE_H