// Act 4.3 - Actividad Integral de Grafos
//
// Alexa Nohemi Lara Carvajal - A01571503
// Marco Antonio Torres Ramírez - A00839451
// Bryan Alberto Lemus Meza - A00838730
// Ernesto De Luna Quintero - A01394008

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

vector<string> ips;

std::vector<string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    std::vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

int binary_search(const vector<string>& arr, const string& ip) {
    string delimiter = ".";
    vector<string> v1 = split (ip, delimiter);

    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        vector<string> v2 = split (arr[mid], delimiter);
        if (stoi(v2[0]) == stoi(v1[0])) {
            if (stoi(v2[1]) == stoi(v1[1])) {
                if (stoi(v2[2]) == stoi(v1[2])) {
                    return mid;
                } else if (stoi(v2[2]) < stoi(v1[2])) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            } else if (stoi(v2[1]) < stoi(v1[1])) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        } else if (stoi(v2[0]) < stoi(v1[0])) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
        if (low==high){
            return high;
        }
    }
    return -1;
}

vector<int> splitIP(const string& ip) {
    vector<int> octets;
    stringstream ss(ip);
    string octet;
    while (getline(ss, octet, '.')) {
        octets.push_back(stoi(octet));
    }
    return octets;
}

bool compareIPs(const string& ip1, const string& ip2) {
    vector<int> octets1 = splitIP(ip1);
    vector<int> octets2 = splitIP(ip2);
    return octets1 < octets2;
}

void merge(vector<string>& logs, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<string> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = logs[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = logs[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compareIPs(L[i], R[j])) {
            logs[k] = L[i];
            i++;
        } else {
            logs[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        logs[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        logs[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortLogsByIP(vector<string>& logs, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortLogsByIP(logs, left, mid);
        mergeSortLogsByIP(logs, mid + 1, right);

        merge(logs, left, mid, right);
    }
}

vector<vector<string> > leerArchivo(const string& file) {
    vector<vector<string> > adj;
    ifstream f(file);
    if (!f.is_open()) {
        cerr << "Error opening file: " << file << endl;
        return adj;
    }

    int n, m;
    f >> n >> m;
    f.ignore();

    ips.resize(n);
    for (int i = 0; i < n; ++i) {
        getline(f, ips[i]);
    }
    mergeSortLogsByIP(ips, 0,n-1);
    adj.resize(n);

    string l, mes, hora, ip_origin, ip_dest, msg;
    int dia;
    while (getline(f, l)) {
        istringstream iss(l);
        iss >> mes >> dia >> hora >> ip_origin >> ip_dest;
        int pos = binary_search(ips, ip_origin);
        adj[pos].push_back(ip_dest);
        getline(iss, msg);
    }
    return adj;
}


void calculateFanout(const vector<vector<string> >& adj, const vector<string>& ips) {
    vector<int> fanout(ips.size(), 0);


    for (const auto& connections : adj) {
        for (const auto& ipDest : connections) {
            int pos = binary_search(ips, ipDest);
            fanout[pos]++;
        }
    }

    auto maxout= max_element(fanout.begin(), fanout.end());

    cout << "Fan-out (entradas) para cada IP:" << endl;
    for (size_t i = 0; i < ips.size(); ++i) {
        cout << ips[i] << ": " << fanout[i] << endl;
    }

    cout << "\nIP(s) con el mayor fanout:" << endl;
    int maxIndex = maxout-fanout.begin();
    cout << ips[maxIndex] << "con fan-out: " << *maxout  << endl;
}



void encontrar_boot(const vector<vector<string> >& adj, const vector<string>& ips) {
    vector<int> salidas(adj.size(), 0);
    int maxs = 0;

    for (size_t i = 0; i < adj.size(); ++i) {
        salidas[i] = adj[i].size();
        maxs = max(maxs, salidas[i]);
    }

    cout << "\n IP(s) con el mayor número de salidas (" << maxs << "):" << endl;
    for (size_t i = 0; i < adj.size(); ++i) {
        if (salidas[i] == maxs) {
            cout << ips[i] << endl;
        }
    }
}

void freeLogs(vector< vector<string> >& logs) {
    for (auto& entry : logs) {
        entry.clear();
    }
    logs.clear();
}

int main() {
    vector<vector<string> > list_adj;
    string filename = "bitacora.txt";

    try {
        if (fs::exists(filename))
            list_adj = leerArchivo(filename);
        else {
            cout << "El archivo " << filename << " no existe" << endl;
            return 1;
        }
    } catch (const exception& exp) {
        cerr << exp.what() << endl;
        return 1;
    }

    calculateFanout(list_adj, ips);
    encontrar_boot(list_adj, ips);
    freeLogs(list_adj);

    return 0;
}