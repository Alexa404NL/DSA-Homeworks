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
    const queue<T> & operator=(const queue &L); //sobrecarga de operador
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
     const queue<T> & queue<T>:: operator=(const queue<T> &q){
        if (this == &q) {
            return *this; // Revision de autoasignacion
        }
        delete[] arr;
        capacity=q.capacity;
        arr = new T[capacity];
        size= q.size;
        frente = q.frente;
        fondo = q.fondo;
        for (int i = q.frente; i <= q.fondo; i++)
            arr[i] = q.arr[i];
        return *this;
    }

template <class T>
    queue<T>::~queue(){
        delete[] arr;
    }

template <class T>
    void queue<T>::enQueue(T value){
        if ((frente == 0 && fondo == capacity - 1) || ((fondo + 1) % capacity == frente)){
            nuevaException ex("La cola esta llena");
            throw ex;
        } // cola vacia?
        else if (frente == -1) /* Se inserta primer elemento */{
            frente = fondo = 0;
            arr[fondo] = value;
        } else if (fondo == capacity -1 && frente != 0){
            // 2da condicion es redundante. Se incluye por claridad.
            fondo = 0;
            arr[fondo] = value;
        }

        else{
            fondo++;
            arr[fondo] = value;
        }

    /*
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
    cout << value << " enqueued to queue\n";*/
}

// extrae un elemento de la cola
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
    } else if (frente == capacity - 1)
        frente = 0;
    else
        frente++;

    return temp;

    /*
    if (size==0){
        nuevaException ex("La cola esta vacia");
        throw ex;
    }
    T item = arr[frente];
    frente = (frente + 1)% capacity;
    size = size - 1;
    return item;*/
}

template <class T>
    void queue<T>::mostrar(){
        if(frente<fondo) {
            for (int i = frente; i <= fondo; i++) {
                cout << arr[i] << " ";
            }
        } else {
            for (int i = frente; i>fondo; i++) {
                cout << arr[i] << " ";
                if (i == capacity - 1) {
                    break;
                }
            }
            if (fondo<frente) {
                for (int i = 0; i <= fondo; i++) {
                    cout << arr[i] << " ";
                }
            }
        }
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
