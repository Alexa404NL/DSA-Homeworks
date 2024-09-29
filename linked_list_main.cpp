#include "linked_list.h"
#include <iostream>

using namespace std;

int main(){
        DoublyLinkedList<string>  dll, mort;
        dll.insertAtEnd("a");
        dll.insertAtEnd("c");
        dll.insertAtEnd("f");
        dll.insertAtEnd("r");

        std::cout << "Original List:" << std::endl;
        dll.imprimeLinkedList();
        dll.imprimealreves();

        mort=dll;
        mort.imprimeLinkedList();
        mort.insertAtEnd(" lol ");
        dll.imprimeLinkedList();
        mort.imprimeLinkedList();

        return 0;
}
