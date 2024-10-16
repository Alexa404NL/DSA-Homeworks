//
// Created by Alexa Nohemi Lara Carvajal on 14/10/24.
//
#ifndef DSA_HOMEWORKS_BST_H
#define DSA_HOMEWORKS_BST_H

#include <iostream>
#include <queue>
#include <exception>

using namespace std;

//exception
class BSTex : public exception{
public:
    virtual const char *what() const throw(){
        return mensaje.c_str();
    }

    string mensaje;
    BSTex(string m){
        mensaje = m;
    }
};

template <class T>
class Node{ //nodo base
public:
    T data;
    Node *left, *right;
    int height;
    Node(T k): data(k), left(nullptr), right(nullptr), height(1){}
};

template <class T> class BST {
private:
    // Puntero a la raíz del árbol
    Node<T>* root;

    // O(1)
    int height(Node<T>* node){
        if (node == nullptr)
            return 0;
        return node->height;
    }

    //  O(h) donde h es la altura del arbol
    int height_tree(Node<T>* node) {
        if (node == nullptr)
            return 0;
        else {
            int lheight = height(node->left);
            int rheight = height(node->right);
            return (lheight > rheight) ? (lheight + 1) : (rheight + 1);
        }
    }

    // O(h) donde h es la altura del arbol
    Node<T>* insert(Node<T>* node, T data){
        // insercion en un ABB normal.
        if (node == nullptr)
            return new Node<T>(data);

        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        } else
            return node;

        // actualizar altura del padre
        node->height = 1
                       + max(height(node->left),
                             height(node->right));

        return node;
    }

    //O(N)
    void por_nivel(Node<T> * root) {
        if (root == nullptr)
            return;
        queue<Node<T>*> q;
        q.push(root);

        while (q.empty() == false) {

            Node<T>* node = q.front();
            cout << node->data << " ";
            q.pop();

            if (node->left != nullptr)
                q.push(node->left);

            if (node->right != nullptr)
                q.push(node->right);
        }
    }

    // O(N)
    void inorder(Node<T>* root){
        if (root != nullptr) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

    // O(N)
    void preorder(Node<T>* root){
        if (root != nullptr) {
            cout << root->data << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    // O(N)
    void postorder(Node<T>* root){
        if (root != nullptr) {
            postorder(root->left);
            postorder(root->right);
            cout << root->data << " ";
        }
    }

    // O(h) donde h es la altura del arbol
    bool search(Node<T>* root, T data){
        if (root == nullptr)
            return false;
        if (root->data == data)
            return true;
        if (data < root->data)
            return search(root->left, data);
        return search(root->right, data);
    }

    //O(h) h es la altura del arbol
    Node<T>* search_heigh_node(Node<T>* root, T data){
        if (root == nullptr)
            return root;
        if (root->data == data)
            return root;
        if (data < root->data)
            return search_heigh_node(root->left, data);
        return search_heigh_node(root->right, data);
    }

    //O(h) h es la altura del arbol
    bool displayAncestors(Node<T>* root, T target){
        if (root == NULL)
            return false;

        if (root->data == target)
            return true;

        if ( displayAncestors(root->left, target) || displayAncestors(root->right, target) ){
            cout << root->data << " ";
            return true;
        }
        return false;
    }

public:
    // Constructor
    BST(): root(nullptr){}

    // wrapper functions
    void insert(T data) { root = insert(root, data); }

    bool search(T data) { return search(root, data); }

    void printInorder(){
        inorder(root);
        cout << endl;
    }

    void printpreorder(){
        preorder(root);
        cout << endl;
    }

    void printpostorder(){
        postorder(root);
        cout << endl;
    }

    void printpornivel(){
        por_nivel(root);
        cout << endl;
    }

    int printhightree(){
        return height_tree(root);
    }

    int highnode(T value){
       int val= height(search_heigh_node(root, value));
       if (val==0){
           return -1;
       } else return val;
    }

    bool displayAncestors(T value){
       return displayAncestors(root, value);
    }
};



#endif //DSA_HOMEWORKS_BST_H
