#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int data = 0) : data(data), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    // Constructor default
    DoublyLinkedList() {
        head = new Node(); // Nodo head como nodo centinela
        tail = nullptr;
    }

    // Constructor copia
    DoublyLinkedList(const DoublyLinkedList& other) {
        head = new Node(); // Nodo head como nodo centinela
        tail = nullptr;
        Node* current = other.head->next; // Omitir el nodo centinela
        while (current) {
            append(current->data);
            current = current->next;
        }
    }

    // Destructor
    ~DoublyLinkedList() {
        destroy();
        delete head; // borrado del nodo centinela
    }

    // Sobrecarga del operador de asignacion
    const DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this == &other) {
            return *this; // Revision de autoasignacion
        }
        destroy(); // Limpieza de la lista actual
        Node* current = other.head->next; // omitir el nodo centinela
        while (current) {
            append(current->data);
            current = current->next;
        }
        return *this;
    }

    // Agrega un nuevo nodo al final de la lista con el valor dado
    void append(int data) {
        Node* newNode = new Node(data);
        if (!head->next) { // si la lista esta vacia
            head->next = newNode;
            newNode->prev = head;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Muestra los elementos de la lista
    void display() const {
        Node* current = head->next; // omitir el nodo centinela
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Invierte la lista y regresa una nueva lista con los elementos invertidos
    // Complexity: O(n)
    DoublyLinkedList invertir() const {
        DoublyLinkedList newDll;
        Node* current = tail;
        while (current && current != head) {
            newDll.append(current->data);
            current = current->prev;
        }
        return newDll;
    }

    // Busca un elemento en la lista y regresa su posicion
    // Complexity: O(n)
    int buscar(int value) const {
        Node* current = head->next; // omitir el nodo centinela
        int position = 0;
        while (current) {
            if (current->data == value) {
                return position;
            }
            current = current->next;
            position++;
        }
        return -1;  // Elemento no encontrado
    }

    // Actualiza el valor de un nodo en la posicion dada
    // Complexity: O(n)
    void update(int position, int newValue) {
        Node* current = head->next; // omitir el nodo centinela
        for (int i = 0; i < position; ++i) {
            if (!current) {
                return;  // Posicion de nodo invalida
            }
            current = current->next;
        }
        if (current) {
            current->data = newValue;
        }
    }

    // Ordena la lista en orden ascendente usando el algoritmo de Bubble Sort
    // Complexity: O(n^2)
    void ordenar() {
        if (!head->next) {
            return;
        }
        Node* current = head->next; // omitir el nodo centinela
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

    // Limpia la lista y libera la memoria de los nodos
    void destroy() {
        Node* current = head->next; // omitir el nodo centinela
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head->next = nullptr;
        tail = nullptr;
    }
};

// Ejemplo de uso de la clase DoublyLinkedList:
int main() {
    DoublyLinkedList dll;
    dll.append(3);
    dll.append(1);
    dll.append(4);
    dll.append(2);

    cout << "Lista original:" << endl;
    dll.display();

    cout << "Lista invertida y lista original:" << endl;
    DoublyLinkedList invertedDll = dll.invertir();
    invertedDll.display();
    dll.display();

    cout << "Posicion del elemento 4: " << dll.buscar(4) << endl;

    cout << "Lista actualizada (posicion 2 a la 5):" << endl;
    dll.update(2, 5);
    dll.display();

    cout << "Lista ordenada:" << endl;
    dll.ordenar();
    dll.display();

    // Pruebas de copia de listas usando el operador de asignacion y el constructor de copia
    DoublyLinkedList dll2;
    dll2 = dll;
    cout << "Lista copiada usando el operador de asignacion:" << endl;
    dll2.display();

    DoublyLinkedList dll3(dll);
    cout << "Lista copiada usando el constructor de copia:" << endl;
    dll3.display();

    return 0;
}

// Output
// Lista original:
// 3 1 4 2 
// Lista invertida y lista original:
// 2 4 1 3 
// 3 1 4 2 
// Posicion del elemento 4: 2
// Lista actualizada (posicion 2 a la 5):
// 3 1 5 2 
// Lista ordenada:
// 1 2 3 5
// Lista copiada usando el operador de asignacion:
// 1 2 3 5
// Lista copiada usando el constructor de copia:
// 1 2 3 5