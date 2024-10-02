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
    const queue & operator=(const queue &L);                //sobrecarga de operador
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
    queue<T>::~queue(){
        delete[] arr;
    }

template <class T>
    void queue<T>::enQueue(T value){
        if ((frente == 0 && fondo == size - 1) || ((fondo + 1) % size == frente)){
            nuevaException ex("La cola esta llena");
            throw ex;
        } // cola vacia?
        else if (frente == -1) /* Se inserta primer elemento */{
            frente = fondo = 0;
            arr[fondo] = value;
        }
        else if (fondo == size - 1 && frente != 0){
            // 2da condicion es redundante. Se incluye por claridad.
            fondo = 0;
            arr[fondo] = value;
        }

        else{
            fondo++;
            arr[fondo] = value;
        }
    }

// extrae un elemento de la cola circular
template <class T>
    T queue<T>::deQueue() {
        T temp;
        if (frente == -1){
            nuevaException ex("La cola esta vacia");
            throw ex;
            return temp;
        }

        temp = arr[frente];
        if (frente == fondo){
            frente = -1;
            fondo = -1;
        }
        else if (frente == size - 1)
            frente = 0;
        else
            frente++;

        return temp;
    }



#endif //DOUBLE_LINKED_LIST_QUEUE_H
