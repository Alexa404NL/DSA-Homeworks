
#ifndef DOUBLE_LINKED_LIST_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_LINKED_LIST_H

#include <iostream>
using namespace std;

template <class T>
class node
{
public:
    //node
    node(T data);
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

//cabeza lista
template <class T>
    class headlista{
    public:
        //node
        headlista(T data);
        //getters
        T getData();
        headlista<T> *getNext();
        //setters
        void setData(T data);
        void setNext(headlista<T> *next);

    private:
        T data;
        headlista<T> *next;
    };

//list

template <class T> //agrehar sobregarga de operador y cabeza como otro tipo de dato
    class DoublyLinkedList
    {
        node<T> *head;
        node<T> *tail;
    private:
        int size;

    public:
        //contructor
        DoublyLinkedList(){
            head = nullptr;
            tail = nullptr;
            size = 0;
        }
        //contructor de copia
        DoublyLinkedList(const DoublyLinkedList &l){
            head = l.head;
            node<T> *current = l.head;
            if (l.head == nullptr){
                return;
            }
            int value;
            while (current != nullptr){
                value=current->getData();
                insertAtEnd(value);
                current = current->getNext();
            }
            tail=l.tail;
        }

        //getter
        int longitud();

        // setters
        void imprimeLinkedList();
        void imprimealreves();
        void insertAtBeginning(T value);
        void insertAtEnd(T value);
        void insertPos(int pos, T value);
        void removeFirstNode();
        void removeLastNode();
        void deleteAtPosition(int position);
        // sobrecarga operador asignacion
        const DoublyLinkedList<T>& operator=(const DoublyLinkedList &);
    };

// definiciones de la clase node.

template <class T>
    inline node<T>::node(T data){
        this->data = data;
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
    inline void node<T>::setNext(node<T> *next){
        this->next = next;
    }

template <class T>
    inline void node<T>::setPrevious(node<T> *previous) {
     this->previous = previous;
    }


template <class T>
    const DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &L){
        if (L.size ==0){
            // lista vacia, no hay que copiar nada.
            head = nullptr;
            tail=nullptr;
            size = 0;
            return *this;
        }
        node<T> *current = L.head;
        node<T> *ptrcopia = nullptr;
        node<T> *newNode = new node<T>(current->getData());
        head = newNode;
        ptrcopia = newNode;
        current = current->getNext();
        for (int i = 1; i < L.size; i++){
            node<T> *newNode = new node<T>(current->getData());
            ptrcopia->setNext(newNode);
            ptrcopia = newNode;
            current = current->getNext();
        }
        size = L.size;
        return *this;
    }

template <class T>
    int DoublyLinkedList<T>::longitud(){
        return size;
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
        node<T> *current = tail;

        while (current != nullptr)
        {
            cout << current->getData() << " ";
            current = current->getPrevious();
        }
        cout << std::endl;
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
        node<T> *newNode = new node<T>(value);

        // Caso lista vacía
        if (head == nullptr){
            head = newNode;
        } else {

            // Recorrer la lista hasta el nodo final...
            node<T> *current = head;
            while (current->getNext() != nullptr) {
                current = current->getNext();
                //previous = previous->getPrevious();
            }

            // el puntero current está apuntando al nodo final.
            current->setNext(newNode);
        }
            size++;
    }

template <class T>
    void DoublyLinkedList<T>::insertPos(int pos, T value){
        if (pos < 1 || pos > size)
        {
            cout << "Posicion no permitida" << endl;
            return;
        }

        // Insertar al principio
        if (pos == 1)
        {
            insertAtBeginning(value);
            return;
        }

        // Recorrer la lista para encontrar el nodo anterior
        // al punto de inserción
        node<T> *prev = head;
        int count = 1;
        while (count < pos - 1 && prev != nullptr)
        {
            prev = prev->getNext();
            count++;
        }
        // Insertar
        node<T> *temp = new node<T>(value);
        temp->setNext(prev->getNext());
        prev->setNext(temp);
        size++;
    }

template <class T>
    void DoublyLinkedList<T>::removeFirstNode(){
        if (head == nullptr)
            return;

        node<T> *temp = head;
        head = head->getNext();
        delete temp;
        size--;
    }

template <class T>
    void DoublyLinkedList<T>::removeLastNode() {
        if (head == nullptr)
            return;

        // caso de un elemento..
        if (head->getNext() == nullptr)
        {
            delete head;
            size--;
            return;
        }

        // ir hasta el penuntimo elemento.
        node<T> *second_last = head;
        while ((second_last->getNext())->getNext() != nullptr)
            second_last = second_last->getNext();

        // Borrar el ultimo
        delete second_last->getNext();

        // el penultimo ahora es el último
        second_last->setNext(nullptr);
        size--;
    }

template <class T>
    void DoublyLinkedList<T>::deleteAtPosition(int position) {
        // Si la lista esta vacia o la posición no es valida
        if (head == nullptr || position < 1 || position > size)
        {
            return;
        }

        // If the head needs to be deleted
        if (position == 1)
        {
            node<T> *temp = head;
            head = head->getNext();
            delete temp;
            size--;
        }

        // recorrer lista hasta el nodo anterior al que se borrará
        node<T> *current = head;
        for (int i = 1; i < position - 1 && current != nullptr; i++)
        {
            current = current->getNext();
        }

        // Almacenar direccion nodo a borrar.
        node<T> *temp = current->getNext();

        // Update the links to bypass the node to be deleted
        current->setNext(current->getNext()->getNext());

        // Delete the node
        delete temp;
        size--;
    }


#endif //DOUBLE_LINKED_LIST_LINKED_LIST_H
