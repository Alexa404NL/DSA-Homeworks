#include "linked_list.h"
#include <iostream>

using namespace std;

int main(){
        DoublyLinkedList<string>  dll, inverted;
        dll.insertAtEnd("a");
        dll.insertAtEnd("z");
        dll.insertAtEnd("c");
        dll.insertAtEnd("w");

        cout << "Lista original:" << std::endl;
        dll.imprimeLinkedList();


        inverted=dll.invertir();
        cout << "Lista original & invertida:" << std::endl;
        dll.imprimeLinkedList();
        inverted.imprimeLinkedList();

        cout << "Posicion del elemento r: " << dll.buscar("r") << endl;
        cout << "Posicion del elemento w: " << dll.buscar("w") << endl;

        cout << "Lista actualizada (cambiar posicion 2 a valor de 'd'):" << endl;
        dll.update(2, "d");
        dll.imprimeLinkedList();

        cout << "Lista ordenada:" << endl;
        dll.ordenar();
        dll.imprimeLinkedList();


    return 0;
}
