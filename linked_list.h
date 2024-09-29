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
            node<T>* current = l.head->next;
            if (current == nullptr){
                return;
            }
            int value;
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
        }

        //getter
        int longitud();

        // métodos y setters
        void imprimeLinkedList();
        void imprimealreves();
        void insertAtBeginning(T value);
        void insertAtEnd(T value);

        // sobrecarga operador asignacion
        const DoublyLinkedList<T>& operator=(const DoublyLinkedList &L);

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
    int DoublyLinkedList<T>::longitud() const{
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

template <class T>
    void DoublyLinkedList<T>::imprimealreves() {
        node<T>* temp = head;
        if (temp == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }

        // Move to the end of the list.
        while (temp->getNext() != nullptr) {
            temp = temp->getNext();
        }

        // Traverse backwards.
        cout << "Reverse List: ";
        while (temp != nullptr) {
            cout << temp->getData() << " ";
            temp = temp->getPrevious();
        }
        cout << endl;
    }

template <class T>
    void DoublyLinkedList<T>::insertAtBeginning(T value){
        node<T> *newNode = new node<T>(value);
        newNode->setNext(head);
        head = newNode;
        size++;
    }

template <class T>
    void DoublyLinkedList<T>::insertAtEnd(T value){
        node<T>* newNode = new node<T>(value);
        if (head->getNext() == nullptr) {
            head->setNext(newNode);
            newNode->setPrevious(head);
            tail = newNode;
            return;
        } else{
            tail->setNext(newNode);
            newNode->setPrevious(tail);
            tail = newNode;
        }
    }



#endif //DOUBLE_LINKED_LIST_LINKED_LIST_H
