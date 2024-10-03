#ifndef QUEUE_H
#define QUEUE_H
#include "exception.h"
template <class T>
class queue{
    // frente, fondo y tamaño de la cola.
    int frente, fondo, size;
    T *arr;

public:
    queue(int cap); // constructor
    queue(const queue &s); // constructor de copia
    const queue & operator=(const queue &L); //sobrecarga de operador
    ~queue();     // Destructor
    void enQueue(T value); //insertar al final
    T deQueue(); //eliminar
    T getFront();
    bool isFull();
    bool isEmpty();
};


template <class T>
    queue<T>::queue(int cap){
        frente = fondo = -1;
        size = cap;
        arr = new T[size];
    }

template <class T>
    queue<T>::queue(const queue &q){
        frente = q.frente;
        fondo = q.fondo;
        size= q.size;
        arr = new T[size];
        for (int i = 0; i <= fondo; i++)
            arr[i] = q.pila[i];
    }

template <class T>
    const queue<T> &queue<T>::operator=(const queue<T> &q){
        if (this == &q) {
            return; // Revision de autoasignacion
        }
        arr = new T[size];
        for (int i = 0; i <= q.fondo; i++)
            arr[i] = q.pila[i];

        size = q.longitud();
        return *this;
    }

template <class T>
    queue<T>::~queue(){
        delete[] arr;
    }

template <class T>
    void queue<T>::enQueue(T value){
        if ((frente == 0 && fondo == size - 1) || ((fondo + 1) % size == frente)){
            nuevaException ex("La cola esta llena");
            throw ex;
        }
        /* falta*/
    }

// extrae un elemento de la cola circular
template <class T>
    T queue<T>::deQueue() {
        T temp;
        if (size==0){
            nuevaException ex("La cola esta vacia");
            throw ex;
        }

        /* falta*/
    }



#endif //DOUBLE_LINKED_LIST_QUEUE_H
