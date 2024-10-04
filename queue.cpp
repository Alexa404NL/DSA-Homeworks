//
// Created by Alexa Nohemi Lara Carvajal on 01/10/24.
//

#include "queue.h"
#include "exception.h"


int main() {
    queue<int> q(5);
    queue<int> lol(8);
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


    lol = q;
    lol.enQueue(1);
    lol.enQueue(2);
    lol.enQueue(3);
    cout<< "lol:"<< endl ;
    lol.mostrar();
    cout<<endl;
    return 0;
}