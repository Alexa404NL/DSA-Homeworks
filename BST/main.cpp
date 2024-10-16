//
// Created by Alexa Nohemi Lara Carvajal on 14/10/24.
//

#include <iostream>
#include "BST.h"
#include "BST.cpp"
using namespace std;

int main(){
    int choice, data;

    //casos de prueba
    BST<int> Tree1 = intTree(); // creando caso de prueba 1
    BST<char> Tree2 = charTree(); // creando caso de prueba 2
    BST<int> Tree3 = random_intTree(); // creando caso de prueba 3
    BST<int> Tree4 = random_intTree(); // creando caso de prueba 4

    do {
        cout << "\n--- BST Menu ---" << endl;
        cout << "1. Traverse BST (Preorder, Inorder, Postorder, Level-order)" << endl;
        cout << "2. Get Height of BST" << endl;
        cout << "3. Display Ancestors of a Node" << endl;
        cout << "4. Find the Level of a Node" << endl;
        cout << "5. Exit" << endl;

        cout << "Qué quieres hacer del menú: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int traversalType;
                cout << "Tipo de visita:" << endl;
                cout << "1. Preorder" << endl;
                cout << "2. Inorder" << endl;
                cout << "3. Postorder" << endl;
                cout << "4. Level-order" << endl;
                cout << "(1-4): ";
                cin >> traversalType;

                switch (traversalType) {
                    case 1:
                        Tree1.printpreorder();
                        break;
                    case 2:
                        Tree1.printInorder();
                        break;
                    case 3:
                        Tree1.printpostorder();
                        break;
                    case 4:
                        Tree1.printpornivel();
                        break;
                    default:
                        cout << "Opción no válida" << endl;
                }
                break;
            }

            case 2:
                 cout << "La altura del árbol es de: " << Tree1.printhightree() << endl;
                break;

            case 3:
                cout << "De que nodo se van a buscar los ancestros: ";
                cin >> data;
                Tree1.displayAncestors(data);
                break;

            case 4:
                cout << "¿Qué dato se esta buscando? ";
                cin >> data;
                cout << "El nivel del dato es: " << Tree1.highnode(data) << endl;
                break;

            case 5:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opción no válida" << endl;
        }
    } while (choice != 5);

    return 0;
}
