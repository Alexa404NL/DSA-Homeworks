#include <iostream>
#include "linked_list.h"
using namespace std;

int main(){
    DoublyLinkedList  dll;
    dll.append(3);
    dll.append(1);
    dll.append(4);
    dll.append(2);

    std::cout << "Original List:" << std::endl;
    dll.display();

    std::cout << "Inverted List:" << std::endl;
    DoublyLinkedList invertedDll = invertir(dll);
    invertedDll.display();

    std::cout << "Position of element 4: " << buscar(dll, 4) << std::endl;

    std::cout << "Updated List (position 2 to 5):" << std::endl;
    update(dll, 2, 5);
    dll.display();

    std::cout << "Sorted List:" << std::endl;
    ordenar(dll);
    dll.display();

    return 0;


}