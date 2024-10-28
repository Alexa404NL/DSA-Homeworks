//
// Created by Alexa Nohemi Lara Carvajal on 18/10/24.
//

#ifndef DSA_HOMEWORKS_PRIORITY_Q_H
#define DSA_HOMEWORKS_PRIORITY_Q_H


template <class T>
class PriorityQueue {
    protected:
        T * pr;
        int tam;
        int capacity=100000;

    public:
        int size();
        bool empty();
        T top();
        void pop();
        void push(T);


        PriorityQueue<T>(int t) {
            pr = new T[t];
            tam=1;
        }

        PriorityQueue<T>() {
            T pr[capacity];
            tam=0;
        }

        ~PriorityQueue() {
            delete[] pr;
            tam=-1;
        }

};

//o(1)
    template <class T>
        int  PriorityQueue<T>::size(){
            return tam-1;
        }

//o(1)
    template <class T>
        bool  PriorityQueue<T>::empty(){
            if ((tam-1)==0){
                return true;
            } else {
                return false;
            }
        }
//o(1)
    template <class T>
        T PriorityQueue<T>::top(){
            return pr[0];
        }

//o(n)
    template <class T>
        void  PriorityQueue<T>::pop(){
            int n=tam;
            T temp = pr[0];
            pr[0] = pr[tam];
            pr[tam] = temp;
            tam--;
            for (int i=0; i<tam; i++) {
                int hijo;
                hijo = 2 * i;
                if ((hijo <= tam && pr[hijo] > pr[i])  || (hijo + 1 <= tam && pr[i] < pr[hijo + 1])) {
                    int hmayor;
                    hmayor = (pr[hijo] > pr[hijo + 1]) ? hijo : hijo + 1;
                    T temp = pr[i];
                    pr[i] = pr[hmayor];
                    pr[hmayor] = temp;
                }
            }
    }

//o(n)
    template <class T>
        void  PriorityQueue<T>::push(T dato) {
        int AP = tam;
        pr[tam] = dato;
        tam++;
        while (AP > 0 && pr[AP/2] < pr[AP]) {
            T parent = pr[AP/2];
            pr[AP/2]= pr[AP];
            pr[AP] = parent;
            AP /= 2;
        }
    }


#endif //DSA_HOMEWORKS_PRIORITY_Q_H
