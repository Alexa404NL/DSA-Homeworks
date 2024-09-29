// double linked list con cabeza
#ifndef DOUBLE_LINKED_LIST_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_LINKED_LIST_H

#include <iostream>
using namespace std;

template <class T>
class node{
    public:
        //node
        node(T data);
        node();
        //getters
        T getData();
        node<T> *getNext();
        node<T> *getPrevious();
        //setters
        void setData(T data);
        void setNext(node<T> *next);
        void setPrevious(node<T> *previous);

    private:
        T data;
        node<T> *next;
        node<T> *previous;
};

//list
template <class T> //agrehar sobregarga de operador y cabeza como otro tipo de dato
    class DoublyLinkedList{
        node<T> *head;
        node<T> *tail;
    private:
        int size;

    public:
        //contructor
        DoublyLinkedList(){
            tail= nullptr;
            head = new node<T>();
            size = 0;
        }

        //contructor de copia
        DoublyLinkedList(const DoublyLinkedList &l){
            tail = l.tail;
            head = l.head;
            size=l.size;
            node<T>* current = l.head->getNext();
            if (current == nullptr){
                return;
            }
            T value;
            while (current != nullptr){
                value=current->getData();
                insertAtEnd(value);
                current = current->getNext();
            }
        }

        // Destructor
        ~DoublyLinkedList() {
            node<T>* current = head->getNext(); // omitir el nodo centinela
            while (current) {
                node<T>* next = current->getNext();
                delete current;
                current = next;
            }
            delete head; // borrado del nodo cabeza
            size=0;
        }

        // métodos y setters
        void imprimeLinkedList();
        DoublyLinkedList<T> invertir();
        int buscar(T value);
        void update(int pos, T value);
        void ordenar();
        void insertAtEnd(T value);

        // sobrecarga operador asignacion
        const DoublyLinkedList<T>& operator=(const DoublyLinkedList &L);

        int longitud();
        int longitud() const;
    };

// definiciones de la clase node.

template <class T>
    inline node<T>::node(T data){
        this->data = data;
        this->next = nullptr;
        this->previous = nullptr;
    }

template <class T>
    inline node<T>::node(){
    this->data = T();
    this->next = nullptr;
    this->previous = nullptr;
}

template <class T>
    inline node<T> *node<T>::getNext(){
        if (next != nullptr)
            return next;
        else
            return nullptr;
    }

template <class T>
    inline node<T> *node<T>::getPrevious() {
        if (previous != nullptr)
            return previous;
        else
            return nullptr;
    }

template <class T>
    inline T node<T>::getData(){
        return data;
    }

template <class T>
    inline void node<T>::setData(T data){
        this->data = data;
    }

template <class T>
    int DoublyLinkedList<T>::longitud() {
        return size;
    }

template <class T>
    int DoublyLinkedList<T>::longitud() const {
    return size;
    }

template <class T>
    inline void node<T>::setNext(node<T> *next){
        this->next = next;
    }

template <class T>
    inline void node<T>::setPrevious(node<T> *previous) {
     this->previous = previous;
    }

//definición de métodos de linked list

template <class T>
    const DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &L){
        if (this == &L) {
            return *this; // Revision de autoasignacion
        }
        node<T>* temp = head->getNext(); // omitir el nodo centinela
        while (temp) {
            node<T> * sig = temp->getNext();
            delete temp;
            temp = sig;
        }
        head->setNext(nullptr);
        tail= nullptr;
        node<T> *current = L.head->getNext(); // omitir el nodo centinela
        node<T>* ultimo = head;
        while (current) {
            T value=current->getData();
            node<T>* newNode = new node<T>(value);
            ultimo->setNext(newNode);
            newNode->setPrevious(ultimo);
            ultimo = newNode;
            current = current->getNext();
            tail=newNode;
        }
        size = L.longitud();
        return *this;
    }

template <class T>
    void DoublyLinkedList<T>::imprimeLinkedList(){
        // Se comienza por el nodo de inicio
        node<T> *current = head;
        if (head == nullptr){
            cout << "Lista vacia.." << endl;
            return;
        }
        // recorre la lista hasta el final.
        while (current != nullptr)
        {
            // Visualiza el dato
            cout << current->getData() << " ";

            // Siguiente nodo
            current = current->getNext();
        }

        cout << std::endl;
    }

    /*                              Métodos de la tarea                             */

// complejidad de 0(n)
template <class T>
    DoublyLinkedList<T> DoublyLinkedList<T>::invertir(){
        DoublyLinkedList<T> copy;
        if (size == 0) {
            cout << "Lista vacia" << endl;
        }   else {
            node<T> *temp = tail;
            while (temp != nullptr) {
                copy.insertAtEnd(temp->getData());
                temp = temp->getPrevious();
            }
        }
            return copy;
    }

// complejidad de 0(n)
template <class T>
    int DoublyLinkedList<T>::buscar(T value){
        node<T>* current = head->getNext(); // omitir el nodo centinela
        int position = 1;
        while (current) {
            if (current->getData() == value) {
                return position;
            }
            current = current->getNext();
            position++;
        }
        return -1;  // Elemento no encontrado
    }

// complejidad de 0(n)
template <class T>
    void DoublyLinkedList<T>::update(int pos, T value){
        node<T>* current = head->getNext(); // omitir el nodo centinela
        for (int i = 1; i < pos; ++i) {
            if (!current) {
                return;  // Posicion de nodo invalida
            }
            current = current->getNext();
        }
            current->setData(value);
    }


// Ordena la lista en orden ascendente usando el algoritmo de Bubble Sort
// Complexity: O(n^2)
template <class T>
    void DoublyLinkedList<T>::ordenar(){
        if (!head->getNext()) {
            return;
        }
        node<T>* current = head->getNext(); // omitir el nodo centinela
        while (current) {
            node<T>* index = current->getNext();
            while (index) {
                if (current->getData() > index->getData()) {
                    T temp=current->getData();
                    current->setData(index->getData());
                    index->setData(temp);
                }
                index = index->getNext();
            }
            current = current->getNext();
        }
    }

// complejidad de 0(n)
template <class T>
    void DoublyLinkedList<T>::insertAtEnd(T value){
        node<T>* newNode = new node<T>(value);
        if (head->getNext() == nullptr) {
            head->setNext(newNode);
            newNode->setPrevious(head);
            tail = newNode;
            size++;
            return;
        } else{
            tail->setNext(newNode);
            newNode->setPrevious(tail);
            tail = newNode;
            size++;
        }
    }



#endif //DOUBLE_LINKED_LIST_LINKED_LIST_H
