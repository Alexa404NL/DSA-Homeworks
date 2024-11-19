// Marco Antonio Torres Ramirez
// A00839451
// Act 5.1 - Implementación individual de operaciones sobre conjuntos

#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include <vector>
#include <string>

using namespace std;

// Estructura para representar un elemento de la tabla hash
struct HashElement {
    int index;
    string value;
    bool isOccupied;
};

// Clase para representar una tabla hash
class HashTable {
public:
    HashTable(int size);
    int hash(int key);
    void insertar(int key, const string& value);
    void visualizar();
    void rehash();

private:
    vector<HashElement> table;
    int size;
    int numElements;
};

#endif // TABLA_HASH_H