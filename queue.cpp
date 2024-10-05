//
// Created by Alexa Nohemi Lara Carvajal on 01/10/24.
//

#include "queue.h"
#include "exception.h"


int main() {
    queue<int> q(5);
    queue<int> nojalo(8);
    try{
        q.deQueue();
    }
    catch (nuevaException &ex1){
        cout << ex1.what() << endl;
    }

    q.enQueue(14);
    q.enQueue(22);
    q.enQueue(13);
    q.enQueue(-6);


    q.mostrar();
    cout<<endl;

    cout << "Extrayendo valor " << q.deQueue() << endl;

    cout << "Extrayendo valor " << q.deQueue() << endl;
    q.mostrar();
    cout<<endl;

    nojalo = q;
    nojalo.enQueue(1);
    nojalo.enQueue(2);
    nojalo.enQueue(3);
    cout<< "nojalo:"<< endl ;
    nojalo.mostrar();
    cout<<endl;
    nojalo.deQueue();
    nojalo.deQueue();
    nojalo.mostrar();
    cout<<endl;
    nojalo.enQueue(4);
    nojalo.enQueue(5);
    nojalo.mostrar();
    cout<<endl;
    nojalo.deQueue();
    nojalo.deQueue();
    nojalo.enQueue(9);
    nojalo.enQueue(10);
    nojalo.mostrar();
    cout<<endl;
    nojalo.deQueue();
    nojalo.deQueue();
    nojalo.enQueue(11);
    nojalo.enQueue(12);
    nojalo.mostrar();
    cout<<endl;
    nojalo.deQueue();
    nojalo.deQueue();
    nojalo.enQueue(13);
    nojalo.mostrar();
    cout<<endl;
    return 0;
}