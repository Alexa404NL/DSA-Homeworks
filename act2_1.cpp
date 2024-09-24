#include <iostream>

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int data) : data(data), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void append(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void display() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

DoublyLinkedList invertir(DoublyLinkedList& dll) {
    DoublyLinkedList newDll;
    Node* current = dll.tail;
    while (current) {
        newDll.append(current->data);
        current = current->prev;
    }
    return newDll;
}

int buscar(DoublyLinkedList& dll, int value) {
    Node* current = dll.head;
    int position = 0;
    while (current) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1;  // Element not found
}

void update(DoublyLinkedList& dll, int position, int newValue) {
    Node* current = dll.head;
    for (int i = 0; i < position; ++i) {
        if (!current) {
            return;  // Position out of bounds
        }
        current = current->next;
    }
    if (current) {
        current->data = newValue;
    }
}

void ordenar(DoublyLinkedList& dll) {
    if (!dll.head) {
        return;
    }
    Node* current = dll.head;
    while (current) {
        Node* index = current->next;
        while (index) {
            if (current->data > index->data) {
                std::swap(current->data, index->data);
            }
            index = index->next;
        }
        current = current->next;
    }
}

// Complexity Analysis:
// invertir: O(n)
// buscar: O(n)
// update: O(n)
// ordenar: O(n^2) (Bubble Sort)

// Usage Example:

int main() {
    DoublyLinkedList dll;
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