//
// Created by Alexa Nohemi Lara Carvajal on 18/10/24.
//

#include <iostream>
#include "Priority_q.h"
using namespace std;


int main(){
    PriorityQueue<int> cola (5); // prueba 1
    PriorityQueue<char> cola1 (10); //  prueba 2
    PriorityQueue<int> cola2 (4); //  prueba 3
    PriorityQueue<char> cola3 (6); //  prueba 4

//prueba cola 1
    if (cola.empty()) cout << "cola vacia\n";
    cout<< "Hata arriba esta: ";
    cola.push(10);
    cout << cola.top() << "\n";
    cout<< "Hata arriba esta: ";
    cola.push(23);
    cout << cola.top() << "\n";
    cout<< "Hata arriba esta: ";
    cola.push(33);
    cout << cola.top() << "\n";
    cout<< "Hata arriba esta: ";
    cola.push(4);
    cout << cola.top() << "\n";
    cout<< "Hata arriba esta: ";
    cola.push(50);
    cout << cola.top() << "\n";

    cout << "se borró ";
    cout << cola.top() << "\n";
    cola.pop();

    cout << "se borró ";
    cout << cola.top() << "\n";
    cola.pop();

    cout << "se borró ";
    cout << cola.top() << "\n";
    cola.pop();
    cout << "el tamaño de la cola ahora es: "<< cola.size()<<"\n";

    cout << "se borró ";
    cout << cola.top() << "\n";
    cola.pop();

    cout << "se borró ";
    cout << cola.top() << "\n";
    cola.pop();

    if (cola.empty()) cout << "cola vacia\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";

//prueba cola 2
    cola1.push('a');
    cout << cola1.top() << "\n";
    cola1.push('b');
    cout << cola1.top() << "\n";
    cola1.push('A');
    cout << cola1.top() << "\n";
    cola1.pop();
    cout << cola1.top() << "\n";
    cola1.pop();
    cout << cola1.top() << "\n";

    cout << "\n";
    cout << "\n";
    cout << "\n";

//prueba cola 3

    cola2.push(10);
    cola2.push(23);
    cola2.push(33);
    cola2.push(4);

    if (cola2.empty()){
        cout << "vacía";
    } else cout << "no esta vacia, su tamaño es "<< cola2.size();


    cout << "\n";
    cout << "\n";
    cout << "\n";

//prueba cola 4
    cola3.push('g');
    cout << cola3.top() << "\n";
    cola3.push('h');
    cout << cola3.top() << "\n";
    cola3.push('j');
    cola3.push('z');
    cola3.push('z');
    cola3.push('v');
    cout << cola3.top() << "\n";
    cola3.pop();
    cout << cola3.top() << "\n";
    cola3.pop();
    cout << cola3.top() << "\n";

    return 0;
}