#include "appHash.h"
#include <iostream>
#include <cmath>

HashTable::HashTable(int expectedSize) {
    size = nextPrime(expectedSize * 2); // Adjust size to be a prime number larger than twice the expected size
    table.resize(size);
}

int HashTable::hash(const string& key) const {
    unsigned long hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

bool HashTable::isUniqueDestination(const vector<string>& uniqueDestinations, const string& ipDest) const {
    for (const auto& dest : uniqueDestinations) {
        if (dest == ipDest) {
            return false;
        }
    }
    return true;
}

void HashTable::insert(const string& ipOrigin, const string& ipDest) {
    int index = hash(ipOrigin);
    int startIndex = index;
    while (table[index].isOccupied && table[index].ipOrigin != ipOrigin) {
        index = (index + 1) % size;
        if (index == startIndex) {
            cerr << "Hash table is full, cannot insert new element." << endl;
            return;
        }
    }
    if (!table[index].isOccupied) {
        table[index].isOccupied = true;
        table[index].ipOrigin = ipOrigin;
    }
    table[index].accessCount++;
    if (isUniqueDestination(table[index].uniqueDestinations, ipDest)) {
        table[index].uniqueDestinations.push_back(ipDest);
    }
    table[index].destinations.push_back(ipDest);
}

HashElement HashTable::get(const string& ipOrigin) const {
    int index = hash(ipOrigin);
    int startIndex = index;
    while (table[index].isOccupied) {
        if (table[index].ipOrigin == ipOrigin) {
            return table[index];
        }
        index = (index + 1) % size;
        if (index == startIndex) {
            break;
        }
    }
    return HashElement{0, vector<string>(), vector<string>(), false, ""};
}

void HashTable::display(const string& ipOrigin) const {
    HashElement element = get(ipOrigin);
    if (element.isOccupied) {
        cout << "IP Origin: " << ipOrigin << endl;
        cout << "Access Count: " << element.accessCount << endl;
        cout << "Unique Destinations: " << element.uniqueDestinations.size() << endl;
        cout << "Destinations: ";
        for (const auto& dest : element.destinations) {
            cout << dest << " ";
        }
        cout << endl;
    } else {
        cout << "IP Origin not found." << endl;
    }
}

void HashTable::displayAll() const {
    for (const auto& element : table) {
        if (element.isOccupied) {
            cout << "IP Origin: " << element.ipOrigin << endl;
            cout << "Access Count: " << element.accessCount << endl;
            cout << "Unique Destinations: " << element.uniqueDestinations.size() << endl;
            cout << "Destinations: ";
            for (const auto& dest : element.destinations) {
                cout << dest << " ";
            }
            cout << endl;
        }
    }
}

int HashTable::nextPrime(int n) const {
    while (true) {
        n++;
        bool isPrime = true;
        for (int i = 2; i <= std::sqrt(n); ++i) {
            if (n % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            return n;
        }
    }
}