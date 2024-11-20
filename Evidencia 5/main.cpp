#include <iostream>
#include <fstream>
#include <sstream>
#include "appHash.h"

using namespace std;

void readLogFile(const string& filename, HashTable& hashTable) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    int n, m;
    file >> n >> m;
    file.ignore();

    vector<string> ips(n);
    for (int i = 0; i < n; ++i) {
        getline(file, ips[i]);
    }

    string line, month, time, ipOrigin, ipDest, reason;
    int day;
    while (getline(file, line)) {
        istringstream iss(line);
        iss >> month >> day >> time >> ipOrigin >> ipDest;
        getline(iss, reason);
        size_t pos = ipOrigin.find(':');
        if (pos != string::npos) {
            ipOrigin = ipOrigin.substr(0, pos);
        }
        hashTable.insert(ipOrigin, ipDest);
    }
}

int main() {
    string filename = "bitacora.txt";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    int n, m;
    file >> n >> m;
    file.close();

    HashTable hashTable(n + m);

    readLogFile(filename, hashTable);

    // // Display the full hash table for debugging
    // cout << "\nFull Hash Table:" << endl;
    // hashTable.displayAll();

    string ipOrigin;
    cout << "Enter IP Origin to get details: ";
    cin >> ipOrigin;
    hashTable.display(ipOrigin);

    return 0;
}