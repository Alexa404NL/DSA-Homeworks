#ifndef QUEUE_H
#define QUEUE_H
#include "exception.h"
template <class T>
class queue{
    // frente, fondo y tamaño de la cola.
    int frente, fondo, size, capacity;
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
    void mostrar();
};


template <class T>
    queue<T>::queue(int cap){
        frente = fondo = -1;
        size=0;
        capacity = cap;
        arr = new T[capacity];
    }

template <class T>
    queue<T>::queue(const queue &q){
        frente = q.frente;
        fondo = q.fondo;
        size =q.size;
        capacity= q.capacity;
        arr = new T[capacity];
        for (int i = 0; i <= size; i++)
            arr[i] = q[i];
    }

template <class T>
    const queue<T> &queue<T>::operator=(const queue<T> &q){
        if (this == &q) {
            return *this; // Revision de autoasignacion
        }
        delete[] arr;
        arr = new T[capacity];
        for (int i = 0; i <= q.size; i++)
            arr[i] = q[i];
        size= q.size;
        frente = q.frente;
        fondo = q.fondo;
        return *this;
    }

template <class T>
    queue<T>::~queue(){
        delete[] arr;
    }

template <class T>
    void queue<T>::enQueue(T value){
        if (size==capacity){
            nuevaException ex("La cola esta llena");
            throw ex;
        }
        fondo = (fondo + 1)% capacity;
        if (size==0){
            frente= (frente + 1)% capacity;
        }
        arr[fondo] = value;
        size += 1;
        cout << value << " enqueued to queue\n";
    }

// extrae un elemento de la cola
template <class T>
    T queue<T>::deQueue() {
        if (size==0){
            nuevaException ex("La cola esta vacia");
            throw ex;
        }
        T item = arr[frente];
        frente = (frente + 1)% capacity;
        size = size - 1;
        return item;
    }
template <class T>
    void queue<T>::mostrar(){
        for (int i = frente; i <= fondo; i++)
           cout << arr[i] << " ";
    }

template <class T>
    T queue<T>::getFront(){
        if (arr->isEmpty()){
            nuevaException ex("La cola esta vacia");
            throw ex;
        }
        return arr[frente];
    }

template <class T>
    bool queue<T>::isEmpty(){
        return (size == 0);
    }
template <class T>
    bool queue<T>::isFull(){
        return (size == capacity);
    }



#endif //DOUBLE_LINKED_LIST_QUEUE_H
