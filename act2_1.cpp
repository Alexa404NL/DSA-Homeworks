#include <iostream>

using namespace std;

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

    // Default constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Copy constructor
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr) {
        Node* current = other.head;
        while (current) {
            append(current->data);
            current = current->next;
        }
    }

    // Destructor
    ~DoublyLinkedList() {
        destroy();
    }

    // Assignment operator overload
    const DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this == &other) {
            return *this; // Self-assignment check
        }
        destroy(); // Clean up existing list
        Node* current = other.head;
        while (current) {
            append(current->data);
            current = current->next;
        }
        return *this;
    }

    // Appends a new node with the given data to the end of the list
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

    // Displays the elements of the list
    void display() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Inverts the list and returns a new list with the elements in reverse order
    // Complexity: O(n)
    DoublyLinkedList invertir() const {
        DoublyLinkedList newDll;
        Node* current = tail;
        while (current) {
            newDll.append(current->data);
            current = current->prev;
        }
        return newDll;
    }

    // Searches for the first occurrence of the given value and returns its position
    // Complexity: O(n)
    int buscar(int value) const {
        Node* current = head;
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

    // Updates the value of the node at the given position
    // Complexity: O(n)
    void update(int position, int newValue) {
        Node* current = head;
        for (int i = 1; i < position; ++i) {
            if (!current) {
                return;  // Position out of bounds
            }
            current = current->next;
        }
        if (current) {
            current->data = newValue;
        }
    }

    // Sorts the list using bubble sort
    // Complexity: O(n^2)
    void ordenar() {
        if (!head) {
            return;
        }
        Node* current = head;
        while (current) {
            Node* index = current->next;
            while (index) {
                if (current->data > index->data) {
                    swap(current->data, index->data);
                }
                index = index->next;
            }
            current = current->next;
        }
    }

    // Destroys the list and frees the memory
    void destroy() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
    }
};

// Usage Example:
int main() {
    DoublyLinkedList dll;
    dll.append(3);
    dll.append(1);
    dll.append(4);
    dll.append(2);

    cout << "Original List:" << endl;
    dll.display();

    cout << "Inverted List & original list:" << endl;
    DoublyLinkedList invertedDll = dll.invertir();
    invertedDll.display();
    dll.display();


    cout << "Position of element 4: " << dll.buscar(4) << endl;

    cout << "Updated List (position 2 to 5):" << endl;
    dll.update(2, 5);
    dll.display();

    cout << "Sorted List:" << endl;
    dll.ordenar();
    dll.display();

    // Testing assignment operator
    DoublyLinkedList dll2;
    dll2 = dll;
    cout << "Copied List using assignment operator:" << endl;
    dll2.display();

    // Testing copy constructor
    DoublyLinkedList dll3(dll);
    cout << "Copied List using copy constructor:" << endl;
    dll3.display();

    return 0;
}