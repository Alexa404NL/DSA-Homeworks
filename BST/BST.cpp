//
// Created by Alexa Nohemi Lara Carvajal on 14/10/24.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BST.h"
using namespace std;

BST<int> intTree(){
    BST<int> arbol;
    arbol.insert(50);
    arbol.insert( 30);
    arbol.insert(20);
    arbol.insert(40);
    arbol.insert( 70);
    arbol.insert(60);
    arbol.insert(80);
    return arbol;

    // arbol
    //      50
    //     /  \
    //    30   70
    //   / \   / \
    //  20 40 60 80
}

BST<char> charTree(){
    BST<char> arbol;
    arbol.insert('a');
    arbol.insert( 'c');
    arbol.insert('p');
    arbol.insert('d');
    arbol.insert( 'z');
    arbol.insert('w');
    arbol.insert('o');
    return arbol;

    // arbol
    //        a
    //        \
    //         c
    //          \
    //           p
    //          / \
    //         d   z
    //         \   /
    //         o   w
}

int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

BST<int> random_intTree(){ //arbol random
    BST<int> arbol;
    int data;
    for (int i=0; i<10; i++) {
        data=generateRandomNumber(0, 100);
        arbol.insert(data);
    }
    return arbol;
}