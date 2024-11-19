#ifndef APP_HASH_H
#define APP_HASH_H

#include <vector>
#include <string>

using namespace std;

// Structure to represent a hash table element
struct HashElement {
    int accessCount;
    vector<string> uniqueDestinations;
    vector<string> destinations;
    bool isOccupied;
    string ipOrigin;
};

// Class to represent a hash table
class HashTable {
public:
    HashTable(int expectedSize);
    void insert(const string& ipOrigin, const string& ipDest);
    HashElement get(const string& ipOrigin) const;
    void display(const string& ipOrigin) const;
    void displayAll() const;

private:
    vector<HashElement> table;
    int size;
    int hash(const string& key) const;
    bool isUniqueDestination(const vector<string>& uniqueDestinations, const string& ipDest) const;
    int nextPrime(int n) const;
};

#endif // APP_HASH_H