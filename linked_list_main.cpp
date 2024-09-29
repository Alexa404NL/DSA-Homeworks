#include "linked_list.h"
#include <iostream>

using namespace std;

int main(){
        DoublyLinkedList<int>  dll;
        dll.insertAtEnd(3);
        dll.insertAtEnd(1);
        dll.insertAtEnd(4);
        dll.insertAtEnd(2);

        std::cout << "Original List:" << std::endl;
        dll.imprimeLinkedList();
        dll.imprimealreves();

        return 0;
}
