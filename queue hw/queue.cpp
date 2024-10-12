//
// Created by Alexa Nohemi Lara Carvajal on 01/10/24.
//

#include "queue.h"
#include "exception.h"


int main() {

    queue<string> q1(5);
    queue<string> q2(8);
    queue<string> prueba(15); //incrementar en caso de poner valores más grandes
    int t=0;
    string temp="";
    string consultas[6]={"llamada operaciones", "consulta banco","retiro","baja de cuenta","nueva cuenta","consulta saldo"};

    /*                                    1er caso de prueba                              */
    try {
        for(string x:consultas){
            if (q1.isFull()) {
                temp=x;
            }
            q1.enQueue(x);
        }
    }
    catch (nuevaException &ex1){
        cout << ex1.what() << endl;
        q2=q1;
        //dividir carga operador 2 comienza a la mitad de la fila
        q2.deQueue();
        q2.deQueue();
        q2.deQueue();
        q2.enQueue(temp);
        cout << "se trajo un nuevo operador " <<endl;
        while(!q2.isEmpty()) {
            if(!q2.isEmpty()) {
                cout << "operador dos atiende: " << q2.deQueue() << endl;
            }
        }
    }


    /*                                    2ndo caso de prueba                              */
    cout << "¿Cuántas consultas se harán? "<< endl;
    cin>>t;
    prueba.enQueue("consulta 0");
    prueba.enQueue("consulta 1");
    int cont=1;
    while (t--){
        string c="consulta "+std::to_string(cont+1);
        string d="consulta "+std::to_string(cont+2);
        prueba.enQueue(c);
        prueba.enQueue(d);
        prueba.deQueue();
        prueba.mostrar();
        cont+=2;
    }

    return 0;
}