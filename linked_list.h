
#ifndef DOUBLE_LINKED_LIST_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_LINKED_LIST_H

#include <iostream>
using namespace std;

template <class T>
class node
{
public:
    node(T data);
    T getData();
    node<T> *getNext();
    void setData(T data);
    void setNext(node<T> *next);

private:
    T data;
    node<T> *next;
};

template <class T>
class LinkedList
{
    node<T> *head;

private:
    int size;

public:
    LinkedList()
    {
        head = nullptr;
        size = 0;
    }
    void imprimeLinkedList();
    int longitud();
    void insertAtBeginning(T value);
    void insertAtEnd(T value);
    void insertPos(int pos, T value);
    void removeFirstNode();
    void removeLastNode();
    void deleteAtPosition(int position);
};

// definiciones de la clase node.

template <class T>
inline node<T>::node(T data)
{
    this->data = data;
    this->next = nullptr;
}

template <class T>
inline node<T> *node<T>::getNext()
{
    if (next != nullptr)
        return next;
    else
        return nullptr;
}

template <class T>
inline T node<T>::getData()
{
    return data;
}

template <class T>
inline void node<T>::setData(T data)
{
    this->data = data;
}

template <class T>
inline void node<T>::setNext(node<T> *next)
{
    this->next = next;
}

// fin definiciones de la clase node.

// definiciones de la clase LinkedList

/* Operaciones de la lista a implementarse

*Agregar: agrega un elemento a la sucesión. El agregar para las listas enlazadas se realiza en 3 posiciones, al principio, al final y en otra posición intermedia.
*Eliminar: elimina un elemento de la sucesión (no actúa con la sucesión vacía). Eliminar para las listas enlazadas se realiza en 3 posiciones, al principio, al final y en otra posición intermedia.
Consultar: devuelve un elemento de la sucesión de acuerdo a una posición dada como dato (no actúa con la sucesión vacía)
Vacia: nos dice si está vacía o no. Que una lista esté vacía significa que el puntero al primer elemento es NULO.
Vaciar: Elimina todos los elementos de una lista.
*longitud: Nos dice el tamaño o cantidad de elementos que contiene la lista.  (Longitud())
Concatenar: Unir dos listas.
Invertir: Invierte el orden de los elementos de la lista.
Ordenar: Ordena por algún criterio los elementos de la lista.
Insertar en Orden: Inserta en la posición que garantice un orden predefinido. La lista siempre estará ordenada.
intercambiar: intercambia dos elementos de la lista.
*imprime: Visualiza los elementos de la lista.

*/

template <class T>
int LinkedList<T>::longitud()
{
    return size;
}

template <class T>
void LinkedList<T>::imprimeLinkedList()
{
    // Se comienza por el nodo de inicio
    node<T> *current = head;
    if (head == nullptr)
    {
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
void LinkedList<T>::insertAtBeginning(T value)
{
    node<T> *newNode = new node<T>(value);
    newNode->setNext(head);
    head = newNode;
    size++;
}

template <class T>
void LinkedList<T>::insertAtEnd(T value)
{
    node<T> *newNode = new node<T>(value);

    // Caso lista vacía
    if (head == nullptr)
        head = newNode;

    // Recorrer la lista hasta el nodo final...
    node<T> *current = head;
    while (current->getNext() != nullptr)
    {
        current = current->getNext();
    }

    // el puntero current está apuntando al nodo final.
    current->setNext(newNode);
    size++;
}

template <class T>
void LinkedList<T>::insertPos(int pos, T value)
{
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
void LinkedList<T>::removeFirstNode()
{
    if (head == nullptr)
        return;

    node<T> *temp = head;
    head = head->getNext();
    delete temp;
    size--;
}

template <class T>
void LinkedList<T>::removeLastNode()
{
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
void LinkedList<T>::deleteAtPosition(int position)
{
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
