// Marco Antonio Torres Ramirez
// A00839451
// Act 5.1 - Implementación individual de operaciones sobre conjuntos

#include "tabla_hash.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor para inicializar la tabla hash con un tamaño dado
// complexity: O(n)
HashTable::HashTable(int size) : size(size) {
    table.resize(size);
    for (int i = 0; i < size; ++i) {
        table[i].index = i;
        table[i].isOccupied = false;
    }
}

// Funcion hash para obtener el indice de la tabla hash para una clave dada
// complexity: O(1)
int HashTable::hash(int key) {
    return key % size;
}

// Funcion para insertar un valor en la tabla hash para una clave dada 
// complexity: O(n)
void HashTable::insertar(int key, const string& value) {
    if (static_cast<float>(numElements) / size >= 0.7) { // Rehash si el factor de carga es mayor o igual a 0.7
        rehash();
    }

    int index = hash(key);
    int originalIndex = index;
    while (table[index].isOccupied) {
        index = (index + 1) % size;
        if (index == originalIndex) {
            cerr << "La tabla de hash esta llena" << endl;
            return;
        }
    }
    table[index].value = value;
    table[index].isOccupied = true;
    numElements++;
}

// Funcion para visualizar la tabla hash 
// complexity: O(n)
void HashTable::visualizar() {
    for (const auto& element : table) {
        cout << "Index: " << element.index
             << ", Value: " << (element.isOccupied ? element.value : "Vacio")
             << ", State: " << (element.isOccupied ? "Ocupado" : "Vacio") << endl;
    }
}

// Funcion para rehash la tabla hash
// complexity: O(n)
void HashTable::rehash() {
    int newSize = size * 2;
    vector<HashElement> newTable(newSize);
    for (int i = 0; i < newSize; ++i) {
        newTable[i].index = i;
        newTable[i].isOccupied = false;
    }

    for (const auto& element : table) {
        if (element.isOccupied) {
            int index = element.index % newSize;
            while (newTable[index].isOccupied) {
                index = (index + 1) % newSize;
            }
            newTable[index].value = element.value;
            newTable[index].isOccupied = true;
        }
    }

    table = newTable;
    size = newSize;
}

int main() {
    int size;
    cout << "Ingrese el tamaño de la tabla hash: ";
    cin >> size;
    if (size <= 0) {
        cerr << "El tamaño de la tabla hash debe ser mayor a 0" << endl;
        return 1;
    }

    HashTable ht(size);

    // Test para la funcion hash
    cout << "Prueba de la funcion hash:" << endl;
    int testKeys[] = {15, 22, 36, 43}; // Claves de prueba para la funcion hash
    for (int key : testKeys) {
        cout << "Hash de " << key << ": " << ht.hash(key) << endl;
    }

    // Insertar elementos en la tabla hash
    int count = 0;
    int key;
    string value;
    char choice;
    do {
        cout << "\nIngrese la llave a insertar: ";
        cin >> key;
        cout << "Ingrese el valor a insertar: ";
        getline(cin >> ws, value);
        ht.insertar(key, value);
        cout << "Desear insertar otro elemento? (y/n): ";
        cin >> choice;
        count++;
    } while (choice == 'y' || choice == 'Y');

    // Visualizar la tabla hash
    cout << "\nTabla hash:" << endl;
    ht.visualizar();

    return 0;
}

// El codigo se probó con los siguientes casos de prueba:
// Caso 1:
// Ingrese el tamaño de la tabla hash: 5
// Prueba de la funcion hash:
// Hash de 15: 0
// Hash de 22: 2
// Hash de 36: 1
// Hash de 43: 3

// Ingrese la llave a insertar: 1
// Ingrese el valor a insertar: 1
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 5
// Ingrese el valor a insertar: 5
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 10
// Ingrese el valor a insertar: 10
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 17
// Ingrese el valor a insertar: 17
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 3
// Ingrese el valor a insertar: 3
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 7
// Ingrese el valor a insertar: 7
// Desear insertar otro elemento? (y/n): n

// Tabla hash:
// Index: 0, Value: 5, State: Ocupado
// Index: 1, Value: 1, State: Ocupado
// Index: 2, Value: 10, State: Ocupado
// Index: 3, Value: 17, State: Ocupado
// Index: 4, Value: 3, State: Ocupado
// Index: 5, Value: Vacio, State: Vacio
// Index: 6, Value: Vacio, State: Vacio
// Index: 7, Value: 7, State: Ocupado
// Index: 8, Value: Vacio, State: Vacio
// Index: 9, Value: Vacio, State: Vacio

// Caso 2:
// Ingrese el tamaño de la tabla hash: -3
// El tamaño de la tabla hash debe ser mayor a 0

// Caso 3:
// Ingrese el tamaño de la tabla hash: 10 
// Prueba de la funcion hash:
// Hash de 15: 5
// Hash de 22: 2
// Hash de 36: 6
// Hash de 43: 3

// Ingrese la llave a insertar: 76
// Ingrese el valor a insertar: 76
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 89
// Ingrese el valor a insertar: 89
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 15
// Ingrese el valor a insertar: 15
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 32
// Ingrese el valor a insertar: 32
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 9
// Ingrese el valor a insertar: 9
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 43
// Ingrese el valor a insertar: 43
// Desear insertar otro elemento? (y/n): n

// Tabla hash:
// Index: 0, Value: 9, State: Ocupado
// Index: 1, Value: Vacio, State: Vacio
// Index: 2, Value: 32, State: Ocupado
// Index: 3, Value: 43, State: Ocupado
// Index: 4, Value: Vacio, State: Vacio
// Index: 5, Value: 15, State: Ocupado
// Index: 6, Value: 76, State: Ocupado
// Index: 7, Value: Vacio, State: Vacio
// Index: 8, Value: Vacio, State: Vacio
// Index: 9, Value: 89, State: Ocupado

// Caso 4:
// Ingrese el tamaño de la tabla hash: 8
// Prueba de la funcion hash:
// Hash de 15: 7
// Hash de 22: 6
// Hash de 36: 4
// Hash de 43: 3

// Ingrese la llave a insertar: 12
// Ingrese el valor a insertar: valor 12
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 15
// Ingrese el valor a insertar: valor 15
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 17
// Ingrese el valor a insertar: valor 17
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 11 
// Ingrese el valor a insertar: valor 11
// Desear insertar otro elemento? (y/n): y

// Ingrese la llave a insertar: 20
// Ingrese el valor a insertar: valor 20
// Desear insertar otro elemento? (y/n): n

// Tabla hash:
// Index: 0, Value: Vacio, State: Vacio
// Index: 1, Value: valor 17, State: Ocupado
// Index: 2, Value: Vacio, State: Vacio
// Index: 3, Value: valor 11, State: Ocupado
// Index: 4, Value: valor 12, State: Ocupado
// Index: 5, Value: valor 20, State: Ocupado
// Index: 6, Value: Vacio, State: Vacio
// Index: 7, Value: valor 15, State: Ocupado