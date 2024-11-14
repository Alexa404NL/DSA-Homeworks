#include "AVLTree.h"

template <typename Key, typename Value>
AVLTree<Key, Value>::Node::Node(const Key& k, const Value& v)
    : key(k), value(v), left(nullptr), right(nullptr), height(1) {}

template <typename Key, typename Value>
int AVLTree<Key, Value>::height(Node* n) {
    return n ? n->height : 0;
}

template <typename Key, typename Value>
int AVLTree<Key, Value>::balanceFactor(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::updateHeight(Node* n) {
    if (n) {
        n->height = 1 + std::max(height(n->left), height(n->right));
    }
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::balance(Node* n) {
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

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::insert(Node* node, const Key& key, const Value& value) {
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

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::find(Node* node, const Key& key) const {
    if (!node) return nullptr;

    if (key < node->key) {
        return find(node->left, key);
    } else if (key > node->key) {
        return find(node->right, key);
    } else {
        return node;
    }
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename Key, typename Value>
AVLTree<Key, Value>::AVLTree() : root(nullptr) {}

template <typename Key, typename Value>
AVLTree<Key, Value>::~AVLTree() {
    clear(root);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::insert(const Key& key, const Value& value) {
    root = insert(root, key, value);
}

template <typename Key, typename Value>
Value& AVLTree<Key, Value>::operator[](const Key& key) {
    Node* node = find(root, key);
    if (node) {
        return node->value;
    } else {
        root = insert(root, key, Value());
        return find(root, key)->value;
    }
}

template <typename Key, typename Value>
const Value& AVLTree<Key, Value>::at(const Key& key) const {
    Node* node = find(root, key);
    if (!node) throw std::out_of_range("Key not found");
    return node->value;
}

template <typename Key, typename Value>
bool AVLTree<Key, Value>::contains(const Key& key) const {
    return find(root, key) != nullptr;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::clear() {
    clear(root);
    root = nullptr;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::Iterator::pushLeft(Node* node) {
    while (node) {
        stack.push(node);
        node = node->left;
    }
}

template <typename Key, typename Value>
AVLTree<Key, Value>::Iterator::Iterator(Node* root) {
    pushLeft(root);
}

template <typename Key, typename Value>
bool AVLTree<Key, Value>::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

template <typename Key, typename Value>
bool AVLTree<Key, Value>::Iterator::operator==(const Iterator& other) const {
    return stack == other.stack;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator& AVLTree<Key, Value>::Iterator::operator++() {
    Node* node = stack.top();
    stack.pop();
    if (node->right) {
        pushLeft(node->right);
    }
    return *this;
}

template <typename Key, typename Value>
std::pair<const Key&, Value&> AVLTree<Key, Value>::Iterator::operator*() {
    Node* node = stack.top();
    return {node->key, node->value};
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator AVLTree<Key, Value>::begin() const {
    return Iterator(root);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator AVLTree<Key, Value>::end() const {
    return Iterator(nullptr);
}

// Explicit template instantiation
template class AVLTree<std::string, std::vector<std::string>>;