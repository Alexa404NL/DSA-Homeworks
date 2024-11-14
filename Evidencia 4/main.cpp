#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "Bitacora.h"
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "BinaryTree.h"

using namespace std;
namespace fs = std::filesystem;

vector<Bitacora*> leerArchivo(const string& file) {
    vector<Bitacora*> log_file;
    ifstream f(file);
    if (!f.is_open()) {
        cerr << "Error opening file: " << file << endl;
        return log_file;
    }

    int n, m;
    f >> n >> m;
    f.ignore(); // Ignore the newline after m

    vector<string> ips(n);
    for (int i = 0; i < n; ++i) {
        getline(f, ips[i]);
    }

    string l, mes, hora, ip_origin, ip_dest, msg;
    int dia;
    while (getline(f, l)) {
        istringstream iss(l);
        iss >> mes >> dia >> hora >> ip_origin >> ip_dest;
        getline(iss, msg);
        try {
            Bitacora* log = new Bitacora(mes, dia, hora, ip_origin, ip_dest, msg);
            log_file.push_back(log);
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << " in line: " << l << endl;
        }
    }
    return log_file;
}

void freeLogs(vector<Bitacora*>& logs) {
    for (auto& entry : logs) {
        delete entry;
    }
    logs.clear();
}

void merge(vector<Bitacora*>& logs, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Bitacora*> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = logs[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = logs[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i]->compareIP(*R[j])) {
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

void mergeSortLogsByIP(vector<Bitacora*>& logs, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortLogsByIP(logs, left, mid);
        mergeSortLogsByIP(logs, mid + 1, right);

        merge(logs, left, mid, right);
    }
}

unordered_map<string, vector<string>> buildAdjacencyList(const vector<Bitacora*>& logs) {
    unordered_map<string, vector<string>> adj_list;
    for (const auto& log : logs) {
        adj_list[log->get_dir_ip_origin()].push_back(log->get_dir_ip_dest());
    }
    return adj_list;
}

unordered_map<string, int> calculateFanOut(const unordered_map<string, vector<string>>& adj_list) {
    unordered_map<string, int> fan_out;
    for (const auto& entry : adj_list) {
        fan_out[entry.first] = entry.second.size();
    }
    return fan_out;
}

vector<string> findNodesWithHighestFanOut(const unordered_map<string, int>& fan_out) {
    vector<string> highest_fan_out_nodes;
    int max_fan_out = 0;
    for (const auto& entry : fan_out) {
        if (entry.second > max_fan_out) {
            max_fan_out = entry.second;
            highest_fan_out_nodes.clear();
            highest_fan_out_nodes.push_back(entry.first);
        } else if (entry.second == max_fan_out) {
            highest_fan_out_nodes.push_back(entry.first);
        }
    }
    return highest_fan_out_nodes;
}

string findBotMaster(const unordered_map<string, int>& fan_out) {
    string bot_master;
    int max_fan_out = 0;
    for (const auto& entry : fan_out) {
        if (entry.second > max_fan_out) {
            max_fan_out = entry.second;
            bot_master = entry.first;
        }
    }
    return bot_master;
}

int main() {
    vector<Bitacora*> log;
    string filename = "bitacora.txt";

    try {
        if (fs::exists(filename))
            log = leerArchivo(filename);
        else {
            cout << "El archivo " << filename << " no existe" << endl;
            return 1;
        }
    } catch (const exception& exp) {
        cerr << exp.what() << endl;
        return 1;
    }

    // Build adjacency list and calculate fan-out
    auto adj_list = buildAdjacencyList(log);
    auto fan_out = calculateFanOut(adj_list);

    // Find nodes with the highest fan-out
    auto highest_fan_out_nodes = findNodesWithHighestFanOut(fan_out);
    cout << "Nodes with the highest fan-out:" << endl;
    for (const auto& node : highest_fan_out_nodes) {
        cout << node << " with fan-out " << fan_out[node] << endl;
    }

    // Determine the bot master
    string bot_master = findBotMaster(fan_out);
    cout << "Presumed bot master IP: " << bot_master << " with fan-out " << fan_out[bot_master] << endl;

    // Free logs
    freeLogs(log);

    return 0;
}